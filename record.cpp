//record.cpp class

#include <iostream>
#include <vector>
#include <ncurses.h>
using namespace std;

class single_record{
    public:
        single_record(string mangaName, vector<string> mangaAuthor, vector <string> mangaGenres, 
                      bool mangaStatus, int releaseYear): name(mangaName), authors(mangaAuthor),
                      genres(mangaGenres), isReleasing(mangaStatus), year(releaseYear){}

        single_record(string mangaName, vector<string> mangaAuthor):
            name(mangaName), authors(mangaAuthor){}

        //default constructor
        single_record(){
            name = "ERROR 404: NAME NOT FOUND";
        }

        // Setters
        void set_name(string newName){name = newName;}
        void set_authors(vector<string> newAuthor){authors = newAuthor;}
        void set_genres(vector <string> newGenres) {genres = newGenres;}
        void set_status (bool newStat){isReleasing = newStat;}
        void set_year(int newYear){year = newYear;}
    
        // Getters
        string getName() const { return name; }
        vector<string> getAuthors() const { return authors; }
        vector<string> getGenres() const { return genres; }
        bool getStatus() const { return isReleasing; }
        int getYear() const { return year; }

        //print everything
        void printEntry(){
            initscr();
            int yMax, xMax;
            getmaxyx(stdscr,yMax, xMax);

            //create window
            WINDOW *win = newwin(yMax*0.70, xMax*0.70, yMax, xMax);
            refresh();

            box(win,0,0);
            wrefresh(win);

            mvwprintw(win, 1, 1,"=========================================");
            mvwprintw(win, 2, 1, "Name: ");
            mvwprintw(win, 2, 5, name);
            mvwprintw(win, 2, name.length() + 5, ".");

            mvwprintw(win, 3, 1, "Genres: ");
            int rowPos = 9;
            for (int i = 0; i < genres.size() - 1; i++){
                mvwprintw(win, 4, rowPos, genres.at(i));
                mvwprintw(win, 4, rowPos + genres.at(i).length(), ", ");
                rowPos += genres.at(i).length() + 2;
            }
            mvwprintw(win, 4, rowPos, genres.at(genres.size() - 1));
            mvwprintw(win, 4, rowPos + genres.at(genres.size() - 1).length(), ".");

            mvwprintw(win, 5, 1, "Authors: ");
            rowPos = 10;
            for (int i = 0; i < authors.size() - 1; i++){
                mvwprintw(win, 5, rowPos, authors.at(i));
                mvwprintw(win, 5, rowPos + authors.at(i).length(), ", ");
                rowPos += authors.at(i).length() + 2;
            }
            mvwprintw(win, 5, rowPos, authors.at(authors.size() - 1));
            mvwprintw(win, 5, rowPos + authors.at(authors.size() - 1).length(), ".");

            mvwprintw(win,6, 1,"Status: ");
            if (isReleasing == true){
                mvwprintw(win,6, 9,"Releasing.");}
            else {mvwprintw(win,6, 9,"Completed.");}

            mvwprintw(win, 7, 1, "Year of release: ");
            mvwprintw(win, 7, 18, year);
            mvwprintw(win, 7, 22, ".");
            wrefresh(win);
            endwin();
        }

        //add to vector functions
        void add_genre(string newGenre){genres.push_back(newGenre);}
        void add_author(string newAuthor){authors.push_back(newAuthor);}

        ~single_record(){}

    private:
        string name = "";
        vector<string> authors = {};
        vector <string> genres = {};
        bool isReleasing = false;
        int year = 0;
};