#include "cmpt_error.h"
//#include "database.h"
//#include "record.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <ncurses.h>
using namespace std;

class single_record{
    public:
        single_record(string mangaName, vector<string> mangaAuthor, vector <string> mangaGenres, 
                      bool mangaStatus, int releaseYear): name(mangaName), authors(mangaAuthor),
                      genres(mangaGenres), isReleasing(mangaStatus), year(releaseYear){}

        single_record(string mangaName, vector<string> mangaAuthor):
            name(mangaName), authors(mangaAuthor){}

        //default constructor
        single_record(){
            name = "ERROR 404: NAME NOT FOUND";
        }

        // Setters
        void set_name(string newName){name = newName;}
        void set_authors(vector<string> newAuthor){authors = newAuthor;}
        void set_genres(vector <string> newGenres) {genres = newGenres;}
        void set_status (bool newStat){isReleasing = newStat;}
        void set_year(int newYear){year = newYear;}
    
        // Getters
        string getName() const { return name; }
        vector<string> getAuthors() const { return authors; }
        vector<string> getGenres() const { return genres; }
        bool getStatus() const { return isReleasing; }
        int getYear() const { return year; }

        //print everything
        void printEntry(){
            initscr();
            int yMax, xMax;
            getmaxyx(stdscr,yMax, xMax);

            //create window
            WINDOW *win = newwin(yMax*0.70, xMax*0.70, yMax, xMax);
            refresh();
            
            box(win,0,0);
            wrefresh(win);

            mvwprintw(win, 1, 1,"=========================================");
            mvwprintw(win, 2, 1, "Name: " + name + "." );

            mvwprintw(win, 3, 1, "Genres: ");
            int rowPos = 9;
            for (int i = 0; i < genres.size() - 1; i++){
                mvwprintw(win, 4, rowPos, genres.at(i) + ", ");
                rowPos += genres.at(i).length() + 2;
            }
            mvwprintw(win, 4, rowPos, genres.at(genres.size() - 1) + ".");

            mvwprintw(win, 5, 1, "Authors: ");
            rowPos = 10;
            for (int i = 0; i < authors.size() - 1; i++){
                mvwprintw(win, 5, rowPos, authors.at(i) + ", ");
                rowPos += authors.at(i).length() + 2;
            }
            mvwprintw(win, 5, rowPos, authors.at(authors.size() - 1) + ".");

            mvwprintw(win,6, 1,"Status: ");
            if (isReleasing == true){
                mvwprintw(win,6, 9,"Releasing.");}
            else {mvwprintw(win,6, 9,"Completed.");}

            mvwprintw(win, 7, 1, "Year of release: " + year + ".");
            wrefresh(win);
            endwin();
        }

        //add to vector functions
        void add_genre(string newGenre){genres.push_back(newGenre);}
        void add_author(string newAuthor){authors.push_back(newAuthor);}

        ~single_record(){}

    private:
        string name = "";
        vector<string> authors = {};
        vector <string> genres = {};
        bool isReleasing = false;
        int year = 0;
};

class database {
    public:
        // Default constructor
        database(string input){
            readFile(input);
            initscr();
            getmaxyx(stdscr,yMax, xMax);
        }

