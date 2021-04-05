#include "cmpt_error.h"
#include "database.h"
#include "record.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

class database {
    public:

        // Default constructor
        database(){}

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
                manga.set_name (entry.substr(0, entry.find(":")));
                entry = entry.substr(entry.find(":") + 1); // Get rid of trailing :

                // Getting Genres
                string mangaGenres = entry.substr(0, entry.find(":"));
                mangaGenres = mangaGenres.substr(1, mangaGenres.size() - 2); // Get rid of starting and trailing {}:
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
                entry = entry.substr(entry.find(":") + 1);
                
                // Getting authors
                string mangaAuthors = entry.substr(0, entry.find(":"));
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
                entry = entry.substr(entry.find(":") + 1);

                // Getting Status of releasing or completed
                if (entry.substr(0, entry.find(":")) == "releasing"){manga.set_status(true);}
                entry = entry.substr(entry.find(":") + 1);

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
                if (mangaList.at(i).getName().find(name) != 1){return mangaList.at(i);}}
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
                        cout << "Entry deleted." << endl;
                        return;
                    }
                    else {
                        cout << "Entry not deleted." << endl;
                        return;
                    }
                }}
            // The case where user enters in a "substring" of the name of manga
            for (int i = 0; i < mangaList.size(); i++){
                if (mangaList.at(i).getName().find(name) != 1){
                    bool userConfirmation = deleteConfirmation(i, mangaList.at(i));
                    if (userConfirmation == true){
                        mangaList.erase(mangaList.begin() + i);
                        cout << "Entry deleted." << endl;
                    }
                    else {
                        cout << "Entry not deleted." << endl;
                    }
                }}
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
            deleteConfirmationYear(searchResults);
        }

        // Ask for confirmation on deleting record
        bool deleteConfirmation (int index, single_record manga){
            bool userConfirmation = false;
            // Use the parameter manga to display manga later once we have a function to do so
            cout << "Are you sure you would like to delete: " << endl; 
            displayInformation(index, manga);
            cout << endl << "(Y)es or (N)o: ";
            char userInput; cin >> userInput;
            userInput = static_cast<char>(tolower(userInput)); // Turns any input to lowercase
            if (userInput == 'y'){
                return true;
            }
            else {
                return false;
            }

        }
        void deleteConfirmationYear (vector<single_record> searchResults){
            cout << "Enter the entry # of the one you want to delete: ";
            int userInput;
            cin >> userInput;
            userInput--; // Account for index display, decrement by 1 for proper index
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

        // Getters
        vector<single_record> getMangaList() const {return mangaList;}

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

            vector<string> authors = manga.getAuthor();
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

