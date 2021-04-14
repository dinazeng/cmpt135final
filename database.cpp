
//class database

#include "cmpt_error.h"
#include "database.h"
#include "record.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <ncurses.h>
using namespace std;


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
            /*for (int pos = 0; pos < mangaList.size(); pos ++){
                mvwprintw(win, pos*15 + 1, 1, "Entry #");
                string str = to_string(pos + 1);
                mvwprintw(win, pos*15 + 1, 8, str);

                mvwprintw(win, pos*15 + 2, 1,"=========================================");
                
                mvwprintw(win, pos*15 + 3, 1, "Name: ");
                string name = mangaList.at(pos).getName();
                mvwprintw(win, pos*15 + 3, 6, name);
                mvwprintw(win, pos*15 + 3, mangaList.at(pos).getName().length() + 6, ".");

                mvwprintw(win, pos*15 + 4, 1, "Genres: ");
                vector<string> genres = mangaList.at(pos).getGenres();
                int rowPos = 9;
                for (int i = 0; i < genres.size() - 1; i++){
                    mvwprintw(win, pos*15 + 4, rowPos, genres.at(i));
                    mvwprintw(win, pos*15 + 4, rowPos + 2, ", ");
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

                mvwprintw(win, pos*15 + 7, 1, "Year of release: ");
                mvwprintw(win, pos*15 + 7, 17, "Year of release: ");
            }
            wrefresh(win);
            */
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