        // Reads in each entry in database.txt
        void readFile (string input){
            // Reads in the file containing manga manga
            fstream inFile(input);
            // Checks if file name is valid
            while (inFile.fail()){
                // Asks user if they meant something else. 
                //Yes = rerun function with correct name
                //No = quit program
                mvwprintw(win, 2, 1, "The file does not exist. Did you mean something else? (Y)es or (N)o: ");
                wrefresh(win);
                char userResponse = wgetch(win);
                while (userResponse != 'n' && userResponse != 'y' && userResponse != 'r'){
                    mvwprintw(win, 1, 1, "Your response is invalid, please try again: ");
                    wrefresh(win);
                    userResponse = wgetch(win);
                }
                if (userResponse == 'n'){
                    cmpt::error("\nThe file inputted does not exist. Please try again.");}
                mvwprintw(win, 1, 1, "What is the name of the file?");
                wrefresh(win);
                string correctInput;
                cin >> correctInput;
                fstream inFile(correctInput);
            }

            // Read in each input (line) from the file
            vector<single_record> mangaList;
            while (true){
                string entry;
                single_record manga;
                getline(inFile, entry);
                if (inFile.fail()){break;}

                // Getting title
                manga.set_name (entry.substr(0, entry.find("|")));
                entry = entry.substr(entry.find("|") + 1); // Get rid of trailing |

                // Getting Genres
                // Get rid of starting and trailing {}|
                string mangaGenres = entry.substr(0, entry.find("|"));
                // Get rid of starting and trailing {}|
                mangaGenres = mangaGenres.substr(1, mangaGenres.size() - 2); 
                while (true){
                    string mangaGenre;
                    if (mangaGenres.find(",") != -1){ // There are remaining genres
                        mangaGenre = mangaGenres.substr(0, mangaGenres.find(","));
                        // Get rid of comma and space
                        mangaGenres = mangaGenres.substr(mangaGenres.find(",") + 2); 
                        manga.add_genre(mangaGenre);}
                    else { // Last genre in the list
                        manga.add_genre(mangaGenres);
                        break;} 
                }
                entry = entry.substr(entry.find("|") + 1);
                
                // Getting authors
                string mangaAuthors = entry.substr(0, entry.find("|"));
                // Get rid of starting and trailing {}:
                mangaAuthors = mangaAuthors.substr(1, mangaAuthors.size() - 2); 
                while (true){
                    string mangaAuthor;
                    if (mangaAuthors.find(",") != -1){ // There are remaining genres
                        mangaAuthor = mangaAuthors.substr(0, mangaAuthors.find(","));
                        // Get rid of comma and space
                        mangaAuthors = mangaAuthors.substr(mangaAuthors.find(",") + 2); 
                        manga.add_author(mangaAuthor);}
                    else { // Last genre in the list
                        manga.add_author(mangaAuthors);
                        break;} 
                }
                entry = entry.substr(entry.find("|") + 1);

                // Getting Status of releasing or completed
                if (entry.substr(0, entry.find("|")) == "releasing"){manga.set_status(true);}
                entry = entry.substr(entry.find("|") + 1);

                // Getting Release Date
                manga.set_year (stoi(entry));

                // Append all this information to mangaList as its own object
                mangaList.push_back(manga);
            }
            inFile.close();
            this->mangaList = mangaList;
            //return mangaList;
        } 

/* -------------------------- Searching for records ------------------------- */
        // Searching by name
        single_record searchByName (string name){
            // The case where user enters in exact name of manga
            for (int i = 0; i < mangaList.size(); i++){
                if (name == mangaList.at(i).getName()){return mangaList.at(i);}}
            // The case where user enters in a "substring" of the name of manga
            for (int i = 0; i < mangaList.size(); i++){
                // Turns all letters of manga's name lower case to remove case sensitivity
                string lowercaseName;
                for (char character : mangaList.at(i).getName()){
                    lowercaseName.push_back(tolower(character));
                }
                // Turns all letters of user's input lower case to remove case sensitivity
                string lowercaseUserInput;
                for (char character : name){
                    lowercaseUserInput.push_back(tolower(character));
                }
                if (lowercaseName.find(lowercaseUserInput) != -1){
                    return mangaList.at(i);
                }
            }
            mvwprintw(win, 3, 1, "The manga that you are looking for cannot be found. Please try again.");
            wrefresh(win);
            single_record noRecord;
            return noRecord;
        }
        // Searching by exact year
        vector<single_record> searchByYear (int year){
            // For each manga with matching year, append to searchResults and return at end
            vector<single_record> searchResults;
            for (single_record manga : mangaList){
                if (manga.getYear() == year){
                    searchResults.push_back(manga);
                }
            }
            if (searchResults.size() == 0){
                mvwprintw(win, 3, 1, "The manga that you are looking for cannot be found. Please try again.");
                wrefresh(win);
            return searchResults;}
        }
        // Searching by year range
        vector<single_record> searchByYear (int yearStart, int yearEnd){
            // For each manga within year range, append to searchResults and return at end
            vector<single_record> searchResults;
            for (single_record manga: mangaList){
                if (manga.getYear() >= yearStart && manga.getYear() <= yearEnd){
                    searchResults.push_back(manga);
                }
            }
            if (searchResults.size() == 0){
                mvwprintw(win, 3, 1, "The manga that you are looking for cannot be found. Please try again.");
                wrefresh(win);
            return searchResults;}
        }

/* ------------------- Searching for and deleting records ------------------- */
        // Searching by name
        void deleteByName (string name){
            // The case where user enters in exact name of manga
            for (int i = 0; i < mangaList.size(); i++){
                if (name == mangaList.at(i).getName()){
                    if (deleteConfirmation(i, mangaList.at(i))){
                        mangaList.erase(mangaList.begin() + i);
                        mvwprintw(win, 3, 1, "Entry deleted.");
                        wrefresh(win);
                        return;
                    }
                    else {
                        mvwprintw(win, 3, 1, "Entry deleted.");
                        wrefresh(win);
                        return;
                    }
                }
            }
            // The case where user enters in a "substring" of the name of manga
            for (int i = 0; i < mangaList.size(); i++){
                // Turns all letters of manga's name lower case to remove case sensitivity
                string lowercaseName;
                for (char character : mangaList.at(i).getName()){
                    lowercaseName.push_back(tolower(character));
                }
                // Turns all letters of user's input lower case to remove case sensitivity
                string lowercaseUserInput;
                for (char character : name){
                    lowercaseUserInput.push_back(tolower(character));
                }
                if (lowercaseName.find(lowercaseUserInput) != -1){
                    if (deleteConfirmation(i, mangaList.at(i))){
                        mangaList.erase(mangaList.begin() + i);
                        mvwprintw(win, 3, 1, "Entry deleted.");
                        wrefresh(win);
                        return;
                    }
                    else {
                        mvwprintw(win, 3, 1, "Entry deleted.");
                        wrefresh(win);
                        return;
                    }
                }
            }
            mvwprintw(win, 3, 1, "The manga that you are looking for cannot be found. Please try again.");
            wrefresh(win);
        }
        // Searching by exact year
        void deleteByYear (int year){
            // For each manga with matching year, append to searchResults and return at end
            vector<single_record> searchResults;
            for (single_record manga : mangaList){
                if (manga.getYear() == year){
                    searchResults.push_back(manga);
                }
            }
            // Display all matched entries and ask user for which one they want to delete
            for (int i = 0; i < searchResults.size(); i++){
                displayInformation(i, searchResults.at(i));
            }
            if (searchResults.size() == 0){
                mvwprintw(win, 3, 1, "The manga that you are looking for cannot be found. Please try again.");
                wrefresh(win);
                return;}

            deleteConfirmationYear(searchResults);
        }
        // Searching by year range
        void deleteByYear (int yearStart, int yearEnd){
            // For each manga within year range, append to searchResults and return at end
            vector<single_record> searchResults;
            for (single_record manga: mangaList){
                if (manga.getYear() >= yearStart && manga.getYear() <= yearEnd){
                    searchResults.push_back(manga);
                }
            }
            if (searchResults.size() == 0){
                mvwprintw(win, 3, 1, "The manga that you are looking for cannot be found. Please try again.");
                wrefresh(win);
                return;}
            for (int i = 0; i < searchResults.size(); i++){
                displayInformation(i, searchResults.at(i));
            }
            deleteConfirmationYear(searchResults);
        }

