//Menu class

#include "Menu.h"
#include "Database.h"
#include "Manga_Record.h"
#include <vector>
#include <string>
#include <fstream>
#include <ncurses.h>
using namespace std;

//default and only constructor
Menu::Menu(){

    info = new Database;
    initscr();
    noecho();
    
    getmaxyx(stdscr, yMax, xMax);

    refresh();

    start_color();

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);

    attron(COLOR_PAIR(1));
    mvaddstr(yMax/4-5, xMax/4-15, "Welcome to the Manga Database!");
    mvaddstr(yMax/4-3, xMax/4-19, "--------------------------------------");
    char stop = 'z';
    while (stop != 'x'){
        attron(COLOR_PAIR(3));
        mvaddstr(yMax/4-1,xMax/4-10, "Press \'x\' to continue");
        refresh();
        stop = tolower(getch());
    }

    response = 'p';
    //continues until user selects quit
    while (response != 'q'){
        erase();
        refresh();
        printMenu();
        //adding a manga into the database
        if (response == 'a')
        {
            addEntry();
        }
        //finding a manga by its name or year of release in the database
        else if (response == 'f')
        {
            attron(COLOR_PAIR(1));
            mvaddstr(1, 1, "You are currently: finding an entry.");
    

            attron(COLOR_PAIR(3));
            mvaddstr(3, 1, "You can search by:");
            attroff( COLOR_PAIR(3));

            attron(COLOR_PAIR(2));
            mvaddstr(5, 1, "(N)ame of manga");
            mvaddstr(6, 1, "(G)enre of manga");
            mvaddstr(7, 1, "(A)uthor of manga");
            mvaddstr(8, 1, "(S)tatus of manga");
            mvaddstr(9, 1, "(Y)ear of release");

            mvaddstr(11, 1, "(R)eturn to main menu");

            attroff(COLOR_PAIR(2));

            attron(COLOR_PAIR(3));
            mvaddstr(13, 1, "Enter the letter of your choice:");

            refresh();

            char input = tolower(getch());
            while (input != 'n'&& input != 'g' && input != 'a' &&
                   input != 's' && input != 'y' && input != 'r')
            {
                mvaddstr(15, 1, "Your response is invalid, please try again: ");
                refresh();
                input = tolower(getch());
            }

            erase();
            attroff(COLOR_PAIR(3));
            refresh();

            if (input == 'n')
            {   
                attron(COLOR_PAIR(3));
                echo();
                mvaddstr(1, 1, "Are you searching for (K)ey words or the (T)itle itself?");
                refresh();
                char res = tolower(getch());
                while (res != 'k' && res != 't')
                {
                    attron(COLOR_PAIR(1));
                    mvaddstr(3, 1, "Your response is invalid, please try again: ");
                    refresh();
                    res = tolower(getch());
                }
                erase();
                refresh();
                vector<Manga_Record> searchResults = {};
                if (res == 't'){
                    mvaddstr(1, 1, "Enter the exact name of the manga: ");
                    char mangaName[200];
                    getnstr(mangaName, 190);
                    erase();
                    refresh();
                    searchResults = info->searchByExactName(mangaName);
                }
                else if (res == 'k'){
                    mvaddstr(1, 1, "Enter a key word of the manga: ");
                    char mangaName[200];
                    getnstr(mangaName,190);
                    erase();
                    searchResults = info->searchBySubName(mangaName);
                }
                attroff(COLOR_PAIR(3));
                noecho();
                if (searchResults.size() != 0)
                {
                    printDatabase(searchResults);
                    erase();
                    refresh();
                }
                else {
                    attron(COLOR_PAIR(1));
                    mvaddstr(1, 1, "Unfortunately, your input yielded no results.");
                    char stop = 'z';
                    while (stop != 'x'){
                        attron(COLOR_PAIR(3));
                        mvaddstr(3,1,"Press \'x\' to continue");
                        refresh();
                        stop = tolower(getch());
                    }
                    attroff(COLOR_PAIR(3));
                }
            }

            else if (input == 'g')
            {
                attron( COLOR_PAIR(3));
                mvaddstr(1, 1, "Enter the genre you are searching for: ");
                echo();
                char mangaName[200];
                getnstr(mangaName,190);
                erase();
                noecho();
                if (info->searchByGenre(mangaName).size() != 0)
                {
                    attroff(COLOR_PAIR(3));
                    printDatabase(info->searchByGenre(mangaName));
                    erase();
                    refresh();
                }
                else
                {
                    attroff(COLOR_PAIR(3));
                    attron(COLOR_PAIR(2));
                    mvaddstr(1,1, "Sorry we could not find that genre.");
                    char stop = 'z';
                    while (stop != 'x'){
                        mvaddstr(3,1,"Press \'x\' to continue");
                        refresh();
                        stop = tolower(getch());
                    }
                    attroff(COLOR_PAIR(2));
                }
            }

            else if (input == 'a')
            {
                attron(COLOR_PAIR(3));
                mvaddstr(1, 1, "Enter the author you are searching for: ");
                echo();
                char mangaName[200];
                getnstr(mangaName,190);
                erase();
                noecho();
                if (info->searchByAuthor(mangaName).size() != 0)
                {
                    attroff(COLOR_PAIR(3));
                    printDatabase(info->searchByAuthor(mangaName));
                    erase();
                    refresh();
                }
                else
                {
                    attroff(COLOR_PAIR(3));
                    attron(COLOR_PAIR(2));
                    mvaddstr(1,1, "Sorry we could not find that author.");
                    char stop = 'z';
                    while (stop != 'x'){
                        mvaddstr(3,1,"Press \'x\' to continue");
                        refresh();
                        stop = tolower(getch());
                    }
                    attroff(COLOR_PAIR(2));
                }
            }

            else if (input == 's')
            {
                attron(COLOR_PAIR(3));
                mvaddstr(1, 1, "Are you searching for (C)ompleted or (I)n Progress mangas: ");
                refresh();
                input = tolower(getch());
                attroff(COLOR_PAIR(3));
                while (input != 'c' && input != 'i')
                {
                    attron(COLOR_PAIR(1));
                    mvaddstr(3, 1, "Your response is invalid, please try again: ");
                    input = tolower(getch());
            
                }
                erase();
                if (input == 'c'){printDatabase(info->searchByStatus(false));}
                else {printDatabase(info->searchByStatus(true));}
            }

            else if (input == 'y')
            {
                attron(COLOR_PAIR(3));
                mvaddstr(1, 1, "Are you searching for a (S)pecific year or a (R)ange:");
                refresh();
                input = tolower(getch());
                while (input != 's' && input != 'r')
                {
                    attron(COLOR_PAIR(1));
                    mvaddstr(3, 1, "Your response is invalid, please try again: ");
                    refresh();
                    input = tolower(getch());
                }
        
                attroff(COLOR_PAIR(3));

                if (input == 's')
                {
                    erase();
                    attron(COLOR_PAIR(3));
                    echo();
                    mvaddstr(1, 1, "What year are you looking for? ");
                    char year[10];
                    getnstr(year,9);
                    while (!realNum(year))
                    {
                        erase();
                        attron(COLOR_PAIR(1));
                        mvaddstr(1, 1, "That is not a valid year, please try again: ");
                        refresh();
                        getnstr(year,9);
                    }
                    printDatabase(info->searchByYear(stoi(string(year))));
                    erase();
                    refresh();
                    noecho();
                }

                else
                {   echo();
                    erase();
                    char startYear[10];
                    char endYear[10];
                    attron(COLOR_PAIR(3));
                    mvaddstr(1, 1, "Enter the starting year: ");
                    getnstr(startYear,9);
                    while (!realNum(startYear))
                    {
                        erase();
                        attron(COLOR_PAIR(1));
                        mvaddstr(1, 1, "That is not a valid year, please try again: ");
                        refresh();
                        getnstr(startYear,9);
                    }
                    attron(COLOR_PAIR(3));
                    mvaddstr(4, 1, "Enter the ending year: ");
                    getnstr(endYear,9);
                    while (!realNum(endYear))
                    {
                        erase();
                        attron(COLOR_PAIR(1));
                        mvaddstr(1, 1, "That is not a valid year, please try again: ");
                        refresh();
                        getnstr(endYear,9);
                    }
                    erase();
                    refresh();
                    noecho();
                    if (!((stoi(string(endYear))) > stoi(string(startYear)))){
                        attron(COLOR_PAIR(1));
                        erase();
                        mvaddstr(1, 1, "That is not a valid range. Returning to main menu.");
                        char stop = 'z';
                        while (stop != 'x'){
                            attron(COLOR_PAIR(3));
                            mvaddstr(3, 1,"Press \'x\' to continue");
                            refresh();
                            stop = tolower(getch());
                        }
                        erase();
                        refresh();
                    }
                    else{
                        int begYear = stoi(string(startYear));
                        int lastYear = stoi(string(endYear));
                        printDatabase(info->searchByYear(begYear,lastYear));
                        erase();
                        refresh();
                    }
                }
            }
        }
        //delete a manga by its name or year of release in the database
        else if (response == 'd')
        {
            attron(COLOR_PAIR(1));
            mvaddstr(1, 1, "You are currently: deleting an entry.");
            attron(COLOR_PAIR(2));
            mvaddstr(3, 1, "You can delete by: ");
            mvaddstr(5, 1, "(N)ame of manga");
            mvaddstr(6, 1, "(Y)ear of release");
            mvaddstr(8, 1, "(R)eturn to main menu");
            attron(COLOR_PAIR(3));
            mvaddstr(10, 1, "Enter the letter of your choice: ");
            refresh();

            char userResponse = tolower(getch());
            while (userResponse != 'n' && userResponse != 'y' && userResponse != 'r')
            {
                attron(COLOR_PAIR(1));
                mvaddstr(12, 1, "Your response is invalid, please try again: ");
                refresh();
                userResponse = tolower(getch());
            }

            erase();
            refresh();

            if (userResponse == 'n')
            {
                attron(COLOR_PAIR(3));
                echo();
                mvaddstr(1, 1, "Are you deleting certain (K)ey words or a (T)itle itself?");
                refresh();
                char res = tolower(getch());
                while (res != 'k' && res != 't')
                {
                    attron(COLOR_PAIR(1));
                    mvaddstr(3, 1, "Your response is invalid, please try again: ");
                    refresh();
                    res = tolower(getch());
                }
                erase();
                refresh();
                if (res == 't'){
                    mvaddstr(1, 1, "Enter the exact name of the manga: ");
                    char mangaName[200];
                    getnstr(mangaName,190);
                    erase();
                    refresh();
                    info->deleteByExactName(mangaName);
                }
                else if (res == 'k'){
                    mvaddstr(1, 1, "Enter a key word of the manga: ");
                    char mangaName[200];
                    getnstr(mangaName,190);
                    erase();
                    info->deleteBySubName(mangaName);
                }
                noecho();
            }

            else if (userResponse == 'y')
            {
                attron(COLOR_PAIR(3));
                mvaddstr(1, 1, "Are you deleting a (S)pecific year or a (R)ange: ");
                refresh();

                char userResponse = tolower(getch());
                while (userResponse != 's' && userResponse != 'r')
                {
                    erase();
                    attron(COLOR_PAIR(3));
                    noecho();
                    mvaddstr(1, 1, "Are you deleting a (S)pecific year or a (R)ange: ");
                    
                    attron(COLOR_PAIR(1));
                    mvaddstr(3, 1, "Your response is invalid, please try again: ");
                    refresh();
                    userResponse = tolower(getch());
                }
 
                erase();

                if (userResponse == 's')
                {
                    echo();
                    attron(COLOR_PAIR(3));
                    mvaddstr(1, 1, "What year are you looking for? ");
                    refresh();
                    char year[10];
                    getnstr(year,9);
                    while (!realNum(year))
                    {
                        erase();
                        attron(COLOR_PAIR(1));
                        mvaddstr(1, 1, "That is not a valid year, please try again: ");
                        refresh();
                        getnstr(year,9);
                    }
                    noecho();
                    info->deleteByYear(stoi(year));
                }

                else
                {
                    echo();
                    char startYear[10];
                    char endYear[10];
                    attron(COLOR_PAIR(3));
                    mvaddstr(1, 1, "Enter the starting year: ");
                    getnstr(startYear,9);
                    erase();
                    
                    while (!realNum(startYear))
                    {
                        attron(COLOR_PAIR(1));
                        mvaddstr(1, 1, "That is not a valid year, please try again: ");
                        refresh();
                        getnstr(startYear,9);
                        erase();
                        
                    }
                    mvaddstr(1, 1, "Enter the ending year: ");
                    getnstr(endYear,9);
                    while (!realNum(endYear))
                    {
                        attron(COLOR_PAIR(1));
                        erase();
                        
                        mvaddstr(1, 1, "That is not a valid year, please try again: ");
                        refresh();
                        getnstr(endYear,9);
                    }
                    erase();
                    
                    refresh();
                    noecho();
                    info->deleteByYear(stoi(string(startYear)), stoi(string((endYear))));
                }
            }
        }
        //list the database by alphbetical order or numerical order
        else if (response == 'l')
        {
            attron(COLOR_PAIR(1));
            mvaddstr(1, 1, "You are currently: listing entries.");
            attron(COLOR_PAIR(3));
            mvaddstr(3, 1, "You can list by: ");
            attron(COLOR_PAIR(2));
            mvaddstr(5, 1, "(N)ame of manga");
            mvaddstr(6, 1, "(A)uthor of manga");
            mvaddstr(7, 1, "(Y)ear of release");
            mvaddstr(9, 1, "(R)eturn to main menu");
            attron(COLOR_PAIR(3));
            mvaddstr(11, 1, "Enter the letter of your choice: ");
            refresh();

            char input = tolower(getch());
            while (input != 'n' && input != 'y' && input != 'r' && input != 'a')
            {
                attron(COLOR_PAIR(1));
                mvaddstr(13, 1, "Your response is invalid, please try again: ");
                refresh();
                input = tolower(getch());
            }

            erase();
            

            if (input == 'n' || input == 'a')
            {
                attron(COLOR_PAIR(3));
                mvaddstr(1, 1, "Did you want them listed in (A)lphabetical order or");
                mvaddstr(1, 52, " in (R)everse alphabetical order?: ");
                refresh();

                char userRes = tolower(getch());
                while (userRes != 'a' && userRes != 'r')
                {
                    attron(COLOR_PAIR(1));
                    mvaddstr(3, 1, "Your response is invalid, please try again: ");
                    refresh();
                    userRes = tolower(getch());
                }

                if (userRes == 'a' && input == 'n')
                {
                    printDatabase(info->listAlphabetical());
                }
                else if (userRes == 'a')
                {
                    printDatabase(info->listAuthor());
                }
                else if (userRes == 'r' && input == 'a')
                {
                    printDatabase(info->listAuthorReverse());
                }   
                else
                {
                    printDatabase(info->listAlphabeticalReverse());
                }
            }

            else if (input == 'y')
            {
                attron(COLOR_PAIR(3));
                mvaddstr(1, 1, "Did you want them listed in (A)scending order or");
                mvaddstr(1, 49, " in (D)escending order?: ");
                refresh();

                char userResponse = tolower(getch());
                while (userResponse != 'a' && userResponse != 'd')
                {
                    attron(COLOR_PAIR(1));
                    mvaddstr(3, 1, "Your response is invalid, please try again: ");
                    refresh();
                    userResponse = tolower(getch());
                }

                if (userResponse == 'a')
                {
                    printDatabase(info->listNumerical());
                }
                else
                {
                    printDatabase(info->listNumericalReverse());
                }
            }
        }
        //stops the program
        else if (response == 'q')
        {
            attron(COLOR_PAIR(1));
            mvaddstr(1, 1, "h");
            attron(COLOR_PAIR(2));
            mvaddstr(1, 2, "A");
            attron(COLOR_PAIR(3));
            mvaddstr(1, 3, "v");
            attron(COLOR_PAIR(1));
            mvaddstr(1, 4, "E");
            attron(COLOR_PAIR(2));
            mvaddstr(1, 6, "a");
            attron(COLOR_PAIR(3));
            mvaddstr(1, 8, "G");
            attron(COLOR_PAIR(1));
            mvaddstr(1, 9, "r");
            attron(COLOR_PAIR(2));
            mvaddstr(1, 10, "E");
            attron(COLOR_PAIR(3));
            mvaddstr(1, 11, "a");
            attron(COLOR_PAIR(1));
            mvaddstr(1, 12, "T");
            attron(COLOR_PAIR(2));
            mvaddstr(1, 14, "d");
            attron(COLOR_PAIR(3));
            mvaddstr(1, 15, "A");
            attron(COLOR_PAIR(1));
            mvaddstr(1, 16, "y");
            attron(COLOR_PAIR(2));
            mvaddstr(1, 17, "!");
            attron(COLOR_PAIR(3));
            mvaddstr(1, 18, "!");

            char stop = 'z';
            while (stop != 'x'){
                mvaddstr(3,1,"Press \'x\' to continue");
                refresh();
                stop = tolower(getch());
            }
            endwin();
            //creates a text file of the database
            ofstream dataFile("database.txt");
            //adds elements to the file
            string returnStr = "";
            vector<Manga_Record> file = info->getMangaList();
            for (int pos = 0; pos < file.size(); pos++)
            {
                Manga_Record record = file.at(pos);
                //add name
                returnStr = record.getName() + "|{";
                //add genres
                for (int gen = 0; gen < record.getGenres().size() - 1; gen++)
                {
                    returnStr += record.getGenres().at(gen) + ", ";
                }
                if (record.getGenres().size() > 0)
                {
                    returnStr += record.getGenres().at(record.getGenres().size() - 1);
                }
                returnStr += "}|{";
                //add authors
                for (int loc = 0; loc < record.getAuthors().size() - 1; loc++)
                {
                    returnStr += record.getAuthors().at(loc) + ", ";
                }
                if (record.getAuthors().size() > 0)
                {
                    returnStr += record.getAuthors().at(record.getAuthors().size() - 1);
                }
                returnStr += "}|";
                //add status and year
                if (record.getStatus())
                {
                    returnStr += "releasing|" + to_string(record.getYear());
                }
                else
                {
                    returnStr += "completed|" + to_string(record.getYear());
                }
                if (pos == file.size() - 1){dataFile << returnStr;}
                else{ dataFile << returnStr << endl;}
            }
            dataFile.close();
        }
        
        else
        {
            char stop = 'z';
            while (stop != 'x'){
                attron(COLOR_PAIR(1));
                mvaddstr(1, 1, "Please enter a valid option. Press \'x\' to continue.");
                refresh();
                stop = tolower(getch());
            }
        }
    }
}

