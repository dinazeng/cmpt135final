//menu class

#include "menu.h"
#include "database.h"
#include "manga_record.h"
#include <vector>
#include <string>
#include <ncurses.h>
using namespace std;

class menu{
    public:
        //default and only constructor
        menu(){
            initscr();
            mvprintw(1,1, "Welcome to the Manga Database!\n---------------------------------");
            char stop = getch();
            //continues until user selects quit
            while (response != 'q'){
                erase();
                refresh();
                printMenu();
                //adding a manga into the database
                if (response == 'a'){
                    addEntry();
                }
                //finding a manga by its name or year of release in the database
                else if (response == 'f'){
                    mvprintw(1, 1, "You are currently: finding an entry.");
                    mvprintw(3, 1, "You can search by:"); 
                    mvprintw(5, 1, "(N)ame of manga");
                    mvprintw(6, 1, "(Y)ear of release");
                    mvprintw(8, 1, "(R)eturn to main menu");   
                    mvprintw(10, 1,"Enter the letter of your choice:");
                    
                    refresh();
                    
                    int userResponse = getch();
                    while (userResponse != 'n' && userResponse != 'y' && userResponse != 'r'){
                        mvprintw(11, 1, "Your response is invalid, please try again: ");
                        refresh();
                        userResponse = getch();
                    }

                    erase();
                    refresh(); 

                    if(userResponse == 'n'){
                        mvprintw(1, 1, "Enter the name of the manga you are searching for: ");
                        char mangaName [100];
                        getstr(mangaName);
                        erase();
                        if (info->searchByName(mangaName).getName()!= "ERROR 404: NAME NOT FOUND"){ 
                            info->searchByName(mangaName).printEntry();
                            erase();
                            refresh();
                        }
                    }

                    else if (userResponse == 'y'){
                        mvprintw(1, 1, "Are you searching for a (S)pecific year or a (R)ange:");
                       userResponse = getch();
                        while (userResponse != 's' && userResponse != 'r'){
                            mvprintw(2, 1, "Your response is invalid, please try again: ");
                            userResponse = getch();
                        }
                        
                        if (userResponse == 's'){
                            erase();
                            mvprintw(1, 1, "What year are you looking for? ");
                            char year [10];
                            getstr(year);
                            while (!realNum (year)){
                                mvprintw(2, 1, "That is not a valid year, please try again: ");
                                getstr(year);
                            }
                            printDatabase(info->searchByYear(stoi(year)));
                            erase();
                            refresh();
                        }
                        
                        else{
                            erase();
                            char startYear[10];
                            char endYear [10];
                            mvprintw(1, 1, "Enter the starting year: ");
                            getstr(startYear);
                            while (!realNum (startYear)){
                                mvprintw(2, 1, "That is not a valid year, please try again: ");
                                getstr(startYear);
                            }
                            mvprintw(4, 1, "Enter the ending year: ");
                            getstr(endYear);
                            while (!realNum (endYear)){
                                mvprintw(5, 1, "That is not a valid year, please try again: ");
                                getstr(endYear);}
                            printDatabase(info -> searchByYear(stoi(startYear), stoi(endYear)));
                            erase();
                            refresh();
                        }
                    }
                }
                //delete a manga by its name or year of release in the database
                else if (response == 'd'){
                    mvprintw(1, 1, "You are currently: deleting an entry.");
                    mvprintw(3, 1, "You can delete by: ");
                    mvprintw(5, 1, "(N)ame of manga");
                    mvprintw(6, 1, "(Y)ear of release");
                    mvprintw(8, 1, "(R)eturn to main menu");
                    mvprintw(10, 1, "Enter the letter of your choice: ");
                    refresh();
                    
                    char userResponse = getch();
                    while (userResponse != 'n' && userResponse != 'y' && userResponse != 'r'){
                        mvprintw(12, 1, "Your response is invalid, please try again: ");
                        refresh();
                        userResponse = getch();
                    }
                    
                    erase();
                    refresh();

                    if(userResponse == 'n'){
                        mvprintw(1, 1, "Enter the name of the manga you are deleting: ");
                        refresh();
                        char mangaName[100];
                        getstr(mangaName);
                        erase();
                        info-> deleteByName(mangaName);
                    }

                    else if (userResponse == 'y'){
                        mvprintw(1, 1, "Are you deleting a (S)pecific year or a (R)ange: ");
                        refresh();

                        char userResponse = getch();
                        while (userResponse != 's' && userResponse != 'r'){
                            mvprintw(2, 1, "Your response is invalid, please try again: ");
                            refresh();
                            userResponse = getch();
                        }

                        if (userResponse == 's'){
                            erase();
                            mvprintw(1, 1, "What year are you looking for? ");
                            refresh();
                            char year [10];
                            getstr(year);
                            while (!realNum (year)){
                                mvprintw(2, 1, "That is not a valid year, please try again: ");
                                getstr(year);
                            }
                            info->deleteByYear(stoi(year));
                        }
                        
                        else{
                            erase();
                            char startYear[10];
                            char endYear [10];
                            mvprintw(1, 1, "Enter the starting year: ");
                            getstr(startYear);
                            while (!realNum (startYear)){
                                mvprintw(2, 1, "That is not a valid year, please try again: ");
                                getstr(startYear);
                            }
                            mvprintw(4, 1, "Enter the starting year: ");
                            getstr(endYear);
                            while (!realNum (endYear)){
                                mvprintw(5, 1, "That is not a valid year, please try again: ");
                                getstr(endYear);}
                            info -> deleteByYear(stoi(startYear), stoi(endYear));
                        }
                    }
                }
                //list the database by alphatical order or numerical order
                else if (response == 'l'){
                    mvprintw(1, 1, "You are currently: listing entries.");
                    mvprintw(3, 1, "You can list by: ");
                    mvprintw(5, 1, "(N)ame of manga");
                    mvprintw(6, 1, "(Y)ear of release");
                    mvprintw(8, 1, "(R)eturn to main menu");
                    mvprintw(10, 1, "Enter the letter of your choice: ");
                    refresh();
                    
                    int userResponse = getch();
                    while (userResponse != 'n' && userResponse != 'y' && userResponse != 'r'){
                        mvprintw(11, 1, "Your response is invalid, please try again: ");
                        refresh();
                        userResponse = getch();
                    }

                    erase();

                    if(userResponse == 'n'){
                        mvprintw(1,1, "Did you want them listed in (A)lphabetical order or"); 
                        mvprintw(1, 52, " in (R)everse alphabetical order?: ");   
                        refresh();
                        
                        char userResponse = getch();
                        while (userResponse != 'a' && userResponse != 'r'){
                            mvprintw(2, 1, "Your response is invalid, please try again: ");
                            refresh();
                            userResponse = getch();
                        }
                        
                        if (userResponse == 'a'){printDatabase(info->listAlphabetical());}
                        else {printDatabase(info->listAlphabeticalReverse());}
                    }

                    else if (userResponse == 'y'){
                        mvprintw(1, 1, "Did you want them listed in (A)scending order or");
                        mvprintw(1, 49, " in (D)escending order?: ");
                        refresh();

                        char userResponse = getch();
                        while (userResponse != 'a' && userResponse != 'd'){
                            mvprintw(2, 1, "Your response is invalid, please try again: ");
                            refresh();
                            userResponse = getch();
                        }
                        
                        if (userResponse == 'a'){printDatabase(info->listNumerical());}
                        else {printDatabase(info->listNumericalReverse());}
                    }
                } 
                //stops the program
                else if (response == 'q'){
                    mvprintw(1,1, "Have a great day!!");
                    char stop = getch();
                    endwin();
                    //creates a text file of the database
                    ofstream dataFile("database.txt");
                    //adds elements to the file
                    string returnStr = "";
                    vector <manga_record> file = info->getMangaList();
                    for (int pos = 0; pos < file.size(); pos++){
                        manga_record record = file.at(pos);
                        //add name
                        returnStr = record.getName() + "|{";
                        //add genres
                        for (int gen = 0; gen < record.getGenres().size() - 1; gen++){
                            returnStr += record.getGenres().at(gen) + ", ";}
                        if (record.getGenres().size() > 0){
                            returnStr += record.getGenres().at(record.getGenres().size()-1);}
                        returnStr += "}|{";
                        //add authors
                        for (int loc = 0; loc < record.getAuthors().size() - 1; loc++){
                            returnStr += record.getAuthors().at(loc) + ", ";}
                        if (record.getAuthors().size() > 0){
                            returnStr += record.getAuthors().at(record.getAuthors().size()-1);
                        }
                        returnStr += "}|";
                        //add status and year
                        if(record.getStatus()){
                            returnStr += "releasing|" + to_string(record.getYear());}
                        else {returnStr += "completed|" + to_string(record.getYear());}
                        dataFile << returnStr << endl;
                    }
                    dataFile.close();
                }
                else {
                    mvprintw(1,1, "Please enter a valid option. Press any key to continue.");
                    char stop = getch();
                }
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
            mvprintw(0, 1, "Main Menu: ");
            mvprintw(2, 1, "(A)dd a manga.");
            mvprintw(3, 1, "(F)ind a manga");
            mvprintw(4, 1, "(D)elete a manga.");
            mvprintw(5, 1, "(L)ist mangas.");
            mvprintw(6, 1, "(Q)uit.");
            mvprintw(8, 1, "Enter the letter of your choice: ");
            refresh();

            response = getch();
            move(0,0);
            erase();
            refresh();
        }
        
        //changes all characters in a string to lower case
        string toLowerStr (string str){
            string returnStr = "";
            for (int pos = 0; pos < str.length(); pos++){
                returnStr += tolower(str[pos]);}
            return returnStr;
        }

         //prints all elements in a vector
        void printDatabase(vector <manga_record> mangaList){
            char input = '0';
            int loc = 0;
            while (input != 'e'){
                input = printEntry(loc, mangaList);
                if (input == 'c'){
                    if (loc != mangaList.size() - 1){loc++;}
                }
                else if (input == 'z' ){
                    if (loc != 0){loc--;}
                }
            }
        }

        //print a single entry
        char printEntry(int index, vector <manga_record> mangaList){
            erase();
            manga_record manga = mangaList.at(index);
            mvprintw(1, 1, "Entry #");
            char entry[to_string(index).length()];
            for (int n = 0; n < 3; n++){entry[n] = to_string(index +1)[n];}
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
            
            mvprintw(9,1, "Enter \'z\' to move backwards \'c\' to move forward and \'e\' to exit");
            refresh();
            char output = getch();
            while ( output!= 'z'&& output!= 'c' && output!= 'e'){
                mvprintw(11, 1, "Enter a valid action: ");
                refresh();
                output = getch();
            }
            return output;
        }

        void addEntry(){
            mvprintw (1, 1, "You are currently: adding an entry. ");
            mvprintw (1, 37, "Enter \"exit\" if you change your mind."); 
            refresh();

            mvprintw (3, 1, "Enter the manga name: ");
            refresh();
            
            char name [100];
            getstr(name);
            if (toLowerStr(name) == "exit"){return;}
            else{
                for (int pos = 0; pos < info->getMangaList().size(); pos++){
                    if(info->getMangaList().at(pos).getName() == name){
                        erase();
                        mvprintw(1, 1, "Entry already exists. Returning to main menu");
                        refresh();
                        int stop = getch();
                        return;
                    }
                }
            }

            erase();

            char entry [100];
            refresh();

            vector<string> authors = {};
            while (true){
                erase();
                mvprintw (1, 1, "Enter the manga authors one at a time. " );
                mvprintw (1, 39, " Enter \"stop\" to stop: ");
                mvprintw (3, 1, "Enter an author: ");
                refresh();

                getstr (entry);
                if (toLowerStr(entry) == "exit"){return;}
                else if (toLowerStr(entry) == "stop"){
                    if(authors.size() != 0){break;}
                    else{
                        erase();
                        mvprintw(1,1,"Please enter an author. Press any key to continue.");
                        refresh();
                        char stop = getch();
                    }
                }
                else{authors.push_back(entry);};
            }

            erase();               
            
            refresh();

            vector<string> genres = {};
            while (true){
                erase();
                mvprintw(1, 1, "Enter the manga genres one at a time. ");
                mvprintw (1, 39, " Enter \"stop\" to stop: ");
                mvprintw (3, 1, "Enter a genre: ");
                refresh();

                getstr (entry);
                if (entry == "exit"){return;}
                else if (toLowerStr(entry) == "stop"){
                    if(genres.size() != 0){break;}
                    else{
                        erase();
                        mvprintw(1,1,"Please enter a genre. Press any key to continue");
                        refresh();
                        char stop = getch();
                    }
                }
                else{genres.push_back(entry);}
                }
            
            erase();

            bool isReleasing;
            mvprintw (1, 1, "Is this manga still releasing? ");
            mvprintw (1, 32,"Enter (Y)es or (N)o or (E) to exit: ");
                                        
            refresh();

            char res = getch();
            while (res != 'n' && res != 'y' && res != 'e'){
                mvprintw(3, 1, "Your response is invalid, please try again: ");
                refresh();
                res = getch();
            }

            if (res == 'e'){return;}
            if (res == 'y'){isReleasing = true;}
            else if (res == 'n'){isReleasing = false;}

            erase();

            mvprintw (1, 1, "Enter the manga year of release: ");
            refresh();

            char year [10];
            getstr(year);
            while (!realNum (year)|| year == "exit"){
                if (year == "exit"){return;}
                mvprintw(2, 1, "That is not a valid year, please try again: ");
                getstr(year);
            }

            manga_record newRecord (name, authors, genres, isReleasing, stoi(year));
            
            erase();
            mvprintw(1, 1, "Are you sure you want to add this entry? Press any key to continue.");
            
            char c = getch();
            refresh();

            erase();
            newRecord.printEntry();
            
            erase();
            mvprintw(1, 1, "Confirm (Y)es or (N)o");
            int userResponse = getch();
            while (userResponse != 'n' && userResponse != 'y'){
                mvprintw(3, 1, "Your response is invalid, please try again: ");
                refresh();
                userResponse = getch();
            }

            erase();
            if (userResponse == 'y'){
                info->add_entry (newRecord);

                mvprintw (1, 1, "You have successfully entered a new entry.");
                refresh();
            }
            else{mvprintw(1,1, "You have cancelled entering an entry");}
            erase();
            refresh();
        }

        ~menu(){delete info;}
    
    private:
        char response;
        database *info = new database("database.txt");
};