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
        menu(){
            cout << "Welcome to the Manga Database!\n-----------------------------\n";
            while (response != "q"){
                printMenu();
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

//TODO BUFF THIS UP
                    cout << "Enter the manga year of release\n";
                    int year;
                    cin >> year;

                    single_record newRecord (name, authors, genres, isReleasing, year);
                    info->add_entry (newRecord);

                    cout << "You have successfully entered a new entry.\n";
                }
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
                            int year;
                            cin >> year;
                            info->searchByYear(year);}
                        
                        else{
                            int startYear;
                            int endYear;
                            cout << "Enter the starting year: ";
                            cin >> startYear;
                            cout << "Enter the ending year: ";
                            cin >> endYear;
                            info -> searchByYear(startYear, endYear);}
                    }
                }
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
                            int year;
                            cin >> year;
                            info->deleteByYear(year);}
                        
                        else{
                            int startYear;
                            int endYear;
                            cout << "Enter the starting year: ";
                            cin >> startYear;
                            cout << "Enter the ending year: ";
                            cin >> endYear;
                            info -> deleteByYear(startYear, endYear);}
                    }
                }
                else if (response == "l"){}
                else if (response == "q"){
                    delete info;
                    cout << "Have a great day!!\n";}
                else{cout << "Sorry, your response is invalid. Please try again.\n";}
            }
        }

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