#include "cmpt_error.h"
//#include "database.h"
//#include "record.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
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
        vector<single_record> getMangaList() const;

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

int main(){
    cout << "The beginning of the end." << endl << endl;

    // Testing reading file into memory
    database mangaDatabase("database.txt");
    //mangaDatabase.readFile("database.txt");

    // Testing searching by exact string
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
    vector<single_record> listingReverseNumerically = mangaDatabase.listNumericalReverse();

    cout << "End of testing." << endl;
}