//ensures that user input is actually a number
bool Menu::realNum(string userInput)
{
    for (int pos = 0; pos < userInput.length(); pos++)
    {
        if (!(userInput[pos] >= '0' && userInput[pos] <= '9'))
        {
            return false;
        }
    }
    if (stoi(userInput) > 2021 || stoi(userInput) < 1952)
    {
        return false;
    }

    return true;
}

//prints the available choices in Menu
void Menu::printMenu()
{   
    noecho();
    attron(COLOR_PAIR(1));
    mvaddstr(1, 1, "Main Menu: ");
    attron(COLOR_PAIR(2));
    mvaddstr(3, 1, "(A)dd a manga.");
    mvaddstr(4, 1, "(F)ind a manga");
    mvaddstr(5, 1, "(D)elete a manga.");
    mvaddstr(6, 1, "(L)ist mangas.");
    mvaddstr(7, 1, "(Q)uit.");
    attron(COLOR_PAIR(3));
    mvaddstr(9, 1, "Enter the letter of your choice: ");
    refresh();

    response = tolower(getch());
    erase();
    
    refresh();
}

//changes all characters in a string to lower case
string Menu::toLowerStr(string str)
{
    string returnStr = "";
    for (int pos = 0; pos < str.length(); pos++)
    {
        returnStr += tolower(str[pos]);
    }
    return returnStr;
}