        // Ask for confirmation on deleting record
        bool deleteConfirmation (int index, single_record manga){
            //bool userConfirmation = false;
            // Use the parameter manga to display manga later once we have a function to do so
            mvwprintw(win, 1, 1, "Are you sure you would like to delete: ");
            wrefresh(win); 
            displayInformation(index, manga);
            mvwprintw(win, 2, 1, "(Y)es or (N)o: ");
            wrefresh(win);
            string userInput; 
            cin >> userInput;
            userInput[0] = tolower(userInput[0]); // Turns any input to lowercase
            while ((userInput != "y" && userInput != "n")|| userInput.length() != 1){
                mvwprintw(win, 2, 1, "Please enter a valid response. (Y)es or (N)o: ");
                wrefresh(win);
                cin >> userInput;
            }
            if (userInput == "y"){return true;}
            return false;
        }

        void deleteConfirmationYear (vector<single_record> searchResults){
            mvwprintw(win, 1, 1, "Enter the entry # of the one you want to delete");
            wrefresh(win);

            string userStr;
            cin >> userStr;
            while (!realNum (userStr, searchResults.size())){
                mvwprintw(win, 2, 1, "The entry # inputted is invalid, please try again: ");
                wrefresh(win);
                cin >> userStr;
            }
            
            // Account for index display, decrement by 1 for proper index
            int userInput = stoi (userStr) - 1;
            if (deleteConfirmation (userInput, searchResults.at(userInput))){
                // Loop through the entries, find matching name of user's input then delete
                for (int i = 0; i < mangaList.size(); i++){
                    if (mangaList.at(i).getName() == searchResults.at(userInput).getName()){
                        mangaList.erase(mangaList.begin() + i);
                    }
                }
                mvwprintw(win, 1, 1, "Entry has been deleted.");
                wrefresh(win);
            }
            else {
                mvwprintw(win, 1, 1, "Entry has been deleted.");
                wrefresh(win);
            }

        }
        
