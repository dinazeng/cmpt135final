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
        vector<single_record> readFile (string input){
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

            // Read in each input from the file
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
                
                // Getting Authors
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

                // Getting Status
                if (entry.substr(0, entry.find(":")) == "releasing"){manga.set_status(true);}
                entry = entry.substr(entry.find(":") + 1);

                // Getting Release Date
                manga.set_year (stoi(entry));

                // Append all this information to mangaList
                mangaList.push_back(manga);
            }
            inFile.close();
            return mangaList;
        } 

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

        // Getters
        vector<single_record> getMangaList() const {return mangaList;}

        // Deconstructor
        ~database(){}

    private:
        vector<single_record> mangaList = {};
};
