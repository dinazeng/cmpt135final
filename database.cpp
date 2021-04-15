//database class

#include "cmpt_error.h"
#include "manga_record.h"
#include "database.h"
#include <vector>
#include <string>
#include <fstream>
#include <ncurses.h>

using namespace std;

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
                initscr();
                mvprintw(1, 1,"File does not exist. Did you mean something else? (Y)es or (N)o: ");
                refresh();
                char userResponse = getch();
                while (userResponse != 'n' && userResponse != 'y' && userResponse != 'r'){
                    mvprintw(2, 1, "Your response is invalid, please try again: ");
                    refresh();
                    userResponse = getch();
                }
                if (userResponse == 'n'){
                    cmpt::error("\nThe file inputted does not exist. Please try again.");}
                erase();
                mvprintw(1, 1, "What is the name of the file?");
                refresh();
                char correctInput [100];
                getstr(correctInput);
                endwin();
                fstream inFile(correctInput);
            }

            // Read in each input (line) from the file
            vector<manga_record> mangaList;
            while (true){
                string entry;
                manga_record manga;
                getline(inFile, entry);
                if (inFile.fail()){break;}

                // Getting title
                manga.set_name (entry.substr(0, entry.find("|")));
                entry = entry.substr(entry.find("|") + 1); // Get rid of trailing |

                // Getting Genres
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
                        mangaAuthors = mangaAuthors.substr(mangaAuthors.find(",") + 2); 
                        // Get rid of comma and space
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
        } 

/* -------------------------- Searching for records ------------------------- */
        // Searching by name
        manga_record searchByName (string name){
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
            notFound();
            manga_record noRecord;
            return noRecord;
        }
        // Searching by exact year
        vector<manga_record> searchByYear (int year){
            // For each manga with matching year, append to searchResults and return at end
            vector<manga_record> searchResults;
            for (manga_record manga : mangaList){
                if (manga.getYear() == year){
                    searchResults.push_back(manga);
                }
            }
            if (searchResults.size() == 0){
                notFound();
            }
            return searchResults;
        }
        // Searching by year range
        vector<manga_record> searchByYear (int yearStart, int yearEnd){
            // For each manga within year range, append to searchResults and return at end
            vector<manga_record> searchResults;
            for (manga_record manga: mangaList){
                if (manga.getYear() >= yearStart && manga.getYear() <= yearEnd){
                    searchResults.push_back(manga);
                }
            }
            if (searchResults.size() == 0){
                notFound();
            }
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
                        initscr();
                        mvprintw(1,1,"Entry Deleted");
                        refresh();
                        char stop = getch();
                        erase();
                        endwin();
                        return;
                    }
                    else {
                        initscr();
                        mvprintw(1,1,"Entry NOT Deleted");
                        refresh();
                        char stop = getch();
                        erase();
                        endwin();
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
                    bool userConfirmation = deleteConfirmation(i, mangaList.at(i));
                    if (userConfirmation == true){
                        mangaList.erase(mangaList.begin() + i);
                        initscr();
                        mvprintw(1,1,"Entry Deleted");
                        refresh();
                        char stop = getch();
                        erase();
                        endwin();
                        return;
                    }
                    else {
                        initscr();
                        mvprintw(1,1,"Entry NOT Deleted");
                        refresh();
                        char stop = getch();
                        erase();
                        endwin();
                        return;
                    }
                }
            }
            notFound();
        }
        // Searching by exact year
        void deleteByYear (int year){
            // For each manga with matching year, append to searchResults and return at end
            vector<manga_record> searchResults;
            for (manga_record manga : mangaList){
                if (manga.getYear() == year){
                    searchResults.push_back(manga);
                }
            }
            // Display all matched entries and ask user for which one they want to delete
            for (int i = 0; i < searchResults.size(); i++){
                displayInformation(i, searchResults.at(i));
            }
            if (searchResults.size() == 0){
                notFound();
                return;}

            deleteConfirmationYear(searchResults);
        }
        // Searching by year range
        void deleteByYear (int yearStart, int yearEnd){
            // For each manga within year range, append to searchResults and return at end
            vector<manga_record> searchResults;
            for (manga_record manga: mangaList){
                if (manga.getYear() >= yearStart && manga.getYear() <= yearEnd){
                    searchResults.push_back(manga);
                }
            }
            if (searchResults.size() == 0){
                notFound();
                return;}
            for (int i = 0; i < searchResults.size(); i++){
                displayInformation(i, searchResults.at(i));
            }
            deleteConfirmationYear(searchResults);
        }

        // Ask for confirmation on deleting record
        bool deleteConfirmation (int index, manga_record manga){
            // Use the parameter manga to display manga later once we have a function to do so
            initscr();
            mvprintw(1,1, "Are you sure you would like to delete: ");
            char stop = getch();
            displayInformation(index, manga);
            mvprintw(1, 1, "Confirm (Y)es or (N)o: ");
            refresh();
            int userResponse = getch();
            while (userResponse != 'n' && userResponse != 'y'){
                mvprintw(11, 1, "Your response is invalid, please try again: ");
                refresh();
                userResponse = getch();
            }
            erase();
            refresh();
            endwin();
            if (userResponse == 'y'){return true;}
            return false;
        }

        void deleteConfirmationYear (vector<manga_record> searchResults){
            initscr();
            mvprintw(1, 1, "Enter the entry # of the one you want to delete: ");
            refresh();
            char userStr [3];
            getstr(userStr);
            while (!realNum (userStr, searchResults.size())){
                mvprintw(3, 1, "The entry # inputted is invalid please try again: ");
                refresh();
                getstr(userStr);
            }
            
            erase();
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
                mvprintw(1, 1, "Entry has been deleted.");
            }
            else {mvprintw(1, 1, "Entry has NOT been deleted.");}
            refresh();
            char stop = getch();
            endwin();
        }
        
         bool realNum (string userInput, int end){
            for (int pos = 0; pos < userInput.length(); pos++){
                if (!(userInput[pos] >= '0' && userInput[pos] <= '9')){
                    return false;}}
            if (stoi (userInput) > end || stoi(userInput) < 1){return false;}

            return true;
        }