        bool realNum (string userInput, int end){
            for (int pos = 0; pos < userInput.length(); pos++){
                if (!(userInput[pos] >= '0' && userInput[pos] <= '9')){
                    return false;}}
            if (stoi (userInput) > end || stoi(userInput) < 1){return false;}

            return true;
        }

/* -------------- Listing records in multiple different orders -------------- */
        vector<single_record> listAlphabetical(){

            // Using selection sort, sort the manga based on the first character of names
            int minIndex;
            vector<single_record> alphabeticalList = mangaList;

            // Iteration for beginning index in unsorted section of alphabeticalList
            for (int i = 0; i < alphabeticalList.size() - 1; i++){
                // Finding the minimum element in the current unsorted alphabeticalList
                // Set index of the 'minimum element' 
                //default to the first index of unsorted alphabeticalList
                minIndex = i;
                // Iterate through the unsorted section of the vector
                for (int j = i + 1; j < alphabeticalList.size(); j++){
                    // Compare the first letters of the titles
                    if (alphabeticalList.at(j).getName()<alphabeticalList.at(minIndex).getName()){
                        minIndex = j;
                    }
                }
                // Swap element at the minIndex with beginning of unsorted vector
                swap(alphabeticalList.at(minIndex), alphabeticalList.at(i));
            }
            return alphabeticalList;
        }

        vector<single_record> listAlphabeticalReverse(){
            // Using selection sort, sort the manga based on the first character of names
            vector<single_record> alphabeticalListReverse = listAlphabetical();
            reverse(alphabeticalListReverse.begin(), alphabeticalListReverse.end());
            return alphabeticalListReverse;
        }

        vector<single_record> listNumerical(){
            vector <single_record> numericalList = mangaList;
            for (int start = 0; start < numericalList.size()-1; start++){
		        int min = start;
		        for (int check = start + 1; check < numericalList.size(); check++){
			        if (numericalList.at(check).getYear() < numericalList.at(min).getYear()){
                        min = check;
                    }
                }
                swap(numericalList.at(min), numericalList.at(start));
            }
	        return numericalList;   
        }

        vector<single_record> listNumericalReverse(){
            vector <single_record> numericalList = listNumerical();
            reverse (numericalList.begin(), numericalList.end());
            return numericalList;
        }

        // Getters
        vector<single_record> getMangaList() const{ return mangaList; };

        //Modify the vector
        void add_entry (single_record newEntry){mangaList.push_back(newEntry);}
        
