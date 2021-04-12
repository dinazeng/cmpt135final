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
                    cout << "You are currently: adding a new entry.\n";

                    cout << "\nEnter the manga name\n";
                    string name;
                    getline (cin, name);

                    cout << "Enter the manga authors one at a time. Enter \"stop\" to stop\n";
                    string entry = "";
                    vector<string> authors;
                    while (true){
                        cout << "Enter an author: \n";
                        getline (cin, entry);
                        if (toLowerStr(entry) == "stop"){break;}
                        authors.push_back(entry);}
                    
                    cout << "Enter the manga genres one at a time. Enter \"stop\" to stop\n";
                    vector<string> genres;
                    while (true){
                        cout << "Enter a genre: \n";
                        getline (cin, entry);
                        if (toLowerStr(entry) == "stop"){break;}
                        genres.push_back(entry);}

                    bool isReleasing;
                    while (true){
                        cout << "Is this manga still releasing ? enter (Y)es or (N)o\n";
                        cin >> entry;
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
                        cout << "That is not a valid year, please try again. \n";
                        cin >> year;}

                    single_record newRecord (name, authors, genres, isReleasing, stoi(year));
                    info->add_entry (newRecord);

                    cout << "You have successfully entered a new entry.\n";
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
                        cout << "Your response is invalid. Please Try Again.\n";
                        cin >> userResponse;
                        userResponse = toLowerStr(userResponse);}

                    if(userResponse == "n"){
                        cout << "Enter the name of the manga you are searching for:";
                        string mangaName;
                        getline (cin, mangaName);
                        info-> searchByName(mangaName);}

                    else if (userResponse == "y"){
                        cout << "Are you searching for a (S)pecific year or a (R)ange:";
                        string userResponse;
                        cin >> userResponse;
                        userResponse = toLowerStr(userResponse);
                        while (userResponse != "s" && userResponse != "r"){
                            cout << "Your response is invalid. Please Try Again.\n";
                            cin >> userResponse;
                            userResponse = toLowerStr(userResponse);}
                        
                        if (userResponse == "s"){
                            cout << "What year are you looking for? ";
                            string year;
                            cin >> year;
                            while (!realNum (year)){
                                cout << "That is not a valid year, please try again. \n";
                                cin >> year;}
                            info->searchByYear(stoi(year));}
                        
                        else{
                            string startYear;
                            string endYear;
                            cout << "Enter the starting year: ";
                            cin >> startYear;
                            while (!realNum (startYear)){
                                cout << "That is not a valid year, please try again. \n";
                                cin >> startYear;}
                            cout << "Enter the ending year: ";
                            cin >> endYear;
                            while (!realNum (endYear)){
                                cout << "That is not a valid year, please try again. \n";
                                cin >> endYear;}
                            info -> searchByYear(stoi(startYear), stoi(endYear));}
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
                        cout << "Your response is invalid. Please Try Again.\n";
                        cin >> userResponse;
                        userResponse = toLowerStr(userResponse);}

                    if(userResponse == "n"){
                        cout << "Enter the name of the manga you are deleting:";
                        string mangaName;
                        getline (cin, mangaName);
                        info-> deleteByName(mangaName);}

                    else if (userResponse == "y"){
                        cout << "Are you deleting a (S)pecific year or a (R)ange:";
                        string userResponse;
                        cin >> userResponse;
                        userResponse = toLowerStr(userResponse);
                        while (userResponse != "s" && userResponse != "r"){
                            cout << "Your response is invalid. Please Try Again.\n";
                            cin >> userResponse;
                            userResponse = toLowerStr(userResponse);}
                        
                        if (userResponse == "s"){
                            cout << "What year are you deleting? ";
                            string year;
                            cin >> year;
                            while (!realNum (year)){
                                cout << "That is not a valid year, please try again. \n";
                                cin >> year;}
                            info->deleteByYear(stoi(year));}
                        
                        else{
                            string startYear;
                            string endYear;
                            cout << "Enter the starting year: ";
                            cin >> startYear;
                            while (!realNum (startYear)){
                                cout << "That is not a valid year, please try again. \n";
                                cin >> startYear;}
                            cout << "Enter the ending year: ";
                            cin >> endYear;
                            while (!realNum (endYear)){
                                cout << "That is not a valid year, please try again. \n";
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
                        cout << "Your response is invalid. Please Try Again.\n";
                        cin >> userResponse;
                        userResponse = toLowerStr(userResponse);}

                    if(userResponse == "n"){
                        cout << "Did you want them listed in (A)lphabetical order or" 
                             << " in (R)everse alphabetical order?";
                        cin >> userResponse;
                        userResponse = toLowerStr(userResponse);
                        while (userResponse != "a" && userResponse != "r"){
                            cout << "Your response is invalid. Please Try Again.\n";
                            cin >> userResponse;
                            userResponse = toLowerStr(userResponse);}
                        
                        if (userResponse == "a"){info->listAlphabetical();}
                        else {info->listAlphabeticalReverse();}
                    }

                    else if (userResponse == "y"){
                        cout << "Did you want them listed in (A)scending order or" 
                             << " in (D)escending order?";
                        cin >> userResponse;
                        userResponse = toLowerStr(userResponse);
                        while (userResponse != "a" && userResponse != "d"){
                            cout << "Your response is invalid. Please Try Again.\n";
                            cin >> userResponse;
                            userResponse = toLowerStr(userResponse);}
                        
                        if (userResponse == "a"){info->listNumerical();}
                        else {info->listNumericalReverse();}
                    }
                } 
                //stops the program
                else if (response == "q"){
                    delete info;
                    cout << "Have a great day!!\n";}
                //if the case where the user does not respond correctly
                else{cout << "Sorry, your response is invalid. Please try again.\n";}
            }
        }

        //ensures that user input is actually a number
        bool realNum (string userInput){
            for (int pos = 0; pos < userInput.length(); pos++){
                if (!(userInput[pos] >= '0' && userInput[pos] <= '9')){
                    return false;}
            }
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
                 << "Enter the LETTER of your choice:\n";
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

    private:
        string response = "";
        database *info = new database();
};