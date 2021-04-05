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
            cout << "Welcome to the Manga Database!\n";
            cout << "-----------------------------\n";
            while (response != "q"){
                printMenu();
                if (response == "a"){
                    cout << "You are currently: adding a new entry.\n";

                    cout << "Enter the manga name\n";
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
                else if (response == "f"){}
                else if (response == "d"){}
                else if (response == "l"){}
                else if (response == "q"){}
                else{}
            }
            delete info;
            cout << "Have a great day!!";
        }

        void printMenu(){
            cout << "\n(A)dd a manga.\n";
            cout << "(F)ind a manga.\n";
            cout << "(D)elete a manga.\n";
            cout << "(L)ist mangas.\n";
            cout << "(Q)uit.\n\n";
            cout << "Enter the LETTER of your choice:\n";
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