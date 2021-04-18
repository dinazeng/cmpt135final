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
    win = newwin(yMax*0.75, xMax*0.75,0, 0);
    box(win, 0, 0);
    refresh();

    start_color();

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);

    wattron(win, COLOR_PAIR(1));
    mvwprintw(win,yMax*3/8-5, xMax*3/8-15, "Welcome to the Manga Database!");
    mvwprintw(win, yMax*3/8-3, xMax*3/8-19, "--------------------------------------");
    char stop = 'z';
    while (stop != 'x'){
        wattron(win, COLOR_PAIR(3));
        mvwprintw(win,yMax*3/8-1,xMax*3/8-10,"Press \'x\' to continue");
        wrefresh(win);
        stop = tolower(getch());
    }

    response = 'p';
    //continues until user selects quit
    while (response != 'q'){
        werase(win);
        box(win,0,0);
        wrefresh(win);
        printMenu();
        //adding a manga into the database
        if (response == 'a')
        {
            addEntry();
        }
        //finding a manga by its name or year of release in the database
        else if (response == 'f')
        {
            wattron(win, COLOR_PAIR(1));
            mvwprintw(win,1, 1, "You are currently: finding an entry.");
    

            wattron(win, COLOR_PAIR(3));
            mvwprintw(win,3, 1, "You can search by:");
            wattroff(win, COLOR_PAIR(3));

            wattron(win, COLOR_PAIR(2));
            mvwprintw(win,5, 1, "(N)ame of manga");
            mvwprintw(win,6, 1, "(G)enre of manga");
            mvwprintw(win,7, 1, "(A)uthor of manga");
            mvwprintw(win,8, 1, "(S)tatus of manga");
            mvwprintw(win,9, 1, "(Y)ear of release");

            mvwprintw(win,11, 1, "(R)eturn to main menu");

            wattroff(win, COLOR_PAIR(2));

            wattron(win, COLOR_PAIR(3));
            mvwprintw(win,13, 1, "Enter the letter of your choice:");

            wrefresh(win);

            char input = tolower(getch());
            while (input != 'n'&& input != 'g' && input != 'a' &&
                   input != 's' && input != 'y' && input != 'r')
            {
                mvwprintw(win,15, 1, "Your response is invalid, please try again: ");
                wrefresh(win);
                input = tolower(getch());
            }

            werase(win);
            wattroff(win, COLOR_PAIR(3));
            box(win,0,0);
            wrefresh(win);

            if (input == 'n')
            {   
                wattron(win, COLOR_PAIR(3));
                echo();
                mvwprintw(win,1, 1, "Are you searching for (K)ey words or the (T)itle itself?");
                wrefresh(win);
                char res = tolower(getch());
                while (res != 'k' && res != 't')
                {
                    wattron(win, COLOR_PAIR(1));
                    mvwprintw(win,3, 1, "Your response is invalid, please try again: ");
                    wrefresh(win);
                    res = tolower(getch());
                }
                werase(win);
                box(win,0,0);
                wrefresh(win);
                vector<Manga_Record> searchResults = {};
                if (res == 't'){
                    mvwprintw(win,1, 1, "Enter the exact name of the manga: ");
                    char mangaName[100];
                    wgetstr(win, mangaName);
                    werase(win);
                    box(win,0,0);
                    wrefresh(win);
                    searchResults = info->searchByExactName(mangaName);
                }
                else if (res == 'k'){
                    mvwprintw(win,1, 1, "Enter a key word of the manga: ");
                    char mangaName[100];
                    wgetstr(win, mangaName);
                    werase(win);
                    box(win,0,0);
                    searchResults = info->searchBySubName(mangaName);
                }
                wattroff(win, COLOR_PAIR(3));
                noecho();
                if (searchResults.size() != 0)
                {
                    printDatabase(searchResults);
                    werase(win);
                    wrefresh(win);
                }
                else {
                    wattron(win, COLOR_PAIR(1));
                    mvwprintw(win,1, 1, "Unfortunately, your input yielded no results.");
                    char stop = 'z';
                    while (stop != 'x'){
                        wattron(win, COLOR_PAIR(3));
                        mvwprintw(win,3,1,"Press \'x\' to continue");
                        wrefresh(win);
                        stop = tolower(getch());
                    }
                    wattroff(win, COLOR_PAIR(3));
                }
            }

            else if (input == 'g')
            {
                wattron(win, COLOR_PAIR(3));
                mvwprintw(win,1, 1, "Enter the genre you are searching for: ");
                echo();
                char mangaName[100];
                wgetstr(win, mangaName);
                werase(win);
                box(win,0,0);
                noecho();
                if (info->searchByGenre(mangaName).size() != 0)
                {
                    wattroff(win, COLOR_PAIR(3));
                    printDatabase(info->searchByGenre(mangaName));
                    werase(win);
                    box(win,0,0);
                    wrefresh(win);
                }
                else
                {
                    wattroff(win, COLOR_PAIR(3));
                    wattron(win, COLOR_PAIR(2));
                    mvwprintw(win,1,1, "Sorry we could not find that genre.");
                    char stop = 'z';
                    while (stop != 'x'){
                        mvwprintw(win,3,1,"Press \'x\' to continue");
                        wrefresh(win);
                        stop = tolower(getch());
                    }
                    wattroff(win, COLOR_PAIR(2));
                }
            }

            else if (input == 'a')
            {
                wattron(win, COLOR_PAIR(3));
                mvwprintw(win,1, 1, "Enter the author you are searching for: ");
                echo();
                char mangaName[100];
                wgetstr(win, mangaName);
                werase(win);
                box(win,0,0);
                noecho();
                if (info->searchByAuthor(mangaName).size() != 0)
                {
                    wattroff(win, COLOR_PAIR(3));
                    printDatabase(info->searchByAuthor(mangaName));
                    werase(win);
                    box(win,0,0);
                    wrefresh(win);
                }
                else
                {
                    wattroff(win, COLOR_PAIR(3));
                    wattron(win, COLOR_PAIR(2));
                    mvwprintw(win,1,1, "Sorry we could not find that author.");
                    char stop = 'z';
                    while (stop != 'x'){
                        mvwprintw(win,3,1,"Press \'x\' to continue");
                        wrefresh(win);
                        stop = tolower(getch());
                    }
                    wattroff(win, COLOR_PAIR(2));
                }
            }

            else if (input == 's')
            {
                wattron(win, COLOR_PAIR(3));
                mvwprintw(win,1, 1, "Are you searching for (C)ompleted or (I)n Progress mangas: ");
                wrefresh(win);
                input = tolower(getch());
                wattroff(win, COLOR_PAIR(3));
                while (input != 'c' && input != 'i')
                {
                    wattron(win, COLOR_PAIR(1));
                    mvwprintw(win,3, 1, "Your response is invalid, please try again: ");
                    input = tolower(getch());
            
                }
                werase(win);
                box(win,0,0);
                if (input == 'c'){printDatabase(info->searchByStatus(false));}
                else {printDatabase(info->searchByStatus(true));}
            }

            else if (input == 'y')
            {
                wattron(win, COLOR_PAIR(3));
                mvwprintw(win,1, 1, "Are you searching for a (S)pecific year or a (R)ange:");
                wrefresh(win);
                input = tolower(getch());
                while (input != 's' && input != 'r')
                {
                    wattron(win, COLOR_PAIR(1));
                    mvwprintw(win,3, 1, "Your response is invalid, please try again: ");
                    wrefresh(win);
                    input = tolower(getch());
                }
        
                wattroff(win, COLOR_PAIR(3));

                if (input == 's')
                {
                    werase(win);
                    box(win,0,0);
                    wattron(win, COLOR_PAIR(3));
                    echo();
                    mvwprintw(win,1, 1, "What year are you looking for? ");
                    char year[10];
                    wgetstr(win, year);
                    while (!realNum(year))
                    {
                        werase(win);
                        box(win,0,0);
                        wattron(win, COLOR_PAIR(1));
                        mvwprintw(win,1, 1, "That is not a valid year, please try again: ");
                        wrefresh(win);
                        wgetstr(win, year);
                    }
                    printDatabase(info->searchByYear(stoi(year)));
                    werase(win);
                    box(win,0,0);
                    wrefresh(win);
                    noecho();
                }

                else
                {   echo();
                    werase(win);
                    box(win,0,0);
                    char startYear[10];
                    char endYear[10];
                    wattron(win, COLOR_PAIR(3));
                    mvwprintw(win,1, 1, "Enter the starting year: ");
                    wgetstr(win, startYear);
                    while (!realNum(startYear))
                    {
                        werase(win);
                        box(win,0,0);
                        wattron(win, COLOR_PAIR(1));
                        mvwprintw(win,1, 1, "That is not a valid year, please try again: ");
                        wrefresh(win);
                        wgetstr(win, startYear);
                    }
                    wattron(win, COLOR_PAIR(3));
                    mvwprintw(win,4, 1, "Enter the ending year: ");
                    wgetstr(win, endYear);
                    while (!realNum(endYear))
                    {
                        werase(win);
                        box(win,0,0);
                        wattron(win, COLOR_PAIR(1));
                        mvwprintw(win,1, 1, "That is not a valid year, please try again: ");
                        wrefresh(win);
                        wgetstr(win, endYear);
                    }
                    werase(win);
                    wrefresh(win);
                    box(win,0,0);
                    noecho();
                    if (!((stoi(string(endYear))) > stoi(string(startYear)))){
                        wattron(win, COLOR_PAIR(1));
                        werase(win);
                        box(win,0,0);
                        mvwprintw(win,1, 1, "That is not a valid range. Returning to main menu.");
                        char stop = 'z';
                        while (stop != 'x'){
                            wattron(win, COLOR_PAIR(3));
                            mvwprintw(win,3, 1,"Press \'x\' to continue");
                            wrefresh(win);
                            stop = tolower(getch());
                        }
                        werase(win);
                        box(win,0,0);
                        wrefresh(win);
                    }
                    else{
                        printDatabase(info->searchByYear(stoi(startYear), stoi(endYear)));
                        werase(win);
                        box(win,0,0);
                        wrefresh(win);
                    }
                }
            }
        }
        //delete a manga by its name or year of release in the database
        else if (response == 'd')
        {
            wattron(win, COLOR_PAIR(1));
            mvwprintw(win,1, 1, "You are currently: deleting an entry.");
            wattron(win, COLOR_PAIR(2));
            mvwprintw(win,3, 1, "You can delete by: ");
            mvwprintw(win,5, 1, "(N)ame of manga");
            mvwprintw(win,6, 1, "(Y)ear of release");
            mvwprintw(win,8, 1, "(R)eturn to main menu");
            wattron(win, COLOR_PAIR(3));
            mvwprintw(win,10, 1, "Enter the letter of your choice: ");
            wrefresh(win);

            char userResponse = tolower(getch());
            while (userResponse != 'n' && userResponse != 'y' && userResponse != 'r')
            {
                wattron(win, COLOR_PAIR(1));
                mvwprintw(win,12, 1, "Your response is invalid, please try again: ");
                wrefresh(win);
                userResponse = tolower(getch());
            }

            werase(win);
            box(win,0,0);
            wrefresh(win);

            if (userResponse == 'n')
            {
                wattron(win, COLOR_PAIR(3));
                echo();
                mvwprintw(win,1, 1, "Are you deleting certain (K)ey words or a (T)itle itself?");
                wrefresh(win);
                char res = tolower(getch());
                while (res != 'k' && res != 't')
                {
                    wattron(win, COLOR_PAIR(1));
                    mvwprintw(win,3, 1, "Your response is invalid, please try again: ");
                    wrefresh(win);
                    res = tolower(getch());
                }
                werase(win);
                box(win,0,0);
                wrefresh(win);
                if (res == 't'){
                    mvwprintw(win,1, 1, "Enter the exact name of the manga: ");
                    char mangaName[100];
                    wgetstr(win, mangaName);
                    werase(win);
                    box(win,0,0);
                    wrefresh(win);
                    info->deleteByExactName(mangaName);
                }
                else if (res == 'k'){
                    mvwprintw(win,1, 1, "Enter a key word of the manga: ");
                    char mangaName[100];
                    wgetstr(win, mangaName);
                    werase(win);
                    box(win,0,0);
                    info->deleteBySubName(mangaName);
                }
                noecho();
            }

            else if (userResponse == 'y')
            {
                wattron(win, COLOR_PAIR(3));
                mvwprintw(win,1, 1, "Are you deleting a (S)pecific year or a (R)ange: ");
                wrefresh(win);

                char userResponse = tolower(getch());
                while (userResponse != 's' && userResponse != 'r')
                {
                    werase(win);
                    box(win,0,0);
                    wattron(win, COLOR_PAIR(3));
                    noecho();
                    mvwprintw(win,1, 1, "Are you deleting a (S)pecific year or a (R)ange: ");
                    
                    wattron(win, COLOR_PAIR(1));
                    mvwprintw(win,3, 1, "Your response is invalid, please try again: ");
                    wrefresh(win);
                    userResponse = tolower(getch());
                }
 
                werase(win);
                box(win,0,0);

                if (userResponse == 's')
                {
                    echo();
                    wattron(win, COLOR_PAIR(3));
                    mvwprintw(win,1, 1, "What year are you looking for? ");
                    wrefresh(win);
                    char year[10];
                    wgetstr(win, year);
                    while (!realNum(year))
                    {
                        werase(win);
                        box(win,0,0);
                        wattron(win, COLOR_PAIR(1));
                        mvwprintw(win,1, 1, "That is not a valid year, please try again: ");
                        wrefresh(win);
                        wgetstr(win, year);
                    }
                    noecho();
                    info->deleteByYear(stoi(year));
                }

                else
                {
                    echo();
                    char startYear[10];
                    char endYear[10];
                    wattron(win, COLOR_PAIR(3));
                    mvwprintw(win,1, 1, "Enter the starting year: ");
                    wgetstr(win, startYear);
                    werase(win);
                    box(win,0,0);
                    while (!realNum(startYear))
                    {
                        wattron(win, COLOR_PAIR(1));
                        mvwprintw(win,1, 1, "That is not a valid year, please try again: ");
                        wrefresh(win);
                        wgetstr(win, startYear);
                        werase(win);
                        box(win,0,0);
                    }
                    mvwprintw(win,1, 1, "Enter the ending year: ");
                    wgetstr(win, endYear);
                    while (!realNum(endYear))
                    {
                        wattron(win, COLOR_PAIR(1));
                        werase(win);
                        box(win,0,0);
                        mvwprintw(win,1, 1, "That is not a valid year, please try again: ");
                        wrefresh(win);
                        wgetstr(win, endYear);
                    }
                    werase(win);
                    box(win,0,0);
                    wrefresh(win);
                    noecho();
                    info->deleteByYear(stoi(startYear), stoi(endYear));
                }
            }
        }
        //list the database by alphbetical order or numerical order
        else if (response == 'l')
        {
            wattron(win, COLOR_PAIR(1));
            mvwprintw(win,1, 1, "You are currently: listing entries.");
            wattron(win, COLOR_PAIR(3));
            mvwprintw(win,3, 1, "You can list by: ");
            wattron(win, COLOR_PAIR(2));
            mvwprintw(win,5, 1, "(N)ame of manga");
            mvwprintw(win,6, 1, "(A)uthor of manga");
            mvwprintw(win,7, 1, "(Y)ear of release");
            mvwprintw(win,9, 1, "(R)eturn to main menu");
            wattron(win, COLOR_PAIR(3));
            mvwprintw(win,11, 1, "Enter the letter of your choice: ");
            wrefresh(win);

            char input = tolower(getch());
            while (input != 'n' && input != 'y' && input != 'r' && input != 'a')
            {
                wattron(win, COLOR_PAIR(1));
                mvwprintw(win,13, 1, "Your response is invalid, please try again: ");
                wrefresh(win);
                input = tolower(getch());
            }

            werase(win);
            box(win,0,0);

            if (input == 'n' || input == 'a')
            {
                wattron(win, COLOR_PAIR(3));
                mvwprintw(win,1, 1, "Did you want them listed in (A)lphabetical order or");
                mvwprintw(win,1, 52, " in (R)everse alphabetical order?: ");
                wrefresh(win);

                char userRes = tolower(getch());
                while (userRes != 'a' && userRes != 'r')
                {
                    wattron(win, COLOR_PAIR(1));
                    mvwprintw(win,3, 1, "Your response is invalid, please try again: ");
                    wrefresh(win);
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
                wattron(win, COLOR_PAIR(3));
                mvwprintw(win,1, 1, "Did you want them listed in (A)scending order or");
                mvwprintw(win,1, 49, " in (D)escending order?: ");
                wrefresh(win);

                char userResponse = tolower(getch());
                while (userResponse != 'a' && userResponse != 'd')
                {
                    wattron(win, COLOR_PAIR(1));
                    mvwprintw(win,3, 1, "Your response is invalid, please try again: ");
                    wrefresh(win);
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
            wattron(win, COLOR_PAIR(1));
            mvwprintw(win,1, 1, "h");
            wattron(win, COLOR_PAIR(2));
            mvwprintw(win,1, 2, "A");
            wattron(win, COLOR_PAIR(3));
            mvwprintw(win,1, 3, "v");
            wattron(win, COLOR_PAIR(1));
            mvwprintw(win,1, 4, "E");
            wattron(win, COLOR_PAIR(2));
            mvwprintw(win,1, 6, "a");
            wattron(win, COLOR_PAIR(3));
            mvwprintw(win,1, 8, "G");
            wattron(win, COLOR_PAIR(1));
            mvwprintw(win,1, 9, "r");
            wattron(win, COLOR_PAIR(2));
            mvwprintw(win,1, 10, "E");
            wattron(win, COLOR_PAIR(3));
            mvwprintw(win,1, 11, "a");
            wattron(win, COLOR_PAIR(1));
            mvwprintw(win,1, 12, "T");
            wattron(win, COLOR_PAIR(2));
            mvwprintw(win,1, 14, "d");
            wattron(win, COLOR_PAIR(3));
            mvwprintw(win,1, 15, "A");
            wattron(win, COLOR_PAIR(1));
            mvwprintw(win,1, 16, "y");
            wattron(win, COLOR_PAIR(2));
            mvwprintw(win,1, 17, "!");
            wattron(win, COLOR_PAIR(3));
            mvwprintw(win,1, 18, "!");

            char stop = 'z';
            while (stop != 'x'){
                mvwprintw(win,3,1,"Press \'x\' to continue");
                wrefresh(win);
                stop = tolower(getch());
            }
            delwin(win);
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
                wattron(win, COLOR_PAIR(1));
                mvwprintw(win,1, 1, "Please enter a valid option. Press \'x\' to continue.");
                wrefresh(win);
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
    wattron(win, COLOR_PAIR(1));
    mvwprintw(win,1, 1, "Main Menu: ");
    wattron(win, COLOR_PAIR(2));
    mvwprintw(win,3, 1, "(A)dd a manga.");
    mvwprintw(win,4, 1, "(F)ind a manga");
    mvwprintw(win,5, 1, "(D)elete a manga.");
    mvwprintw(win,6, 1, "(L)ist mangas.");
    mvwprintw(win,7, 1, "(Q)uit.");
    wattron(win, COLOR_PAIR(3));
    mvwprintw(win,9, 1, "Enter the letter of your choice: ");
    wrefresh(win);

    response = tolower(getch());
    move(0, 0);
    werase(win);
    box(win,0,0);
    wrefresh(win);
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
    werase(win);
    box(win,0,0);
    Manga_Record manga = mangaList.at(index);
    wattron(win, COLOR_PAIR(1));
    mvwprintw(win,1, 1, "Entry #");
    mvwprintw(win,1, 8, to_string(index + 1).data());

    mvwprintw(win,2, 1, "=========================================");

    attron(COLOR_PAIR(3));
    mvprintw(3, 1, "Name: ");
    attron(COLOR_PAIR(2));
    mvprintw(3, 7, manga.getName().data());
    mvprintw(3, manga.getName().size() + 7, ".");

    attron(COLOR_PAIR(3));
    mvprintw(4, 1, "Genres: ");
    attron(COLOR_PAIR(2));
    int rowPos = 9;
    for (int i = 0; i < manga.getGenres().size() - 1; i++){
        mvprintw(4, rowPos, manga.getGenres().at(i).data());
        mvprintw(4, rowPos + manga.getGenres().at(i).length(), ", ");
        rowPos += manga.getGenres().at(i).length() + 2;
    }
    mvprintw(4, rowPos, manga.getGenres().at(manga.getGenres().size() - 1).data());
    mvprintw(4, rowPos + manga.getGenres().at(manga.getGenres().size() - 1).length(), ".");
        
    
    attron(COLOR_PAIR(3));
    mvprintw(5, 1, "Authors: ");
    attron(COLOR_PAIR(2));
    rowPos = 10;
    for (int i = 0; i < manga.getAuthors().size() - 1; i++){
        mvprintw(5, rowPos, manga.getAuthors().at(i).data());
        mvprintw(5, rowPos + manga.getAuthors().at(i).length(), ", ");
        rowPos += manga.getAuthors().at(i).length() + 2;
    }
    mvprintw(5, rowPos, manga.getAuthors().at(manga.getAuthors().size()-1).data());
    mvprintw(5, rowPos + manga.getAuthors().at(manga.getAuthors().size()-1).length(), ".");

    wattron(win, COLOR_PAIR(3));
    mvwprintw(win,6, 1, "Status: ");
    wattron(win, COLOR_PAIR(2));
    if (manga.getStatus() == true)
    {
        mvwprintw(win,6, 9, "Releasing.");
    }
    else
    {
        mvwprintw(win,6, 9, "Completed.");
    }

    wattron(win, COLOR_PAIR(3));
    mvwprintw(win,7, 1, "Year of release: ");
    wattron(win, COLOR_PAIR(2));
    string yearRel = to_string(manga.getYear());
    char arrYear[4];
    for (int n = 0; n < 4; n++)
    {
        arrYear[n] = yearRel[n];
    }
    mvwprintw(win,7, 18, arrYear);

    wattron(win, COLOR_PAIR(3));
    mvwprintw(win,9, 1, "Enter \'z\' to move backwards \'c\' to move forward and \'e\' to exit");
    wrefresh(win);
    char output = tolower(getch());
    while (output != 'z' && output != 'c' && output != 'e')
    {
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win,11, 1, "Enter a valid action: ");
        wrefresh(win);
        output = tolower(getch());
    }
    return output;
}

//adds an entry to the database
void Menu::addEntry()
{
    wattron(win, COLOR_PAIR(1));
    mvwprintw(win,1, 1, "You are currently: adding an entry. ");

    wattron(win, COLOR_PAIR(3));
    char name[100];
    echo();
    mvwprintw(win, 5, 1, "Enter \"exit\" if you change your mind. ");
    mvwprintw(win,3, 1, "Enter the manga name: ");

    wrefresh(win);
    wgetstr(win, name);
    while (isBlankString(string(name))){
        werase(win);
        box(win,0,0);
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win,1,1, "Invalid entry.");
        wattron(win, COLOR_PAIR(3));
        mvwprintw(win, 5, 1, "Enter \"exit\" if you change your mind. ");
        mvwprintw(win,3, 1, "Enter the manga name: ");
        wrefresh(win);
        wgetstr(win,name);
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
                werase(win);
                box(win,0,0);
                char stop = 'z';
                while (stop != 'x'){
                    wattron(win, COLOR_PAIR(1));
                    mvwprintw(win,1, 1, "Entry already exists. Press \'x\' to return to menu.");
                    wrefresh(win);
                    stop = tolower(getch());
                    werase(win);
                    wrefresh(win);
                }   
                return;
            }
        }
    }

    werase(win);
    box(win,0,0);

    wrefresh(win);

    char entry[100];

    vector<string> authors = {};
    while (true)
    {
        werase(win);
        box(win,0,0);
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win,1, 1, "Enter the manga authors one at a time. ");
        mvwprintw(win,1, 39, " Enter \"stop\" to stop: ");
        wattron(win, COLOR_PAIR(3));
        mvwprintw(win,3, 1, "Enter an author: ");
        wrefresh(win);

        wgetstr(win, entry);
        if (toLowerStr(deleteWhitespace(string(entry))) == "exit")
        {
            return;
        }
        // (>^_^)># here's a waffle for your troubles
        else if (isBlankString(string(entry))){
            werase(win);
            box(win,0,0);
            char stop = 'z';
            while (stop != 'x'){
                wattron(win, COLOR_PAIR(1));
                mvwprintw(win,1, 1, "Please enter an author. Press \'x\' to continue.");
                wrefresh(win);
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
                werase(win);
                box(win,0,0);
                char stop = 'z';
                while (stop != 'x'){
                    wattron(win, COLOR_PAIR(1));
                    mvwprintw(win,1, 1, "Please enter an author. Press \'x\' to continue.");
                    wrefresh(win);
                    stop = tolower(getch());
                }   
            }
        }
       else
        {
            authors.push_back(deleteWhitespace(entry));
        }
    }

    werase(win);
    box(win,0,0);

    wrefresh(win);

    vector<string> genres = {};
    while (true)
    {
        werase(win);
        box(win,0,0);

        wattron(win, COLOR_PAIR(1));
        mvwprintw(win,1, 1, "Enter the manga genres one at a time. ");
        mvwprintw(win,1, 39, " Enter \"stop\" to stop: ");
        wattron(win, COLOR_PAIR(3));
        mvwprintw(win,3, 1, "Enter a genre: ");
        wrefresh(win);

        wgetstr(win, entry);
        if (toLowerStr(deleteWhitespace(string(entry))) == "exit")
        {
            return;
        }
        else if (isBlankString(string(entry))){
            werase(win);
            box(win,0,0);
            char stop = 'z';
            while (stop != 'x'){
                wattron(win, COLOR_PAIR(1));
                mvwprintw(win,1, 1, "Please enter a genre. Press \'x\' to continue.");
                wrefresh(win);
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
                werase(win);
                box(win,0,0);
                char stop = 'z';
                while (stop != 'x'){
                    wattron(win, COLOR_PAIR(1));
                    mvwprintw(win,1, 1, "Please enter a genre. Press \'x\' to continue.");
                    wrefresh(win);
                    stop = tolower(getch());
                }  
            }
        }
        else
        {
            genres.push_back(deleteWhitespace(entry));
        }
    }

    werase(win);
    box(win,0,0);

    bool isReleasing;
    wattron(win, COLOR_PAIR(3));
    mvwprintw(win,1, 1, "Is this manga still releasing? ");
    noecho();
    mvwprintw(win,3, 1, "Enter (Y)es or (N)o or (E) to exit: ");

    wrefresh(win);

    char res = tolower(getch());
    while (res != 'n' && res != 'y' && res != 'e')
    {
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win,3, 1, "Your response is invalid, please try again: ");
        wrefresh(win);
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

    werase(win);
    box(win,0,0);

    wattron(win, COLOR_PAIR(3));
    echo();
    mvwprintw(win,1, 1, "Enter the manga year of release: ");
    wrefresh(win);

    char year[10];
    wgetstr(win, year);
    while (!realNum(year))
    {
        if (string(year) == "exit"){return;}
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win,3, 1, "That is not a valid year, please try again: ");
        wgetstr(win, year);
    }

    Manga_Record newRecord(deleteWhitespace(name), authors, genres, isReleasing, stoi(year));

    werase(win);
    box(win,0,0);
    char stop = 'z';
    while (stop != 'x'){
        wattron(win, COLOR_PAIR(3));
        mvwprintw(win,1, 1, "Are you sure you want to add this entry? Press \'x\' to continue.");
        wrefresh(win);
        stop = tolower(getch());
    }  

    werase(win);
    box(win,0,0);
    newRecord.printEntry();

    werase(win);
    box(win,0,0);
    mvwprintw(win,1, 1, "Confirm (Y)es or (N)o");
    wattron(win, COLOR_PAIR(3));
    wrefresh(win);
    int userResponse = tolower(getch());
    while (userResponse != 'n' && userResponse != 'y')
    {
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win,3, 1, "Your response is invalid, please try again: ");
        wrefresh(win);
        userResponse = tolower(getch());
    }

    werase(win);
    box(win,0,0);
    if (userResponse == 'y'){
        info->add_entry(newRecord);

        wattron(win, COLOR_PAIR(3));
        mvwprintw(win,1, 1, "You have successfully entered a new entry.");
        wrefresh(win);
    }else{
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win,1, 1, "You have cancelled entering an entry");
    }
    werase(win);
    box(win,0,0);
    wrefresh(win);
}

// Mainly for deleting and adding, checks if strings are blank
bool Menu::isBlankString(string input){

    if (input.length() == 0){return true;}
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