        // Displaying a manga's information
        void displayInformation(int index, single_record manga){
            for (int pos = 0; pos < mangaList.size(); pos ++){
                mvwprintw(win, pos*15 + 1, 1, "Entry #" + to_string(pos+1));
                mvwprintw(win, pos*15 + 2, 1,"=========================================");
                mvwprintw(win, pos*15 + 3, 1, "Name: " + mangaList.at(pos).getName() + "." );

                mvwprintw(win, pos*15 + 4, 1, "Genres: ");
                vector<string> genres = mangaList.at(pos).getGenres();
                int rowPos = 9;
                for (int i = 0; i < genres.size() - 1; i++){
                    mvwprintw(win, pos*15 + 4, rowPos, genres.at(i) + ", ");
                    rowPos += genres.at(i).length() + 2;
                }
                mvwprintw(win, pos* 15 + 4, rowPos, genres.at(genres.size() - 1) + ".");

                mvwprintw(win, pos*15 + 5, 1, "Authors: ");
                rowPos = 10;
                vector<string> authors = mangaList.at(pos).getAuthors();
                for (int i = 0; i < authors.size() - 1; i++){
                    mvwprintw(win, pos*15 + 5, rowPos, authors.at(i) + ", ");
                    rowPos += authors.at(i).length() + 2;
                }
                mvwprintw(win, pos* 15 + 5, rowPos, authors.at(authors.size() - 1) + ".");

                mvwprintw(win, pos*15 + 6, 1,"Status: ");
                if (mangaList.at(pos).getStatus() == true){
                    mvwprintw(win, pos*15 + 6, 9,"Releasing.");}
                else {mvwprintw(win, pos*15 + 6, 9,"Completed.");}

                mvwprintw(win, pos*15 + 7, 1, "Year of release: " 
                          + mangaList.at(pos).getYear() + ".");
            }
            wrefresh(win);
        }

        // Deconstructor
        ~database(){
            endwin();
        }

    private:
        vector<single_record> mangaList = {};
        int yMax, xMax;
        WINDOW *win = newwin(yMax*0.70, xMax*0.70, yMax, xMax);
};