//controls what entrys are displayed (user navigation)
void Menu::printDatabase(vector<Manga_Record> mangaList)
{
    char input = '0';
    int loc = 0;
    while (input != 'e')
    {
        input = printEntry(loc, mangaList);
        if (input == 'c')
        {
            if (loc != mangaList.size() - 1)
            {
                loc++;
            }
        }
        else if (input == 'z')
        {
            if (loc != 0)
            {
                loc--;
            }
        }
    }
}

//prints a single entry
char Menu::printEntry(int index, vector<Manga_Record> mangaList){
    erase();
    
    Manga_Record manga = mangaList.at(index);
    attron(COLOR_PAIR(1));
    mvaddstr(1, 1, "Entry #");
    mvaddstr(1, 8, to_string(index + 1).data());

    mvaddstr(2, 1, "=========================================");

    attron(COLOR_PAIR(3));
    mvaddstr( 3, 1, "Name: ");
    attron(COLOR_PAIR(2));
    mvaddstr( 3, 7, manga.getName().data());
    mvaddstr( 3, manga.getName().size() + 7, ".");

    attron(COLOR_PAIR(3));
    mvaddstr( 4, 1, "Genres: ");
    attron(COLOR_PAIR(2));
    int rowPos = 9;
    for (int i = 0; i < manga.getGenres().size() - 1; i++){
        mvaddstr( 4, rowPos, manga.getGenres().at(i).data());
        mvaddstr( 4, rowPos + manga.getGenres().at(i).length(), ", ");
        rowPos += manga.getGenres().at(i).length() + 2;
    }
    mvaddstr( 4, rowPos, manga.getGenres().at(manga.getGenres().size() - 1).data());
    mvaddstr( 4, rowPos + manga.getGenres().at(manga.getGenres().size() - 1).length(), ".");
        
    
    attron(COLOR_PAIR(3));
    mvaddstr( 5, 1, "Authors: ");
    attron(COLOR_PAIR(2));
    rowPos = 10;
    for (int i = 0; i < manga.getAuthors().size() - 1; i++){
        mvaddstr( 5, rowPos, manga.getAuthors().at(i).data());
        mvaddstr( 5, rowPos + manga.getAuthors().at(i).length(), ", ");
        rowPos += manga.getAuthors().at(i).length() + 2;
    }
    mvaddstr( 5, rowPos, manga.getAuthors().at(manga.getAuthors().size()-1).data());
    mvaddstr( 5, rowPos + manga.getAuthors().at(manga.getAuthors().size()-1).length(), ".");

    attron(COLOR_PAIR(3));
    mvaddstr(6, 1, "Status: ");
    attron(COLOR_PAIR(2));
    if (manga.getStatus() == true)
    {
        mvaddstr(6, 9, "Releasing.");
    }
    else
    {
        mvaddstr(6, 9, "Completed.");
    }

    attron(COLOR_PAIR(3));
    mvaddstr(7, 1, "Year of release: ");
    attron(COLOR_PAIR(2));
    string yearRel = to_string(manga.getYear());
    mvaddstr(7, 18, yearRel.data());

    attron(COLOR_PAIR(3));
    mvaddstr(9, 1, "Enter \'z\' to move backwards \'c\' to move forward and \'e\' to exit");
    refresh();
    char output = tolower(getch());
    while (output != 'z' && output != 'c' && output != 'e')
    {
        attron(COLOR_PAIR(1));
        mvaddstr(11, 1, "Enter a valid action: ");
        refresh();
        output = tolower(getch());
    }
    return output;
}

