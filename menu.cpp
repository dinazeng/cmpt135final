//menu class
#include "cmpt_error.h"
#include "database.h"
#include "record.h"
//#include "menu.h"
#include <iostream>
#include <vector>
#include <string>
#include <ncurses.h>
using namespace std;

class menu{
    public:
        //default and only constructor
        menu(){
            initscr();
            //get screen size
            getmaxyx(stdscr,yMax, xMax);

            //create window
            win = newwin(yMax*0.70, xMax*0.70, yMax, xMax);
            refresh();
            
            box(win,0,0);
            mvwprintw(win, 1, 1, "Welcome to the Manga Database!\n----------------------------");
            wrefresh(win);

            keypad(win, true);

            //continues until user selects quit
            while (response != 'q'){
                printMenu();
                //adding a manga into the database
                if (response == 'a'){
                    addEntry();
                }
                //finding a manga by its name or year of release in the database
                else if (response == 'f'){
                    mvwprintw(win, 1, 1, "You are currently: finding an entry.");
                    mvwprintw(win, 3, 1, "You can search by:"); 
                    mvwprintw(win, 5, 1, "(N)ame of manga");
                    mvwprintw(win, 6, 1, "(Y)ear of release");
                    mvwprintw(win, 8, 1, "(R)eturn to main menu");   
                    mvwprintw(win, 10, 1,"Enter the letter of your choice:");
                    
                    wrefresh(win);
                    
                    char userResponse = wgetch(win);
                    while (userResponse != 'n' && userResponse != 'y' && userResponse != 'r'){
                        mvwprintw(win, 1, 1, "Your response is invalid, please try again: ");
                        wrefresh(win);
                        userResponse = wgetch(win);
                    }
                
                    if(userResponse == 'n'){
                        mvwprintw(win, 1, 1, "Enter the name of the manga you are searching for:");
                        wrefresh(win);
                        string mangaName;
                        getline (cin, mangaName);
                        if (info->searchByName(mangaName).getName()!= "ERROR 404: NAME NOT FOUND"){ 
                            info->searchByName(mangaName).printEntry();}
                    }

                    else if (userResponse == 'y'){
                        mvwprintw(win, 1, 1, "Are you searching for a (S)pecific year or a (R)ange:");
                        wrefresh(win);
                        userResponse = wgetch(win);
                        while (userResponse != 's' && userResponse != 'r'){
                            mvwprintw(win, 1, 1, "Your response is invalid, please try again: ");
                            mvwprintw(win, 3, 1, "Are you searching for a (S)pecific year or a (R)ange:");
                            wrefresh(win);
                            userResponse = wgetch(win);
                        }
                        
                        if (userResponse == 's'){
                            mvwprintw(win, 1, 1, "What year are you looking for?: "); 
                            
                            string year;
                            cin >> year;
                            while (!realNum (year)){
                                mvwprintw(win, 1, 1, "That is not a valid year, please try again: ");
                                wrefresh(win);
                                cin >> year;}
                            printDatabase(info->searchByYear(stoi(year)));
                        }
                        
                        else{
                            string startYear;
                            string endYear;
                            mvwprintw(win,1,1,"Enter the starting year: ");
                            wrefresh(win);
                            cin >> startYear;
                            while (!realNum (startYear)){
                                mvwprintw(win, 1,1, "That is not a valid year, please try again: ");
                                wrefresh(win);
                                cin >> startYear;}
                            mvwprintw(win,1,1,"Enter the starting year: ");
                            wrefresh(win);
                            cin >> endYear;
                            while (!realNum (endYear)){
                                mvwprintw(win, 1,1, "That is not a valid year, please try again: ");
                                wrefresh(win);
                                cin >> endYear;}
                            printDatabase(info -> searchByYear(stoi(startYear), stoi(endYear)));
                        }
                    }
                }
                //delete a manga by its name or year of release in the database
                else if (response == 'd'){
                    mvwprintw(win, 1, 1, "You are currently: deleting an entry.");
                    mvwprintw(win, 2, 1, "You can delete by: ");
                    mvwprintw(win, 3, 1, "(N)ame of manga");
                    mvwprintw(win, 4, 1, "(Y)ear of release");
                    mvwprintw(win, 5, 1, "(R)eturn to main menu");
                    mvwprintw(win, 6, 1, "Enter the letter of your choice: ");
                    wrefresh(win);
                    
                    char userResponse = wgetch(win);
                    while (userResponse != 'n' && userResponse != 'y' && userResponse != 'r'){
                        mvwprintw(win, 1, 1, "Your response is invalid, please try again: ");
                        wrefresh(win);
                        userResponse = wgetch(win);
                    }

                    if(userResponse == 'n'){
                        mvwprintw(win, 1, 1, "Enter the name of the manga youa re deleting: ");
                        wrefresh(win);
                        
                        string mangaName;
                        cin.ignore();
                        getline (cin, mangaName);
                        info-> deleteByName(mangaName);}

                    else if (userResponse == 'y'){
                        mvwprintw(win, 1, 1, "Are you deleting a (S)pecific year or a (R)ange: ");
                        wrefresh(win);

                        char userResponse = wgetch(win);
                        while (userResponse != 's' && userResponse != 'r'){
                            mvwprintw(win, 1, 1, "Your response is invalid, please try again: ");
                            wrefresh(win);
                            userResponse = wgetch(win);
                        }
                        if (userResponse == 's'){
                            mvwprintw(win, 1, 1, "What year are you deleting?: ");
                            wrefresh(win);

                            string year;
                            cin >> year;
                            while (!realNum (year)){
                                mvwprintw(win, 2, 1, "That is not a valid year please try again: ");
                                wrefresh(win);
                                
                                cin >> year;}
                            info->deleteByYear(stoi(year));}
                        
                        else{
                            string startYear;
                            string endYear;
                            
                            mvwprintw(win, 1, 1, "Enter the starting year: ");
                            wrefresh(win);

                            cin >> startYear;
                            while (!realNum (startYear)){
                                mvwprintw(win, 2, 1, "That is not a valid year.");
                                wrefresh(win);
                                cin >> startYear;}
                
                            mvwprintw(win, 2, 1, "Enter the ending year: ");
                            wrefresh(win);

                            cin >> endYear;
                            while (!realNum (endYear)){
                                mvwprintw(win, 3, 1, "That is not a valid year please try again: ");
                                wrefresh(win);
                                cin >> endYear;}
                            info -> deleteByYear(stoi(startYear), stoi(endYear));}
                    }
                }
                //list the database by alphatical order or numerical order
                else if (response == 'l'){
                    mvwprintw(win, 1, 1, "You are currently: listing entries.");
                    mvwprintw(win, 3, 1, "You can order by:"); 
                    mvwprintw(win, 5, 1, "(N)ame of manga");
                    mvwprintw(win, 6, 1, "(Y)ear of release");
                    mvwprintw(win, 8, 1, "(R)eturn to main menu");   
                    mvwprintw(win, 10, 1,"Enter the letter of your choice:");
                    
                    char userResponse = wgetch(win);
                    while (userResponse != 'n' && userResponse != 'y' && userResponse != 'r'){
                        mvwprintw(win, 1, 1, "Your response is invalid, please try again: ");
                        wrefresh(win);
                        userResponse = wgetch(win);
                    }

                    if(userResponse == 'n'){
                        mvwprintw(win, 1,1, "Did you want them listed in (A)lphabetical order or"); 
                        mvwprintw(win, 1, 52, " in (R)everse alphabetical order?: ");   
                        
                        char userResponse = wgetch(win);
                        while (userResponse != 'a' && userResponse != 'r'){
                            mvwprintw(win, 1, 1, "Your response is invalid, please try again: ");
                            wrefresh(win);
                            userResponse = wgetch(win);
                        }
                        
                        if (userResponse == 'a'){printDatabase(info->listAlphabetical());}
                        else {printDatabase(info->listAlphabeticalReverse());}
                    }

                    else if (userResponse == 'y'){
                        mvwprintw(win, 1, 1, "Did you want them listed in (A)scending order or");
                        mvwprintw(win, 1, 49, " in (D)escending order?: ");
                        wrefresh(win);

                        char userResponse = wgetch(win);
                        while (userResponse != 'a' && userResponse != 'd'){
                            mvwprintw(win, 1, 1, "Your response is invalid, please try again: ");
                            wrefresh(win);
                            userResponse = wgetch(win);
                        }
                        
                      if (userResponse == 'a'){printDatabase(info->listNumerical());}
                        else {printDatabase(info->listNumericalReverse());}
                    }
                } 
                //stops the program
                else if (response == 'q'){
                   mvwprintw(win, 1,1, "Have a great day!! --dee.nah");
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
                //if the case where the user does not respond correctly
                else{mvwprintw(win, 1, 1, "Sorry, Your response is invalid, please try again: ");}
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

            box(win, 0, 0);
            mvwprintw(win, 1, 1, "Main Menu: ");
            mvwprintw(win, 3, 1, "(A)dd a manga.");
            mvwprintw(win, 4, 1, "(D)elete a manga.");
            mvwprintw(win, 5, 1, "(L)ist mangas.");
            mvwprintw(win, 6, 1, "(Q)uit.");
            mvwprintw(win, 8, 1, "Enter the letter of your choice: ");
            wrefresh(win);

            int response = wgetch(win);
            
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
            /*
            for (int pos = 0; pos < mangaList.size(); pos ++){
                mvwprintw(win, pos*15 + 1, 1, "Entry #" + to_string(pos+1));
                mvwprintw(win, pos*15 + 2, 1,"=========================================");
                mvwprintw(win, pos*15 + 3, 1, "Name: " + mangaList.at(pos).getName() + "." );

                mvwprintw(win, pos*15 + 4, 1, "Genres: ");
                vector<string> genres = mangaList.at(pos).getGenres();
                int rowPos = 9;
                for (int i = 0; i < genres.size() - 1; i++){
                    mvwprintw(win, pos*15 + 4, rowPos, genres.at(i) + ", ");
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

                mvwprintw(win, pos*15 + 7, 1, "Year of release: " 
                          + mangaList.at(pos).getYear() + ".");
            }
            wrefresh(win);
            */
        }

        //adds an entry
        void addEntry(){
            mvwprintw(win, 1, 1, "You are currently: adding an entry. ");
            mvwprintw(win, 1, 38, "Enter \"exit\" if you change your mind."); 
            wrefresh(win);

            mvwprintw(win, 1, 1, "Enter the manga name: ");
            wrefresh(win);
            
            string name;
            cin.ignore();
            getline (cin, name);
            if (name == "exit"){return;}

            mvwprintw(win, 1, 1, "Enter the manga authors one at a time. " );
            mvwprintw(win, 1, 39, "Enter \"stop\" to stop: ");
            wrefresh(win);

            string entry = "";
            vector<string> authors;
            while (true){
                //cout << "Enter an author: \n";
                mvwprintw(win, 1, 1, "Enter an author: ");
                wrefresh(win);

                getline (cin, entry);
                if (entry == "exit"){return;}
                else if (toLowerStr(entry) == "stop"){break;}
                authors.push_back(entry);}
                    
            mvwprintw(win, 1, 1, "Enter the manga genres one at a time. " );
            mvwprintw(win, 1, 39, "Enter \"stop\" to stop: ");
            wrefresh(win);

            vector<string> genres;
            while (true){
                // cout << "Enter a genre: \n";
                mvwprintw(win, 1, 1, "Enter a genre: ");
                wrefresh(win);

                getline (cin, entry);
                if (entry == "exit"){return;}
                else if (toLowerStr(entry) == "stop"){break;}
                genres.push_back(entry);}

            bool isReleasing;
            while (true){
                mvwprintw(win, 1, 1, "Is this manga still releasing? ");
                mvwprintw(win, 1, 32,"Enter (Y)es or (N)o: ");
                                        
                wrefresh(win);

                cin >> entry;
                if (entry == "exit"){return;}
                if (toLowerStr (entry) == "y"){
                    isReleasing = true;
                    break;}
                else if (toLowerStr (entry) == "n"){
                    isReleasing = false;
                    break;}}

            mvwprintw(win, 1, 1, "Enter the manga year of release: ");
            wrefresh(win);

            string year;
            cin >> year;
            while (!realNum (year)){
                if (year == "exit"){return;}
                mvwprintw(win, 1, 1, "That is not a valid year, please try again.");
                wrefresh(win);
                cin >> year;}

            single_record newRecord (name, authors, genres, isReleasing, stoi(year));
            info->add_entry (newRecord);

            mvwprintw(win, 1, 1, "You have successfully entered a new entry.");
            wrefresh(win);
        }

        ~menu(){
            delete info;
            endwin();}
    
    private:
        int response;
        int xMax, yMax;
        WINDOW *win;
        database *info = new database("database.txt");
};