class menu{
    public:
        //default and only constructor
        menu(){
            initscr();
            //get screen size
            getmaxyx(stdscr,yMax, xMax);

            //create window
            win = newwin(yMax*0.70, xMax*0.70, yMax, xMax);
            refresh();
            
            box(win,0,0);
            mvwprintw(win, 1, 1, "Welcome to the Manga Database!\n----------------------------");
            wrefresh(win);

            keypad(win, true);

            //continues until user selects quit
            while (response != 'q'){
                printMenu();
                //adding a manga into the database
                if (response == 'a'){
                    addEntry();
                }
                //finding a manga by its name or year of release in the database
                else if (response == 'f'){
                    mvwprintw(win, 1, 1, "You are currently: finding an entry.");
                    mvwprintw(win, 3, 1, "You can search by:"); 
                    mvwprintw(win, 5, 1, "(N)ame of manga");
                    mvwprintw(win, 6, 1, "(Y)ear of release");
                    mvwprintw(win, 8, 1, "(R)eturn to main menu");   
                    mvwprintw(win, 10, 1,"Enter the letter of your choice:");
                    
                    wrefresh(win);
                    
                    char userResponse = wgetch(win);
                    while (userResponse != 'n' && userResponse != 'y' && userResponse != 'r'){
                        mvwprintw(win, 1, 1, "Your response is invalid, please try again: ");
                        wrefresh(win);
                        userResponse = wgetch(win);
                    }
                
                    if(userResponse == 'n'){
                        mvwprintw(win, 1, 1, "Enter the name of the manga you are searching for:");
                        wrefresh(win);
                        string mangaName;
                        getline (cin, mangaName);
                        if (info->searchByName(mangaName).getName()!= "ERROR 404: NAME NOT FOUND"){ 
                            info->searchByName(mangaName).printEntry();}
                    }

                    else if (userResponse == 'y'){
                        mvwprintw(win, 1, 1, "Are you searching for a (S)pecific year or a (R)ange:");
                        wrefresh(win);
                        userResponse = wgetch(win);
                        while (userResponse != 's' && userResponse != 'r'){
                            mvwprintw(win, 1, 1, "Your response is invalid, please try again: ");
                            mvwprintw(win, 3, 1, "Are you searching for a (S)pecific year or a (R)ange:");
                            wrefresh(win);
                            userResponse = wgetch(win);
                        }
                        
                        if (userResponse == 's'){
                            mvwprintw(win, 1, 1, "What year are you looking for?: "); 
                            
                            string year;
                            cin >> year;
                            while (!realNum (year)){
                                mvwprintw(win, 1, 1, "That is not a valid year, please try again: ");
                                wrefresh(win);
                                cin >> year;}
                            printDatabase(info->searchByYear(stoi(year)));
                        }
                        
                        else{
                            string startYear;
                            string endYear;
                            mvwprintw(win,1,1,"Enter the starting year: ");
                            wrefresh(win);
                            cin >> startYear;
                            while (!realNum (startYear)){
                                mvwprintw(win, 1,1, "That is not a valid year, please try again: ");
                                wrefresh(win);
                                cin >> startYear;}
                            mvwprintw(win,1,1,"Enter the starting year: ");
                            wrefresh(win);
                            cin >> endYear;
                            while (!realNum (endYear)){
                                mvwprintw(win, 1,1, "That is not a valid year, please try again: ");
                                wrefresh(win);
                                cin >> endYear;}
                            printDatabase(info -> searchByYear(stoi(startYear), stoi(endYear)));
                        }
                    }
                }
                //delete a manga by its name or year of release in the database
                else if (response == 'd'){
                    mvwprintw(win, 1, 1, "You are currently: deleting an entry.");
                    mvwprintw(win, 2, 1, "You can delete by: ");
                    mvwprintw(win, 3, 1, "(N)ame of manga");
                    mvwprintw(win, 4, 1, "(Y)ear of release");
                    mvwprintw(win, 5, 1, "(R)eturn to main menu");
                    mvwprintw(win, 6, 1, "Enter the letter of your choice: ");
                    wrefresh(win);
                    
                    char userResponse = wgetch(win);
                    while (userResponse != 'n' && userResponse != 'y' && userResponse != 'r'){
                        mvwprintw(win, 1, 1, "Your response is invalid, please try again: ");
                        wrefresh(win);
                        userResponse = wgetch(win);
                    }

                    if(userResponse == 'n'){
                        mvwprintw(win, 1, 1, "Enter the name of the manga youa re deleting: ");
                        wrefresh(win);
                        
                        string mangaName;
                        cin.ignore();
                        getline (cin, mangaName);
                        info-> deleteByName(mangaName);}

                    else if (userResponse == 'y'){
                        mvwprintw(win, 1, 1, "Are you deleting a (S)pecific year or a (R)ange: ");
                        wrefresh(win);

                        char userResponse = wgetch(win);
                        while (userResponse != 's' && userResponse != 'r'){
                            mvwprintw(win, 1, 1, "Your response is invalid, please try again: ");
                            wrefresh(win);
                            userResponse = wgetch(win);
                        }
                        if (userResponse == 's'){
                            mvwprintw(win, 1, 1, "What year are you deleting?: ");
                            wrefresh(win);

                            string year;
                            cin >> year;
                            while (!realNum (year)){
                                mvwprintw(win, 2, 1, "That is not a valid year please try again: ");
                                wrefresh(win);
                                
                                cin >> year;}
                            info->deleteByYear(stoi(year));}
                        
                        else{
                            string startYear;
                            string endYear;
                            
                            mvwprintw(win, 1, 1, "Enter the starting year: ");
                            wrefresh(win);

                            cin >> startYear;
                            while (!realNum (startYear)){
                                mvwprintw(win, 2, 1, "That is not a valid year.");
                                wrefresh(win);
                                cin >> startYear;}
                
                            mvwprintw(win, 2, 1, "Enter the ending year: ");
                            wrefresh(win);

                            cin >> endYear;
                            while (!realNum (endYear)){
                                mvwprintw(win, 3, 1, "That is not a valid year please try again: ");
                                wrefresh(win);
                                cin >> endYear;}
                            info -> deleteByYear(stoi(startYear), stoi(endYear));}
                    }
                }
                //list the database by alphatical order or numerical order
                else if (response == 'l'){
                    mvwprintw(win, 1, 1, "You are currently: listing entries.");
                    mvwprintw(win, 3, 1, "You can order by:"); 
                    mvwprintw(win, 5, 1, "(N)ame of manga");
                    mvwprintw(win, 6, 1, "(Y)ear of release");
                    mvwprintw(win, 8, 1, "(R)eturn to main menu");   
                    mvwprintw(win, 10, 1,"Enter the letter of your choice:");
                    
                    char userResponse = wgetch(win);
                    while (userResponse != 'n' && userResponse != 'y' && userResponse != 'r'){
                        mvwprintw(win, 1, 1, "Your response is invalid, please try again: ");
                        wrefresh(win);
                        userResponse = wgetch(win);
                    }

                    if(userResponse == 'n'){
                        mvwprintw(win, 1,1, "Did you want them listed in (A)lphabetical order or"); 
                        mvwprintw(win, 1, 52, " in (R)everse alphabetical order?: ");   
                        
                        char userResponse = wgetch(win);
                        while (userResponse != 'a' && userResponse != 'r'){
                            mvwprintw(win, 1, 1, "Your response is invalid, please try again: ");
                            wrefresh(win);
                            userResponse = wgetch(win);
                        }
                        
                        if (userResponse == 'a'){printDatabase(info->listAlphabetical());}
                        else {printDatabase(info->listAlphabeticalReverse());}
                    }

                    else if (userResponse == 'y'){
                        mvwprintw(win, 1, 1, "Did you want them listed in (A)scending order or");
                        mvwprintw(win, 1, 49, " in (D)escending order?: ");
                        wrefresh(win);

                        char userResponse = wgetch(win);
                        while (userResponse != 'a' && userResponse != 'd'){
                            mvwprintw(win, 1, 1, "Your response is invalid, please try again: ");
                            wrefresh(win);
                            userResponse = wgetch(win);
                        }
                        
                      if (userResponse == 'a'){printDatabase(info->listNumerical());}
                        else {printDatabase(info->listNumericalReverse());}
                    }
                } 
                //stops the program
                else if (response == 'q'){
                   mvwprintw(win, 1,1, "Have a great day!! --dee.nah");
                    //creates a text file of the database
                    ofstream dataFile("database.txt");
                    //adds elements to the file
                    string returnStr = "";
                    vector <single_record> file = info->getMangaList();
                    for (int pos = 0; pos < file.size(); pos++){
                        single_record record = file.at(pos);
                        //add name
                        returnStr = record.getName() + "|{";
                        //add genres
                        for (int gen = 0; gen < record.getGenres().size() - 1; gen++){
                            returnStr += record.getGenres().at(gen) + ", ";}
                        returnStr += record.getGenres().at(record.getGenres().size()-1) + "}|{";
                        //add authors
                        for (int loc = 0; loc < record.getAuthors().size() - 1; loc++){
                            returnStr += record.getAuthors().at(loc) + ", ";}
                        returnStr += record.getAuthors().at(record.getAuthors().size()-1) + "}|";
                        //add status and year
                        if(record.getStatus()){returnStr += "releasing|" + to_string(record.getYear());}
                        else {returnStr += "completed|" + to_string(record.getYear());}
                        dataFile << returnStr << endl;
                    }

                    dataFile.close();
                }
                //if the case where the user does not respond correctly
                else{mvwprintw(win, 1, 1, "Sorry, Your response is invalid, please try again: ");}
            }
        }

