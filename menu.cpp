//menu class
#include "cmpt_error.h"
#include "database.h"
#include "record.h"
#include "menu.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class menu{
    public:
        //default and only constructor
        menu(){
            cout << "Welcome to the Manga Database!\n-----------------------------\n";
            //continues until user selects quit
            while (response != "q"){
                printMenu();
                //adding a manga into the database
                if (response == "a"){
                    addEntry();
                }
                //finding a manga by its name or year of release in the database
                else if (response == "f"){
                    cout << "You are currently: finding an entry.\n"
                         << "\nYou can search by:\n"
                         << "(N)ame of manga\n"
                         << "(Y)ear of release\n"
                         << "\n(R)eturn to main menu\n"
                         << "\nEnter the letter of your choice:";
                    
                    string userResponse;
                    cin >> userResponse;
                    userResponse = toLowerStr(userResponse);
                    while (userResponse != "n" && userResponse != "y"&& userResponse != "r"){
                        cout << "Your response is invalid, please try again: ";
                        cin >> userResponse;
                        userResponse = toLowerStr(userResponse);}

                    if(userResponse == "n"){
                        cout << "Enter the name of the manga you are searching for:";
                        string mangaName;
                        cin.ignore();
                        getline (cin, mangaName);
                        if (info->searchByName(mangaName).getName()!= "ERROR 404: NAME NOT FOUND"){ 
                            info->searchByName(mangaName).printEntry();}
                        }

                    else if (userResponse == "y"){
                        cout << "Are you searching for a (S)pecific year or a (R)ange:";
                        string userResponse;
                        cin >> userResponse;
                        userResponse = toLowerStr(userResponse);
                        while (userResponse != "s" && userResponse != "r"){
                            cout << "Your response is invalid, please try again: ";
                            cin >> userResponse;
                            userResponse = toLowerStr(userResponse);}
                        
                        if (userResponse == "s"){
                            cout << "What year are you looking for? ";
                            string year;
                            cin >> year;
                            while (!realNum (year)){
                                cout << "That is not a valid year, please try again: ";
                                cin >> year;}
                            printDatabase(info->searchByYear(stoi(year)));}
                        
                        else{
                            string startYear;
                            string endYear;
                            cout << "Enter the starting year: ";
                            cin >> startYear;
                            while (!realNum (startYear)){
                                cout << "That is not a valid year, please try again: ";
                                cin >> startYear;}
                            cout << "Enter the ending year: ";
                            cin >> endYear;
                            while (!realNum (endYear)){
                                cout << "That is not a valid year, please try again: ";
                                cin >> endYear;}
                            printDatabase(info -> searchByYear(stoi(startYear), stoi(endYear)));}
                    }
                }
                //delete a manga by its name or year of release in the database
                else if (response == "d"){
                    cout << "You are currently: deleting an entry.\n"
                         << "\nYou can delete by:\n"
                         << "(N)ame of manga\n"
                         << "(Y)ear of release\n"
                         << "\n(R)eturn to main menu\n"
                         << "\nEnter the letter of your choice:";
                    
                    string userResponse;
                    cin >> userResponse;
                    userResponse = toLowerStr(userResponse);
                    while (userResponse != "n" && userResponse != "y"&& userResponse != "r"){
                        cout << "Your response is invalid, please try again: ";
                        cin.ignore();
                        cin >> userResponse;
                        userResponse = toLowerStr(userResponse);}

                    if(userResponse == "n"){
                        cout << "Enter the name of the manga you are deleting:";
                        string mangaName;
                        cin.ignore();
                        getline (cin, mangaName);
                        info-> deleteByName(mangaName);}

                    else if (userResponse == "y"){
                        cout << "Are you deleting a (S)pecific year or a (R)ange:";
                        string userResponse;
                        cin >> userResponse;
                        userResponse = toLowerStr(userResponse);
                        while (userResponse != "s" && userResponse != "r"){
                            cout << "Your response is invalid, please try again: ";
                            cin >> userResponse;
                            userResponse = toLowerStr(userResponse);}
                        
                        if (userResponse == "s"){
                            cout << "What year are you deleting? ";
                            string year;
                            cin >> year;
                            while (!realNum (year)){
                                cout << "That is not a valid year, please try again: ";
                                cin >> year;}
                            info->deleteByYear(stoi(year));}
                        
                        else{
                            string startYear;
                            string endYear;
                            cout << "Enter the starting year: ";
                            cin >> startYear;
                            while (!realNum (startYear)){
                                cout << "That is not a valid year, please try again: ";
                                cin >> startYear;}
                            cout << "Enter the ending year: ";
                            cin >> endYear;
                            while (!realNum (endYear)){
                                cout << "That is not a valid year, please try again: ";
                                cin >> endYear;}
                            info -> deleteByYear(stoi(startYear), stoi(endYear));}
                    }
                }
                //list the database by alphatical order or numerical order
                else if (response == "l"){
                    cout << "You are currently: listing entries.\n"
                         << "\nYou can list by:\n"
                         << "(N)ame of manga\n"
                         << "(Y)ear of release\n"
                         << "\n(R)eturn to main menu\n"
                         << "\nEnter the letter of your choice:";
                    
                    string userResponse;
                    cin >> userResponse;
                    userResponse = toLowerStr(userResponse);
                    while (userResponse != "n" && userResponse != "y"&& userResponse != "r"){
                        cout << "Your response is invalid, please try again: ";
                        cin >> userResponse;
                        userResponse = toLowerStr(userResponse);}

                    if(userResponse == "n"){
                        cout << "Did you want them listed in (A)lphabetical order or" 
                             << " in (R)everse alphabetical order?: ";
                        cin >> userResponse;
                        userResponse = toLowerStr(userResponse);
                        while (userResponse != "a" && userResponse != "r"){
                            cout << "Your response is invalid, please try again: ";
                            cin >> userResponse;
                            userResponse = toLowerStr(userResponse);}
                        
                        if (userResponse == "a"){printDatabase(info->listAlphabetical());}
                        else {printDatabase(info->listAlphabeticalReverse());}
                    }

                    else if (userResponse == "y"){
                        cout << "Did you want them listed in (A)scending order or" 
                             << " in (D)escending order?: ";
                        cin >> userResponse;
                        userResponse = toLowerStr(userResponse);
                        while (userResponse != "a" && userResponse != "d"){
                            cout << "Your response is invalid, please try again: ";
                            cin >> userResponse;
                            userResponse = toLowerStr(userResponse);}
                        
                      if (userResponse == "a"){printDatabase(info->listNumerical());}
                        else {printDatabase(info->listNumericalReverse());}
                    }
                } 
                //stops the program
                else if (response == "q"){
                    cout << "Have a great day!!\n";
                    //creates a text file of the database
                    ofstream dataFile("database.txt");
                    //adds elements to the file
                    string returnStr = "";
                    vector <single_record> file = info->getMangaList();
                    for (int pos = 0; pos < file.size(); pos++){
                        single_record record = file.at(pos);
                        //add name
                        returnStr = record.getName() + ",{";
                        //add genres
                        for (int gen = 0; gen < record.getGenres().size() - 1; gen++){
                            returnStr += record.getGenres().at(gen) + ", ";}
                        returnStr += record.getGenres().at(record.getGenres().size()-1) + "},{";
                        //add authors
                        for (int loc = 0; loc < record.getAuthors().size() - 1; loc++){
                            returnStr += record.getAuthors().at(loc) + ", ";}
                        returnStr += record.getAuthors().at(record.getAuthors().size()-1) + "},";
                        //add status and year
                        if(record.getStatus()){returnStr += "releasing," + to_string(record.getYear());}
                        else {returnStr += "completed," + to_string(record.getYear());}
                        dataFile << returnStr << endl;
                    }

                    dataFile.close();
                }
                //if the case where the user does not respond correctly
                else{cout << "Sorry, Your response is invalid, please try again: ";}
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
            cout << "\nMain Menu:\n"
                 << "\n(A)dd a manga.\n"
                 << "(F)ind a manga.\n"
                 << "(D)elete a manga.\n"
                 << "(L)ist mangas.\n"
                 << "(Q)uit.\n\n"
                 << "Enter the LETTER of your choice: ";
            cin >> response;
            if (response.length() != 0){response [0] = tolower(response[0]);}
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
                cout << "Entry #" << pos + 1 << endl;
                cout << "=========================================" << endl;
                cout << "Name: " << mangaList.at(pos).getName() << "." << endl;

                cout << "Genres: ";
                vector<string> genres = mangaList.at(pos).getGenres();
                for (int i = 0; i < genres.size() - 1; i++){cout << genres.at(i) << ", ";}
                cout << genres.at(genres.size() - 1) << "." << endl;

                cout << "Authors: ";
                vector<string> authors = mangaList.at(pos).getAuthors();
                for (int i = 0; i < authors.size() - 1; i++){cout << authors.at(i) << ", ";}
                cout << authors.at(authors.size() - 1) << "." << endl;

                cout << "Status: ";
                if (mangaList.at(pos).getStatus() == true){cout << "Releasing." << endl;}
                else {cout << "Completed." << endl;}

                cout << "Year of release: " << mangaList.at(pos).getYear() << "." << endl << endl;
            }
        }

        //adds an entry
        void addEntry(){
            cout << "You are currently: adding an entry. Enter \"exit\" if you change your mind.";

            cout << "\n\nEnter the manga name\n";
            string name;
            cin.ignore();
            getline (cin, name);
            if (name == "exit"){return;}

            cout << "Enter the manga authors one at a time. Enter \"stop\" to stop: ";
            string entry = "";
            vector<string> authors;
            while (true){
                cout << "Enter an author: \n";
                getline (cin, entry);
                if (entry == "exit"){return;}
                else if (toLowerStr(entry) == "stop"){break;}
                authors.push_back(entry);}
                    
            cout << "Enter the manga genres one at a time. Enter \"stop\" to stop: ";
            vector<string> genres;
            while (true){
                cout << "Enter a genre: \n";
                getline (cin, entry);
                if (entry == "exit"){return;}
                else if (toLowerStr(entry) == "stop"){break;}
                genres.push_back(entry);}

            bool isReleasing;
            while (true){
                cout << "Is this manga still releasing ? enter (Y)es or (N)o: ";
                cin >> entry;
                if (entry == "exit"){return;}
                if (toLowerStr (entry) == "y"){
                    isReleasing = true;
                    break;}
                else if (toLowerStr (entry) == "n"){
                    isReleasing = false;
                    break;}}

            cout << "Enter the manga year of release\n";
            string year;
            cin >> year;
            while (!realNum (year)){
                if (year == "exit"){return;}
                cout << "That is not a valid year, please try again: ";
                cin >> year;}

            single_record newRecord (name, authors, genres, isReleasing, stoi(year));
            info->add_entry (newRecord);

            cout << "You have successfully entered a new entry.\n";
        }

        ~menu(){
            delete info;}
    
    private:
        string response = "";
        database *info = new database("database.txt");
};