//adds an entry to the database
void Menu::addEntry()
{
    attron(COLOR_PAIR(1));
    mvaddstr(1, 1, "You are currently: adding an entry. ");

    attron(COLOR_PAIR(3));
    char name[200];
    echo();
    mvaddstr( 5, 1, "Enter \"exit\" if you change your mind. ");
    mvaddstr(3, 1, "Enter the manga name: ");

    refresh();
    getnstr(name,190);
    while (isIllegalName(string(name))){
        erase();
        
        attron(COLOR_PAIR(1));
        mvaddstr(1,1, "Invalid entry.");
        attron(COLOR_PAIR(3));
        mvaddstr( 5, 1, "Enter \"exit\" if you change your mind. ");
        mvaddstr(3, 1, "Enter the manga name: ");
        refresh();
        getnstr(name,190);
    }

    if (toLowerStr(deleteWhitespace(name)) == "exit")
    {
        return;
    }

    else
    {
        for (int pos = 0; pos < info->getMangaList().size(); pos++)
        {
            if (toLowerStr(info->getMangaList().at(pos).getName()) 
                == (toLowerStr(deleteWhitespace(name))))
            {
                erase();
                
                char stop = 'z';
                while (stop != 'x'){
                    attron(COLOR_PAIR(1));
                    mvaddstr(1, 1, "Entry already exists. Press \'x\' to return to menu.");
                    refresh();
                    stop = tolower(getch());
                    erase();
                    refresh();
                }   
                return;
            }
        }
    }

    erase();
    

    refresh();

    char entry[200];

    vector<string> authors = {};
    while (true)
    {
        erase();
        
        attron(COLOR_PAIR(1));
        mvaddstr(1, 1, "Enter the manga authors one at a time. ");
        mvaddstr(1, 39, " Enter \"stop\" to stop: ");
        attron(COLOR_PAIR(3));
        mvaddstr(3, 1, "Enter an author: ");
        refresh();

        getnstr(entry,99);
        if (toLowerStr(deleteWhitespace(string(entry))) == "exit")
        {
            return;
        }
        // (>^_^)># here's a waffle for your troubles
        else if (isIllegalVector(string(entry))){
            erase();
            
            char stop = 'z';
            while (stop != 'x'){
                attron(COLOR_PAIR(1));
                mvaddstr(1, 1, "Please enter a valid entry. Press \'x\' to continue.");
                refresh();
                 stop = tolower(getch());
            }  
        }
        else if (toLowerStr(deleteWhitespace(string(entry))) == "stop")
        {
            if (authors.size() != 0)
            {
                break;
            }
            else
            {
                erase();
                
                char stop = 'z';
                while (stop != 'x'){
                    attron(COLOR_PAIR(1));
                    mvaddstr(1, 1, "Please enter an author. Press \'x\' to continue.");
                    refresh();
                    stop = tolower(getch());
                }   
            }
        }
       else
        {
            authors.push_back(deleteWhitespace(entry));
        }
    }

    erase();
    

    refresh();

    vector<string> genres = {};
    while (true)
    {
        erase();
        

        attron(COLOR_PAIR(1));
        mvaddstr(1, 1, "Enter the manga genres one at a time. ");
        mvaddstr(3, 1, " Enter \"stop\" to stop: ");
        attron(COLOR_PAIR(3));
        mvaddstr(5, 1, "Enter a genre: ");
        refresh();

        getnstr(entry,99);
        if (toLowerStr(deleteWhitespace(string(entry))) == "exit")
        {
            return;
        }
        else if (isIllegalVector(string(entry))){
            erase();
            
            char stop = 'z';
            while (stop != 'x'){
                attron(COLOR_PAIR(1));
                mvaddstr(1, 1, "Please enter a genre. Press \'x\' to continue.");
                refresh();
                stop = tolower(getch());
            }  
        }
        else if 
        (toLowerStr(deleteWhitespace(string(entry))) == "stop")
        {
            if (genres.size() != 0)
            {
                break;
            }
            else
            {
                erase();
                
                char stop = 'z';
                while (stop != 'x'){
                    attron(COLOR_PAIR(1));
                    mvaddstr(1, 1, "Please enter a genre. Press \'x\' to continue.");
                    refresh();
                    stop = tolower(getch());
                }  
            }
        }
        else
        {
            genres.push_back(deleteWhitespace(entry));
        }
    }

    erase();
    

    bool isReleasing;
    attron(COLOR_PAIR(3));
    mvaddstr(1, 1, "Is this manga still releasing? ");
    noecho();
    mvaddstr(3, 1, "Enter (Y)es or (N)o or (E) to exit: ");

    refresh();

    char res = tolower(getch());
    while (res != 'n' && res != 'y' && res != 'e')
    {
        attron(COLOR_PAIR(1));
        mvaddstr(3, 1, "Your response is invalid, please try again: ");
        refresh();
        res = tolower(getch());
    }

    if (res == 'e')
    {
        return;
    }
    if (res == 'y')
    {
        isReleasing = true;
    }
    else if (res == 'n')
    {
        isReleasing = false;
    }

    erase();
    

    attron(COLOR_PAIR(3));
    echo();
    mvaddstr(1, 1, "Enter the manga year of release: ");
    refresh();

    char year[10];
    getnstr(year,9);
    while (!realNum(year))
    {
        if (string(year) == "exit"){return;}
        attron(COLOR_PAIR(1));
        mvaddstr(3, 1, "That is not a valid year, please try again: ");
        getnstr(year, 9);
    }

    Manga_Record newRecord(deleteWhitespace(name), authors, genres, isReleasing, stoi(year));

    erase();
    
    char stop = 'z';
    while (stop != 'x'){
        attron(COLOR_PAIR(3));
        mvaddstr(1, 1, "Are you sure you want to add this entry?");
        mvaddstr(3, 1, "Press \'x\' to continue.");
        refresh();
        stop = tolower(getch());
    }  

    erase();
    
    newRecord.printEntry();

    erase();
    
    mvaddstr(1, 1, "Confirm (Y)es or (N)o");
    attron(COLOR_PAIR(3));
    refresh();
    int userResponse = tolower(getch());
    while (userResponse != 'n' && userResponse != 'y')
    {
        attron(COLOR_PAIR(1));
        mvaddstr(3, 1, "Your response is invalid, please try again: ");
        refresh();
        userResponse = tolower(getch());
    }

    stop = 'z';
    erase();
    while (stop != 'x'){
        if (userResponse == 'y'){
            info->add_entry(newRecord);
            attron(COLOR_PAIR(3));
            mvaddstr(1, 1, "You have successfully entered a new entry.");
            mvaddstr(3, 1, "Press \'x\' to continue.");
            refresh();
            stop = tolower(getch());
        }else{
            attron(COLOR_PAIR(1));
            mvaddstr(1, 1, "You have cancelled entering an entry");
            mvaddstr(3, 1, "Press \'x\' to continue.");
            refresh();
            stop = tolower(getch());
        }
    } 

    erase();
    
    refresh();
}