/* -------------- Listing records in multiple different orders -------------- */
        vector<manga_record> listAlphabetical(){

            // Using selection sort, sort the manga based on the first character of names
            int minIndex;
            vector<manga_record> alphaList = mangaList;

            // Iteration for beginning index in unsorted section of alphabeticalList
            for (int i = 0; i < alphaList.size() - 1; i++){
                // Finding the minimum element in the current unsorted alphabeticalList
                // Set index of the 'minimum element' default 
                //to the first index of unsorted alphabeticalList
                minIndex = i;
                // Iterate through the unsorted section of the vector
                for (int j = i + 1; j < alphaList.size(); j++){
                    // Compare the first letters of the titles
                    if (alphaList.at(j).getName() < alphaList.at(minIndex).getName()){
                        minIndex = j;
                    }
                }
                // Swap element at the minIndex with beginning of unsorted vector
                swap(alphaList.at(minIndex), alphaList.at(i));
            }
            return alphaList;
        }

        vector<manga_record> listAlphabeticalReverse(){
            // Using selection sort, sort the manga based on the first character of names
            vector<manga_record> alphabeticalListReverse = listAlphabetical();
            reverse(alphabeticalListReverse.begin(), alphabeticalListReverse.end());
            return alphabeticalListReverse;
        }

        vector<manga_record> listNumerical(){
            vector <manga_record> numericalList = mangaList;
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

        vector<manga_record> listNumericalReverse(){
            vector <manga_record> numericalList = listNumerical();
            reverse (numericalList.begin(), numericalList.end());
            return numericalList;
        }

        // Getters
        vector<manga_record> getMangaList() const{ return mangaList; };

        //Modify the vector
        void add_entry (manga_record newEntry){mangaList.push_back(newEntry);}
        
        // Displaying a manga's information
        void displayInformation(int index, manga_record manga){
            initscr();
            erase();
            refresh();

            mvprintw(1, 1, "Entry #");
            char entry[to_string(index).length()];
            for (int n = 0; n < 3; n++){entry[n] = to_string(index + 1)[n];}
            mvprintw(1, 8, entry);

            mvprintw(2, 1,"=========================================");
                
            mvprintw(3, 1, "Name: ");
            char nameArr[manga.getName().length()];                
            for (int n = 0; n < manga.getName().length(); n++){nameArr[n] = manga.getName()[n];}
            mvprintw(3, 7, nameArr);
            mvprintw(3, manga.getName().length() + 7, ".");

            mvprintw(4, 1, "Genres: ");
            int rowPos = 9;
            for (int i = 0; i < manga.getGenres().size() - 1; i++){
                char arr[manga.getGenres().at(i).length()];
                for (int n = 0; n < manga.getGenres().at(i).length(); n++){
                    arr[n] = manga.getGenres().at(i)[n];}
                mvprintw(4, rowPos, arr);
                mvprintw(4, rowPos + manga.getGenres().at(i).length(), ", ");
                rowPos += manga.getGenres().at(i).length() + 2;
            }
            char arrGen[manga.getGenres().at(manga.getGenres().size() - 1).length()];
            for (int n = 0; n < manga.getGenres().at(manga.getGenres().size() - 1).length(); n++){
                arrGen[n] = manga.getGenres().at(manga.getGenres().size() - 1)[n];}
            mvprintw(4, rowPos, arrGen);
            mvprintw(4, rowPos + manga.getGenres().at(manga.getGenres().size() - 1).length(), ".");
            
                
            mvprintw(5, 1, "Authors: ");
            rowPos = 10;
            for (int i = 0; i < manga.getAuthors().size() - 1; i++){
                char arrAu[manga.getAuthors().at(i).length()];
                for (int n = 0; n < manga.getAuthors().at(i).length(); n++){
                    arrAu[n] = manga.getAuthors().at(i)[n];}
                mvprintw(5, rowPos, arrAu);
                mvprintw(5, rowPos + manga.getAuthors().at(i).length(), ", ");
                rowPos += manga.getAuthors().at(i).length() + 2;
            }
            char arrAu[manga.getAuthors().at(manga.getAuthors().size() - 1).length()];
            for (int n = 0; n < manga.getAuthors().at(manga.getAuthors().size()-1).length(); n++){
                arrAu[n] = manga.getAuthors().at(manga.getAuthors().size() - 1)[n];}
            mvprintw(5, rowPos, arrAu);
            mvprintw(5, rowPos + manga.getAuthors().at(manga.getAuthors().size()-1).length(), ".");

            mvprintw(6, 1,"Status: ");
            if (manga.getStatus() == true){mvprintw(6, 9,"Releasing.");}
            else {mvprintw(6, 9,"Completed.");}

            mvprintw(7, 1, "Year of release: ");
            string yearRel = to_string(manga.getYear());
            char arrYear[4];
            for (int n = 0; n < 4; n++){arrYear[n] = yearRel[n];}
            mvprintw(7, 18, arrYear);
            
            refresh();
            int stop = getch();

            erase();
            refresh();
            endwin();
        }

        void notFound(){
            initscr();
            mvprintw(1,1,"The manga that you are looking for cannot be found. Please try again.");
            refresh();
            char stop = getch();
            erase();
            endwin();
        }

        // Deconstructor
        ~database(){}

    private:
        vector<manga_record> mangaList = {};
};