        //ensures that user input is actually a number
        bool realNum (string userInput){
            for (int pos = 0; pos < userInput.length(); pos++){
                if (!(userInput[pos] >= '0' && userInput[pos] <= '9')){
                    return false;}}
            if (stoi (userInput) > 2021 || stoi(userInput) < 1952){return false;}

            return true;
        }

        //prints the available choices in menu
        void printMenu(){

            box(win, 0, 0);
            mvwprintw(win, 1, 1, "Main Menu: ");
            mvwprintw(win, 3, 1, "(A)dd a manga.");
            mvwprintw(win, 4, 1, "(D)elete a manga.");
            mvwprintw(win, 5, 1, "(L)ist mangas.");
            mvwprintw(win, 6, 1, "(Q)uit.");
            mvwprintw(win, 8, 1, "Enter the letter of your choice: ");
            wrefresh(win);

            int response = wgetch(win);
            
        }
        
        //changes all characters in a string to lower case
        string toLowerStr (string str){
            string returnStr = "";
            for (int pos = 0; pos < str.length(); pos++){
                returnStr += tolower(str[pos]);}
            return returnStr;
        }

        //prints all elements in a vector
        void printDatabase(vector <single_record> mangaList){
            for (int pos = 0; pos < mangaList.size(); pos ++){
                mvwprintw(win, pos*15 + 1, 1, "Entry #" + to_string(pos+1));
                mvwprintw(win, pos*15 + 2, 1,"=========================================");
                mvwprintw(win, pos*15 + 3, 1, "Name: " + mangaList.at(pos).getName() + "." );

                mvwprintw(win, pos*15 + 4, 1, "Genres: ");
                vector<string> genres = mangaList.at(pos).getGenres();
                int rowPos = 9;
                for (int i = 0; i < genres.size() - 1; i++){
                    mvwprintw(win, pos*15 + 4, rowPos, genres.at(i) + ", ");
                    rowPos += genres.at(i).length() + 2;
                }
                mvwprintw(win, pos* 15 + 4, rowPos, genres.at(genres.size() - 1) + ".");

                mvwprintw(win, pos*15 + 5, 1, "Authors: ");
                rowPos = 10;
                vector<string> authors = mangaList.at(pos).getAuthors();
                for (int i = 0; i < authors.size() - 1; i++){
                    mvwprintw(win, pos*15 + 5, rowPos, authors.at(i) + ", ");
                    rowPos += authors.at(i).length() + 2;
                }
                mvwprintw(win, pos* 15 + 5, rowPos, authors.at(authors.size() - 1) + ".");

                mvwprintw(win, pos*15 + 6, 1,"Status: ");
                if (mangaList.at(pos).getStatus() == true){
                    mvwprintw(win, pos*15 + 6, 9,"Releasing.");}
                else {mvwprintw(win, pos*15 + 6, 9,"Completed.");}

                mvwprintw(win, pos*15 + 7, 1, "Year of release: " 
                          + mangaList.at(pos).getYear() + ".");
            }
            wrefresh(win);
        }

