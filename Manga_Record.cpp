//Manga_Record.cpp class

#include <vector>
#include <ncurses.h>
#include <string>
#include "Manga_Record.h"

using namespace std;


Manga_Record::Manga_Record(string mangaName, vector<string> mangaAuthor,
                vector <string> mangaGenres, bool mangaStatus, int releaseYear){
    name = mangaName;
    authors = mangaAuthor;
    genres = mangaGenres;
    isReleasing = mangaStatus;
    year = releaseYear;
    initscr();
    refresh();
    noecho();
}

Manga_Record::Manga_Record(string mangaName, vector<string> mangaAuthor){
    name = mangaName;
    authors = mangaAuthor;
    genres = {};
    isReleasing = {};
    year = 0;
    initscr();
    refresh();
    noecho();
}

//default constructor
Manga_Record::Manga_Record(){
    name = "ERROR 404: NAME NOT FOUND";
    authors = {};
    genres = {};
    isReleasing = {};
    year = 0;
    initscr();
    refresh();
    noecho();
}

// Setters
void Manga_Record::set_name(string newName){name = newName;}
void Manga_Record::set_authors(vector<string> newAuthor){authors = newAuthor;}
void Manga_Record::set_genres(vector <string> newGenres) {genres = newGenres;}
void Manga_Record::set_status (bool newStat){isReleasing = newStat;}
void Manga_Record::set_year(int newYear){year = newYear;}

// Getters
string Manga_Record::getName() const { return name; }
vector<string> Manga_Record::getAuthors() const { return authors; }
vector<string> Manga_Record::getGenres() const { return genres; }
bool Manga_Record::getStatus() const { return isReleasing; }
int Manga_Record::getYear() const { return year; }

//print everything
void Manga_Record::printEntry(){
    // Displays information with proper formatting and colour coding

    refresh();

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK); // FOR LABELS
    init_pair(2, COLOR_WHITE, COLOR_BLACK); // FOR INFO
    init_pair(3, COLOR_GREEN, COLOR_BLACK); // HELPFUL MESSAGES

    refresh();

    erase();

    attron(COLOR_PAIR(3));
    mvaddstr(1, 1,"=========================================");
    
    attron(COLOR_PAIR(3));
    mvaddstr(3, 1, "Name: ");
    attron(COLOR_PAIR(2));
    mvaddstr(3, 7, name.data());
    mvaddstr(3, name.size() + 7, ".");

    attron(COLOR_PAIR(3));
    mvaddstr(4, 1, "Genres: ");
    attron(COLOR_PAIR(2));
    int rowPos = 9;
    for (int i = 0; i < genres.size() - 1; i++){
        mvaddstr(4, rowPos, genres.at(i).data());
        mvaddstr(4, rowPos + genres.at(i).length(), ", ");
        rowPos += genres.at(i).length() + 2;
    }
    mvaddstr(4, rowPos, genres.at(genres.size() - 1).data());
    mvaddstr(4, rowPos + genres.at(genres.size() - 1).length(), ".");
        
    
    attron(COLOR_PAIR(3));
    mvaddstr(5, 1, "Authors: ");
    attron(COLOR_PAIR(2));
    rowPos = 10;
    for (int i = 0; i < authors.size() - 1; i++){
        mvaddstr(5, rowPos, authors.at(i).data());
        mvaddstr(5, rowPos + authors.at(i).length(), ", ");
        rowPos += authors.at(i).length() + 2;
    }
    mvaddstr(5, rowPos, authors.at(authors.size()-1).data());
    mvaddstr(5, rowPos + authors.at(authors.size()-1).length(), ".");

    attron(COLOR_PAIR(3));
    mvaddstr(6, 1,"Status: ");
    attron(COLOR_PAIR(2));
    if (isReleasing){mvaddstr(6, 9,"Releasing.");}
    else {mvaddstr(6, 9,"Completed.");}

    attron(COLOR_PAIR(3));
    mvaddstr(7, 1, "Year of release: ");
    attron(COLOR_PAIR(2));
    string yearRel = to_string(year);
    char arrYear[4];
    for (int n = 0; n < 4; n++){arrYear[n] = yearRel[n];}
    mvaddstr(7, 18, arrYear);
    
    refresh();
    char stop = 'z';
    while (stop != 'x'){
        attron(COLOR_PAIR(3));
        mvaddstr(9, 1,"Press \'x\' to continue.");
        refresh();
        stop = getch();
    }

    erase();
    refresh();
}

//add to vector functions
void Manga_Record::add_genre(string newGenre){genres.push_back(newGenre);}
void Manga_Record::add_author(string newAuthor){authors.push_back(newAuthor);}

Manga_Record::~Manga_Record(){endwin();}