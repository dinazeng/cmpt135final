//manga_record.cpp class

#include <vector>
#include <ncurses.h>
#include <string>
#include "manga_record.h"

using namespace std;


manga_record::manga_record(string mangaName, vector<string> mangaAuthor, vector <string> mangaGenres, 
                bool mangaStatus, int releaseYear){
    name = mangaName;
    authors = mangaAuthor;
    genres = mangaGenres;
    isReleasing = mangaStatus;
    year = releaseYear;
    initscr();
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    win = newwin(yMax*3/4, xMax*3/4,0, 0);
    refresh();
    noecho();
}

manga_record::manga_record(string mangaName, vector<string> mangaAuthor){
    name = mangaName;
    authors = mangaAuthor;
    genres = {};
    isReleasing = {};
    year = 0;
    initscr();
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    win = newwin(yMax*3/4, xMax*3/4,0, 0);
    refresh();
    noecho();
}

//default constructor
manga_record::manga_record(){
    name = "ERROR 404: NAME NOT FOUND";
    authors = {};
    genres = {};
    isReleasing = {};
    year = 0;
    initscr();
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    win = newwin(yMax*3/4, xMax*3/4,0, 0);
    refresh();
    noecho();
}

// Setters
void manga_record::set_name(string newName){name = newName;}
void manga_record::set_authors(vector<string> newAuthor){authors = newAuthor;}
void manga_record::set_genres(vector <string> newGenres) {genres = newGenres;}
void manga_record::set_status (bool newStat){isReleasing = newStat;}
void manga_record::set_year(int newYear){year = newYear;}

// Getters
string manga_record::getName() const { return name; }
vector<string> manga_record::getAuthors() const { return authors; }
vector<string> manga_record::getGenres() const { return genres; }
bool manga_record::getStatus() const { return isReleasing; }
int manga_record::getYear() const { return year; }

//print everything
void manga_record::printEntry(){
    // Displays information with proper formatting and colour coding

    box(win, 0, 0);
    wrefresh(win);

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK); // FOR LABELS
    init_pair(2, COLOR_WHITE, COLOR_BLACK); // FOR INFO
    init_pair(3, COLOR_GREEN, COLOR_BLACK); // HELPFUL MESSAGES

    wrefresh(win);

    werase(win);

    attron(COLOR_PAIR(3));
    mvprintw(1, 1,"=========================================");
    
    attron(COLOR_PAIR(3));
    mvprintw(3, 1, "Name: ");
    attron(COLOR_PAIR(2));
    mvprintw(3, 7, name.data());
    mvprintw(3, name.size() + 7, ".");

    attron(COLOR_PAIR(3));
    mvprintw(4, 1, "Genres: ");
    attron(COLOR_PAIR(2));
    int rowPos = 9;
    for (int i = 0; i < genres.size() - 1; i++){
        mvprintw(4, rowPos, genres.at(i).data());
        mvprintw(4, rowPos + genres.at(i).length(), ", ");
        rowPos += genres.at(i).length() + 2;
    }
    mvprintw(4, rowPos, genres.at(genres.size() - 1).data());
    mvprintw(4, rowPos + genres.at(genres.size() - 1).length(), ".");
        
    
    attron(COLOR_PAIR(3));
    mvprintw(5, 1, "Authors: ");
    attron(COLOR_PAIR(2));
    rowPos = 10;
    for (int i = 0; i < authors.size() - 1; i++){
        mvprintw(5, rowPos, authors.at(i).data());
        mvprintw(5, rowPos + authors.at(i).length(), ", ");
        rowPos += authors.at(i).length() + 2;
    }
    mvprintw(5, rowPos, authors.at(authors.size()-1).data());
    mvprintw(5, rowPos + authors.at(authors.size()-1).length(), ".");

    attron(COLOR_PAIR(3));
    mvprintw(6, 1,"Status: ");
    attron(COLOR_PAIR(2));
    if (isReleasing){mvprintw(6, 9,"Releasing.");}
    else {mvprintw(6, 9,"Completed.");}

    attron(COLOR_PAIR(3));
    mvprintw(7, 1, "Year of release: ");
    attron(COLOR_PAIR(2));
    string yearRel = to_string(year);
    char arrYear[4];
    for (int n = 0; n < 4; n++){arrYear[n] = yearRel[n];}
    mvprintw(7, 18, arrYear);

    box(win, 0, 0);
    
    wrefresh(win);
    char stop = 'z';
    while (stop != 'x'){
        attron(COLOR_PAIR(3));
        mvprintw(9, 1,"Press \'x\' to continue.");
        wrefresh(win);
        stop = getch();
    }

    werase(win);
    wrefresh(win);
}

//add to vector functions
void manga_record::add_genre(string newGenre){genres.push_back(newGenre);}
void manga_record::add_author(string newAuthor){authors.push_back(newAuthor);}

manga_record::~manga_record(){
    delwin(win);
    endwin();}
