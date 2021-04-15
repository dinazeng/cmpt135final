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
            erase();
            refresh();

            mvprintw(1, 1,"=========================================");
                
            mvprintw(3, 1, "Name: ");
            char nameArr[name.length()];                
            for (int n = 0; n < name.length(); n++){nameArr[n] = name[n];}
            mvprintw(3, 6, nameArr);
            mvprintw(3, name.length() + 6, ".");

            mvprintw(4, 1, "Genres: ");
            int rowPos = 9;
            for (int i = 0; i < genres.size() - 1; i++){
                char arr[genres.at(i).length()];
                for (int n = 0; n < genres.at(i).length(); n++){arr[n] = genres.at(i)[n];}
                mvprintw(4, rowPos, arr);
                mvprintw(4, rowPos + genres.at(i).length(), ", ");
                rowPos += genres.at(i).length() + 2;
            }
            char arrGen[genres.at(genres.size() - 1).length()];
            for (int n = 0; n < genres.at(genres.size() - 1).length(); n++){
                arrGen[n] = genres.at(genres.size() - 1)[n];}
            mvprintw(4, rowPos, arrGen);
            mvprintw(4, rowPos + genres.at(genres.size() - 1).length(), ".");
                
            mvprintw(5, 1, "Authors: ");
            rowPos = 10;
            for (int i = 0; i < authors.size() - 1; i++){
                char arrAu[authors.at(i).length()];
                for (int n = 0; n < authors.at(i).length(); n++){arrAu[n] = authors.at(i)[n];}
                mvprintw(5, rowPos, arrAu);
                mvprintw(5, rowPos + authors.at(i).length(), ", ");
                rowPos += authors.at(i).length() + 2;
            }
            char arrAu[authors.at(authors.size() - 1).length()];
            for (int n = 0; n < authors.at(authors.size() - 1).length(); n++){
                arrAu[n] = authors.at(authors.size() - 1)[n];}
            mvprintw(5, rowPos, arrAu);
            mvprintw(5, rowPos + authors.at(authors.size() - 1).length(), ".");

            mvprintw(6, 1,"Status: ");
            if (isReleasing == true){mvprintw(6, 9,"Releasing.");}
            else {mvprintw(6, 9,"Completed.");}

            mvprintw(7, 1, "Year of release: ");
            string yearRel = to_string(year);
            char arrYear[4];
            for (int n = 0; n < 4; n++){arrYear[n] = yearRel[n];}
            mvprintw(7, 18, arrYear);
            
            refresh();
            int stop = getch();

            erase();
            refresh();
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
        database(string input){ readFile(input); }

        // Reads in each entry in database.txt
        void readFile (string input){
            // Reads in the file containing manga manga
            fstream inFile(input);
            // Checks if file name is valid
            while (inFile.fail()){
                // Asks user if they meant something else. 
                //Yes = rerun function with correct name
                //No = quit program
                cout << "The file does not exist. Did you mean something else? (Y)es or (N)o: ";
                char userAnswer;
                cin >> userAnswer;
                if (tolower(userAnswer) == 'n'){
                    cmpt::error("\nThe file inputted does not exist. Please try again.");}
                else {
                    cout << "What is the name of the file?";
                    string correctInput;
                    cin >> correctInput;
                    fstream inFile(correctInput);
                }
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
                string mangaGenres = entry.substr(0, entry.find("|"));
                mangaGenres = mangaGenres.substr(1, mangaGenres.size() - 2); // Get rid of starting and trailing {}|
                while (true){
                    string mangaGenre;
                    if (mangaGenres.find(",") != -1){ // There are remaining genres
                        mangaGenre = mangaGenres.substr(0, mangaGenres.find(","));
                        mangaGenres = mangaGenres.substr(mangaGenres.find(",") + 2); // Get rid of comma and space
                        manga.add_genre(mangaGenre);}
                    else { // Last genre in the list
                        manga.add_genre(mangaGenres);
                        break;} 
                }
                entry = entry.substr(entry.find("|") + 1);
                
                // Getting authors
                string mangaAuthors = entry.substr(0, entry.find("|"));
                mangaAuthors = mangaAuthors.substr(1, mangaAuthors.size() - 2); // Get rid of starting and trailing {}:
                while (true){
                    string mangaAuthor;
                    if (mangaAuthors.find(",") != -1){ // There are remaining genres
                        mangaAuthor = mangaAuthors.substr(0, mangaAuthors.find(","));
                        mangaAuthors = mangaAuthors.substr(mangaAuthors.find(",") + 2); // Get rid of comma and space
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
            cout << "The manga that you are looking for cannot be found. Please try again.\n";
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
                cout << "The manga that you are looking for cannot be found. Please try again.\n";}
            return searchResults;
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
                cout << "The manga that you are looking for cannot be found. Please try again.\n";}
            return searchResults;
        }

/* ------------------- Searching for and deleting records ------------------- */
        // Searching by name
        void deleteByName (string name){
            // The case where user enters in exact name of manga
            for (int i = 0; i < mangaList.size(); i++){
                if (name == mangaList.at(i).getName()){
                    bool userConfirmation = deleteConfirmation(i, mangaList.at(i));
                    if (userConfirmation == true){
                        mangaList.erase(mangaList.begin() + i);
                        cout << "Entry deleted." << endl << endl;
                        return;
                    }
                    else {
                        cout << "Entry not deleted." << endl << endl;
                        return;
                    }
                }}
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
                    bool userConfirmation = deleteConfirmation(i, mangaList.at(i));
                    if (userConfirmation == true){
                        mangaList.erase(mangaList.begin() + i);
                        cout << "Entry deleted." << endl << endl;
                        return;
                    }
                    else {
                        cout << "Entry not deleted." << endl << endl;
                        return;
                    }
                }}
            cout << "The manga that you are looking for cannot be found. Please try again.\n";
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
                cout << "The manga that you are looking for cannot be found. Please try again.\n";
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
                cout << "The manga that you are looking for cannot be found. Please try again.\n";
                return;}
            for (int i = 0; i < searchResults.size(); i++){
                cout << endl;
                displayInformation(i, searchResults.at(i));
            }
            deleteConfirmationYear(searchResults);
        }

        // Ask for confirmation on deleting record
        bool deleteConfirmation (int index, single_record manga){
            //bool userConfirmation = false;
            // Use the parameter manga to display manga later once we have a function to do so
            cout << "Are you sure you would like to delete: " << endl; 
            displayInformation(index, manga);
            cout << endl << "(Y)es or (N)o: ";
            string userInput; 
            cin >> userInput;
            userInput[0] = tolower(userInput[0]); // Turns any input to lowercase
            while ((userInput != "y" && userInput != "n")|| userInput.length() != 1){
                cout << "Please enter a valid response. (Y)es or (N)o: ";
                cin >> userInput;
            }
            if (userInput == "y"){return true;}
            return false;
        }
        void deleteConfirmationYear (vector<single_record> searchResults){
            cout << endl;
            cout << "Enter the entry # of the one you want to delete: ";
            string userStr;
            cin >> userStr;
            while (!realNum (userStr, searchResults.size())){
                cout << "The entry # inputted is invalid please try again.";
                cin >> userStr;
            }
            
            // Account for index display, decrement by 1 for proper index
            int userInput = stoi (userStr) - 1;
            bool userConfirmation = deleteConfirmation (userInput, searchResults.at(userInput));
            if (userConfirmation == true){
                // Loop through the entries, find matching name of user's input then delete
                for (int i = 0; i < mangaList.size(); i++){
                    if (mangaList.at(i).getName() == searchResults.at(userInput).getName()){
                        mangaList.erase(mangaList.begin() + i);
                    }
                }
                cout << "Entry has been deleted." << endl;
            }
            else {
                cout << "Entry has not been deleted." << endl;
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
                // Set index of the 'minimum element' default to the first index of unsorted alphabeticalList
                minIndex = i;
                // Iterate through the unsorted section of the vector
                for (int j = i + 1; j < alphabeticalList.size(); j++){
                    // Compare the first letters of the titles
                    if (alphabeticalList.at(j).getName() < alphabeticalList.at(minIndex).getName()){
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
            cout << "Entry #" << index + 1 << endl;
            cout << "=========================================" << endl;
            cout << "Name: " << manga.getName() << "." << endl;

            cout << "Genres: ";
            vector<string> genres = manga.getGenres();
            for (int i = 0; i < genres.size() - 1; i++){
                cout << genres.at(i) << ", ";
            }
            cout << genres.at(genres.size() - 1) << "." << endl;

            cout << "Authors: ";
            vector<string> authors = manga.getAuthors();
            for (int i = 0; i < authors.size() - 1; i++){
                cout << authors.at(i) << ", ";
            }
            cout << authors.at(authors.size() - 1) << "." << endl;

            cout << "Status: ";
            if (manga.getStatus() == true){
                cout << "Releasing." << endl;
            }
            else {
                cout << "Completed." << endl;
            }

            cout << "Year of release: " << manga.getYear() << "." << endl;
        }

        // Deconstructor
        ~database(){}

    private:
        vector<single_record> mangaList = {};
};

class menu{
    public:
        //default and only constructor
        menu(){
            initscr();
            mvprintw(1,1, "Welcome to the Manga Database!\n-----------------------------");
            //continues until user selects quit
            while (response != 'q'){
                erase();
                refresh();
                printMenu();
                //adding a manga into the database
                if (response == 'a'){
                    addEntry();
                }
                //finding a manga by its name or year of release in the database
                else if (response == 'f'){
                    mvprintw(1, 1, "You are currently: finding an entry.");
                    mvprintw(3, 1, "You can search by:"); 
                    mvprintw(5, 1, "(N)ame of manga");
                    mvprintw(6, 1, "(Y)ear of release");
                    mvprintw(8, 1, "(R)eturn to main menu");   
                    mvprintw(10, 1,"Enter the letter of your choice:");
                    
                    refresh();
                    
                    int userResponse = getch();
                    while (userResponse != 'n' && userResponse != 'y' && userResponse != 'r'){
                        mvprintw(11, 1, "Your response is invalid, please try again: ");
                        refresh();
                        userResponse = getch();
                    }

                    erase();
                    refresh(); 

                    if(userResponse == 'n'){
                        mvprintw(1, 1, "Enter the name of the manga you are searching for: ");
                        char mangaName [100];
                        getstr(mangaName);
                        erase();
                        if (info->searchByName(mangaName).getName()!= "ERROR 404: NAME NOT FOUND"){ 
                            info->searchByName(mangaName).printEntry();
                            erase();
                            refresh();
                        }
                    }

                    else if (userResponse == 'y'){
                        mvprintw(1, 1, "Are you searching for a (S)pecific year or a (R)ange:");
                       userResponse = getch();
                        while (userResponse != 's' && userResponse != 'r'){
                            mvprintw(2, 1, "Your response is invalid, please try again: ");
                            userResponse = getch();
                        }
                        
                        if (userResponse == 's'){
                            erase();
                            mvprintw(1, 1, "What year are you looking for? ");
                            char year [10];
                            getstr(year);
                            while (!realNum (year)){
                                mvprintw(2, 1, "That is not a valid year, please try again: ");
                                getstr(year);
                            }
                            printDatabase(info->searchByYear(stoi(year)));
                            erase();
                            refresh();
                        }
                        
                        else{
                            erase();
                            char startYear[10];
                            char endYear [10];
                            mvprintw(1, 1, "Enter the starting year: ");
                            getstr(startYear);
                            while (!realNum (startYear)){
                                mvprintw(2, 1, "That is not a valid year, please try again: ");
                                getstr(startYear);
                            }
                            mvprintw(4, 1, "Enter the ending year: ");
                            getstr(endYear);
                            while (!realNum (endYear)){
                                mvprintw(5, 1, "That is not a valid year, please try again: ");
                                getstr(endYear);}
                            printDatabase(info -> searchByYear(stoi(startYear), stoi(endYear)));
                            erase();
                            refresh();
                        }
                    }
                }
                //delete a manga by its name or year of release in the database
                else if (response == 'd'){
                    mvprintw(1, 1, "You are currently: deleting an entry.");
                    mvprintw(2, 1, "You can delete by: ");
                    mvprintw(3, 1, "(N)ame of manga");
                    mvprintw(4, 1, "(Y)ear of release");
                    mvprintw(5, 1, "(R)eturn to main menu");
                    mvprintw(6, 1, "Enter the letter of your choice: ");
                    refresh();
                    
                    char userResponse = getch();
                    while (userResponse != 'n' && userResponse != 'y' && userResponse != 'r'){
                        mvprintw(8, 1, "Your response is invalid, please try again: ");
                        refresh();
                        userResponse = getch();
                    }
                    
                    erase();
                    refresh();

                    if(userResponse == 'n'){
                        mvprintw(1, 1, "Enter the name of the manga you are deleting: ");
                        refresh();
                        erase();
                        char mangaName[100];
                        getstr(mangaName);
                        info-> deleteByName(mangaName);
                    }

                    else if (userResponse == 'y'){
                        mvprintw(1, 1, "Are you deleting a (S)pecific year or a (R)ange: ");
                        refresh();

                        char userResponse = getch();
                        while (userResponse != 's' && userResponse != 'r'){
                            mvprintw(2, 1, "Your response is invalid, please try again: ");
                            refresh();
                            userResponse = getch();
                        }

                        if (userResponse == 's'){
                            erase();
                            mvprintw(1, 1, "What year are you looking for? ");
                            refresh();
                            char year [10];
                            getstr(year);
                            while (!realNum (year)){
                                mvprintw(2, 1, "That is not a valid year, please try again: ");
                                getstr(year);
                            }
                            info->deleteByYear(stoi(year));
                        }
                        
                        else{
                            erase();
                            char startYear[10];
                            char endYear [10];
                            mvprintw(1, 1, "Enter the starting year: ");
                            getstr(startYear);
                            while (!realNum (startYear)){
                                mvprintw(2, 1, "That is not a valid year, please try again: ");
                                getstr(startYear);
                            }
                            mvprintw(4, 1, "Enter the starting year: ");
                            getstr(endYear);
                            while (!realNum (endYear)){
                                mvprintw(5, 1, "That is not a valid year, please try again: ");
                                getstr(endYear);}
                            info -> deleteByYear(stoi(startYear), stoi(endYear));
                        }
                    }
                }
                //list the database by alphatical order or numerical order
                else if (response == 'l'){
                    mvprintw(1, 1, "You are currently: listing entries.");
                    mvprintw(2, 1, "You can list by: ");
                    mvprintw(3, 1, "(N)ame of manga");
                    mvprintw(4, 1, "(Y)ear of release");
                    mvprintw(5, 1, "(R)eturn to main menu");
                    mvprintw(6, 1, "Enter the letter of your choice: ");
                    refresh();
                    
                    int userResponse = getch();
                    while (userResponse != 'n' && userResponse != 'y' && userResponse != 'r'){
                        mvprintw(11, 1, "Your response is invalid, please try again: ");
                        refresh();
                        userResponse = getch();
                    }

                    erase();
                    refresh();

                    if(userResponse == 'n'){
                        mvprintw(1,1, "Did you want them listed in (A)lphabetical order or"); 
                        mvprintw(1, 52, " in (R)everse alphabetical order?: ");   
                        refresh();
                        
                        char userResponse = getch();
                        while (userResponse != 'a' && userResponse != 'r'){
                            mvprintw(2, 1, "Your response is invalid, please try again: ");
                            refresh();
                            userResponse = getch();
                        }
                        
                        if (userResponse == 'a'){printDatabase(info->listAlphabetical());}
                        else {printDatabase(info->listAlphabeticalReverse());}
                    }

                    else if (userResponse == 'y'){
                        mvprintw(1, 1, "Did you want them listed in (A)scending order or");
                        mvprintw(1, 49, " in (D)escending order?: ");
                        refresh();

                        char userResponse = getch();
                        while (userResponse != 'a' && userResponse != 'd'){
                            mvprintw(2, 1, "Your response is invalid, please try again: ");
                            refresh();
                            userResponse = getch();
                        }
                        
                        if (userResponse == 'a'){printDatabase(info->listNumerical());}
                        else {printDatabase(info->listNumericalReverse());}
                    }
                } 
                //stops the program
                else if (response == 'q'){
                    mvprintw(1,1, "Have a great day!!");
                    endwin();
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
            mvprintw(0, 1, "Main Menu: ");
            mvprintw(2, 1, "(A)dd a manga.");
            mvprintw(3, 1, "(F)ind a manga");
            mvprintw(4, 1, "(D)elete a manga.");
            mvprintw(5, 1, "(L)ist mangas.");
            mvprintw(6, 1, "(Q)uit.");
            mvprintw(8, 1, "Enter the letter of your choice: ");
            refresh();

            response = getch();
            move(0,0);
            erase();
            refresh();
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
            erase();
             for (int pos = 0; pos < mangaList.size(); pos ++){
                mvprintw(pos*9 + 1, 1, "Entry #");
                char entry[3];
                for (int n = 0; n < 3; n++){entry[n] = to_string(pos+1)[n];}
                mvprintw(pos*9 + 1, 8, entry);

                mvprintw(pos*9 + 2, 1,"=========================================");
                
                mvprintw(pos*9 + 3, 1, "Name: ");
                string name = mangaList.at(pos).getName();
                char nameArr[name.length()];
                for (int n = 0; n < name.length(); n++){nameArr[n] = name[n];}
                mvprintw(pos*9 + 3, 6, nameArr);
                mvprintw(pos*9 + 3, mangaList.at(pos).getName().length() + 6, ".");

                mvprintw(pos*9 + 4, 1, "Genres: ");
                vector<string> genres = mangaList.at(pos).getGenres();
                int rowPos = 9;
                for (int i = 0; i < genres.size() - 1; i++){
                    char arr[genres.at(i).length()];
                    for (int n = 0; n < genres.at(i).length(); n++){arr[n] = genres.at(i)[n];}
                    mvprintw(pos*9 + 4, rowPos, arr);
                    mvprintw(pos*9 + 4, rowPos + genres.at(i).length(), ", ");
                    rowPos += genres.at(i).length() + 2;
                }
                char arrGen[genres.at(genres.size() - 1).length()];
                for (int n = 0; n < genres.at(genres.size() - 1).length(); n++){
                    arrGen[n] = genres.at(genres.size() - 1)[n];}
                mvprintw(pos*9 + 4, rowPos, arrGen);
                mvprintw(pos*9 + 4, rowPos + genres.at(genres.size() - 1).length(), ".");

                mvprintw(pos*9 + 5, 1, "Authors: ");
                rowPos = 10;
                vector<string> authors = mangaList.at(pos).getAuthors();
                for (int i = 0; i < authors.size() - 1; i++){
                    char arrAu[authors.at(i).length()];
                    for (int n = 0; n < authors.at(i).length(); n++){arrAu[n] = authors.at(i)[n];}
                    mvprintw(pos*9 + 5, rowPos, arrAu);
                    mvprintw(pos*9 + 5, rowPos + authors.at(i).length(), ", ");
                    rowPos += authors.at(i).length() + 2;
                }
                char arrAu[authors.at(authors.size() - 1).length()];
                for (int n = 0; n < authors.at(authors.size() - 1).length(); n++){
                    arrAu[n] = authors.at(authors.size() - 1)[n];}
                mvprintw(pos*9 + 5, rowPos, arrAu);
                mvprintw(pos*9 + 5, rowPos + authors.at(authors.size() - 1).length(), ".");

                mvprintw(pos*9 + 6, 1,"Status: ");
                if (mangaList.at(pos).getStatus() == true){mvprintw(pos*9 + 6, 9,"Releasing.");}
                else {mvprintw(pos*9 + 6, 9,"Completed.");}

                mvprintw(pos*9 + 7, 1, "Year of release: ");
                string year = to_string(mangaList.at(pos).getYear());
                char arrYear[4];
                for (int n = 0; n < 4; n++){arrYear[n] = year[n];}
                mvprintw(pos*9 + 7, 1, arrYear);
            }
            refresh();
            int stop = getch();
        }

        void addEntry(){
            mvprintw (1, 1, "You are currently: adding an entry. ");
            mvprintw (1, 38, "Enter \"exit\" if you change your mind."); 
            refresh();

            mvprintw (3, 1, "Enter the manga name: ");
            refresh();
            
            char name [100];
            getstr(name);
            if (name == "exit"){return;}

            erase();

            mvprintw (1, 1, "Enter the manga authors one at a time. ");
            mvprintw (1, 40, "Enter \"stop\" to stop: ");
            refresh();

            char entry [100];
            vector<string> authors;
            while (true){
                erase();
                mvprintw (1, 1, "Enter the manga authors one at a time. " );
                mvprintw (1, 40, "Enter \"stop\" to stop: ");
                mvprintw (3, 1, "Enter an author: ");
                refresh();

                getstr (entry);
                if (entry == "exit"){return;}
                else if (toLowerStr(entry) == "stop"){break;}
                authors.push_back(entry);
            }

            erase();
                    
            mvprintw (1, 1, "Enter the manga genres one at a time. " );
            mvprintw (1, 39, "Enter \"stop\" to stop: ");
            refresh();

            vector<string> genres;
            while (true){
                erase();
                mvprintw (1, 1, "Enter the manga genres one at a time. " );
                mvprintw (1, 39, "Enter \"stop\" to stop: ");
                mvprintw (3, 1, "Enter a genre: ");
                refresh();

                getstr (entry);
                if (entry == "exit"){return;}
                else if (toLowerStr(entry) == "stop"){break;}
                genres.push_back(entry);}
            
            erase();

            bool isReleasing;
            mvprintw (1, 1, "Is this manga still releasing? ");
            mvprintw (1, 32,"Enter (Y)es or (N)o or (E) to exit: ");
                                        
            refresh();

            char res = getch();
            while (res != 'n' && res != 'y' && res != 'e'){
                mvprintw(3, 1, "Your response is invalid, please try again: ");
                refresh();
                res = getch();
            }

            if (res == 'e'){return;}
            if (res == 'y'){isReleasing = true;}
            else if (res == 'n'){isReleasing = false;}

            erase();

            mvprintw (1, 1, "Enter the manga year of release: ");
            refresh();

            char year [10];
            getstr(year);
            while (!realNum (year)){
                mvprintw(2, 1, "That is not a valid year, please try again: ");
                getstr(year);
            }

            single_record newRecord (name, authors, genres, isReleasing, stoi(year));
            info->add_entry (newRecord);

            mvprintw (1, 1, "You have successfully entered a new entry.");
            refresh();
        }

        ~menu(){
            delete info;
        }
    
    private:
        char response;
        database *info = new database("database.txt");
};

int main(){

/*     // Testing reading file into memory
    database mangaDatabase("database.txt");
    //mangaDatabase.readFile("database.txt"); */

/*     // Testing searching by exact string
    single_record drStone = mangaDatabase.searchByName("Dr. Stone");
    single_record koiToUtatane = mangaDatabase.searchByName("utatane");
    single_record kanojoOkarishimasu = mangaDatabase.searchByName("okarishimasu");
    single_record kanojoMoKanojo = mangaDatabase.searchByName("Kanojo mo kanojo");
    
    // Testing searching by year
    vector<single_record> range2018 = mangaDatabase.searchByYear(2018);
    // Testing searching by year range
    vector<single_record> range2010to2015 = mangaDatabase.searchByYear(2010, 2015);
    
    // Testing deleting by name 
    mangaDatabase.deleteByName("Dr. Stone");
    mangaDatabase.deleteByName("utatane");
    mangaDatabase.deleteByName("okarishimasu");
    mangaDatabase.deleteByName("Kanojo mo kanojo");
    
    // Testing deleting by year
    mangaDatabase.deleteByYear(2020);
    // Testing deleting by year range
    mangaDatabase.deleteByYear(2014, 2018);
    
    // Testing listing alphabetically
    vector<single_record> listingAlphabetical = mangaDatabase.listAlphabetical();
    // Testing listing reverse alphabetically
    vector<single_record> listingReverseAlphabetical = mangaDatabase.listAlphabeticalReverse();
    // Testing listing numerically
    vector<single_record> listingNumerically = mangaDatabase.listNumerical();
    // Testing listing reverse alphabetically
    vector<single_record> listingReverseNumerically = mangaDatabase.listNumericalReverse(); */

/*     // Testing searching by exact string
    single_record drStone = mangaDatabase.searchByName("bleach");
    single_record koiToUtatane = mangaDatabase.searchByName("boku no hero academia");
    single_record kanojoOkarishimasu = mangaDatabase.searchByName("one piece");
    single_record kanojoMoKanojo = mangaDatabase.searchByName("demon slayer");
    
    // Testing searching by year
    vector<single_record> range2018 = mangaDatabase.searchByYear(2022);
    // Testing searching by year range
    vector<single_record> range2010to2015 = mangaDatabase.searchByYear(1050, 2021);
    
    // Testing deleting by name 
    mangaDatabase.deleteByName("bleach");
    mangaDatabase.deleteByName("boku no hero academia");
    mangaDatabase.deleteByName("one piece");
    mangaDatabase.deleteByName("Demon slayer");
    
    // Testing deleting by year
    mangaDatabase.deleteByYear(2022);
    // Testing deleting by year range
    mangaDatabase.deleteByYear(1953, 2018);
    
    // Testing listing alphabetically
    vector<single_record> listingAlphabetical = mangaDatabase.listAlphabetical();
    // Testing listing reverse alphabetically
    vector<single_record> listingReverseAlphabetical = mangaDatabase.listAlphabeticalReverse();
    // Testing listing numerically
    vector<single_record> listingNumerically = mangaDatabase.listNumerical();
    // Testing listing reverse alphabetically
    vector<single_record> listingReverseNumerically = mangaDatabase.listNumericalReverse(); */

    menu mangaMenu;

}