        //adds an entry
        void addEntry(){
            mvwprintw(win, 1, 1, "You are currently: adding an entry. " +
                                    "Enter \"exit\" if you change your mind.");
            wrefresh(win);

            mvwprintw(win, 1, 1, "Enter the manga name: ");
            wrefresh(win);
            
            string name;
            cin.ignore();
            getline (cin, name);
            if (name == "exit"){return;}

            mvwprintw(win, 1, 1, "Enter the manga authors one at a time. " + 
                                    "Enter \"stop\" to stop: ");
            wrefresh(win);

            string entry = "";
            vector<string> authors;
            while (true){
                //cout << "Enter an author: \n";
                mvwprintw(win, 1, 1, "Enter an author: ");
                wrefresh(win);

                getline (cin, entry);
                if (entry == "exit"){return;}
                else if (toLowerStr(entry) == "stop"){break;}
                authors.push_back(entry);}
                    
            //cout << "Enter the manga genres one at a time. Enter \"stop\" to stop: ";
            mvwprintw(win, 1, 1, "Enter the manga genres one at a time. " +
                                    "Enter \"stop\" to stop: ");
            wrefresh(win);

            vector<string> genres;
            while (true){
                // cout << "Enter a genre: \n";
                mvwprintw(win, 1, 1, "Enter a genre: ");
                wrefresh(win);

                getline (cin, entry);
                if (entry == "exit"){return;}
                else if (toLowerStr(entry) == "stop"){break;}
                genres.push_back(entry);}

            bool isReleasing;
            while (true){
                mvwprintw(win, 1, 1, "Is this manga still releaasing? " + 
                                        "Enter (Y)es or (N)o: ");
                wrefresh(win);

                cin >> entry;
                if (entry == "exit"){return;}
                if (toLowerStr (entry) == "y"){
                    isReleasing = true;
                    break;}
                else if (toLowerStr (entry) == "n"){
                    isReleasing = false;
                    break;}}

            //cout << "Enter the manga year of release\n";
            mvwprintw(win, 1, 1, "Enter the manga year of release: ");
            wrefresh(win);

            string year;
            cin >> year;
            while (!realNum (year)){
                if (year == "exit"){return;}
                mvwprintw(win, 1, 1, "That is not a valid year, please try again.");
                wrefresh(win);
                cin >> year;}

            single_record newRecord (name, authors, genres, isReleasing, stoi(year));
            info->add_entry (newRecord);

            mvwprintw(win, 1, 1, "You have successfully entered a new entry.");
            wrefresh(win);
        }

        ~menu(){
            delete info;
            endwin();}
    
    private:
        int response;
        int xMax, yMax;
        WINDOW *win;
        database *info = new database("database.txt");
};



int main(){
    menu mangaMenu;
}