// Mainly for deleting and adding, checks if strings are blank
bool Menu::isIllegalName(string input){

    if (input.length() == 0){return true;}
    // Checks for illegal characters
    if (input.find("|") != -1){
        return true;
    }
    for (char letter : input){
        if (letter != ' '){
            // If there is any character that is not equal to a space, return true
            return false;
        }
    }
    // If every character is a space, return true;
    return true;

}
// Checks if authors/genres is illegal
bool Menu::isIllegalVector(string input){

    if (input.length() == 0){return true;}
    // Checks for illegal characters
    if (input.find("|") != -1){
        return true;
    }
    if (input.find("{") != -1){
        return true;
    }
    if (input.find("}") != -1){
        return true;
    }
    if (input.find(",") != -1){
        return true;
    }
    for (char letter : input){
        if (letter != ' '){
            // If there is any character that is not equal to a space, return true
            return false;
        }
    }
    // If every character is a space, return true;
    return true;

}

// Deletes leading and trailing whitespace
string Menu::deleteWhitespace(string name){

    // Starts from beginning, finds first nonspace char
    int startingIndex = 0;
    for (int i = 0; i < name.size(); i++){
        if (name.at(i) != ' '){
            startingIndex = i;
            break;
        }
    }
    // Starts from ending, finds last nonspace char
    int endingIndex = 0;
    for (int i = name.size() - 1; i >= 0; i--){
        if (name.at(i) != ' '){
            endingIndex = i;
            break;
        }
    }

    return name.substr(startingIndex, endingIndex - startingIndex + 1);

}


Menu::~Menu(){
    delete info;
}