//manga_record.cpp class

#include <vector>
#include <ncurses.h>
#include <string>
#include "manga_record.h"

using namespace std;

class manga_record{
    public:
        manga_record::manga_record(string mangaName, vector<string> mangaAuthor, vector <string> mangaGenres, 
                      bool mangaStatus, int releaseYear): name(mangaName), authors(mangaAuthor),
                      genres(mangaGenres), isReleasing(mangaStatus), year(releaseYear){}

        manga_record::manga_record(string mangaName, vector<string> mangaAuthor):
            name(mangaName), authors(mangaAuthor){}

        //default constructor
        manga_record::manga_record(){
            name = "ERROR 404: NAME NOT FOUND";
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
            initscr();
            refresh();

            mvprintw(1, 1,"=========================================");
                
            mvprintw(3, 1, "Name: ");
            char nameArr[name.length()];                
            for (int n = 0; n < name.length(); n++){nameArr[n] = name[n];}
            mvprintw(3, 7, nameArr);
            mvprintw(3, name.length() + 7, ".");

            mvprintw(4, 1, "Genres: ");
            int rowPos = 9;
            for (int i = 0; i < genres.size() - 1; i++){
                char arr[genres.at(i).length()];
                for (int n = 0; n < genres.at(i).length(); n++){arr[n] = genres.at(i)[n];}
                mvprintw(4, rowPos, arr);
                mvprintw(4, rowPos + genres.at(i).length(), ", ");
                rowPos += genres.at(i).length() + 2;
            }
            if (genres.size() > 0){
                char arrGen[genres.at(genres.size() - 1).length()];
                for (int n = 0; n < genres.at(genres.size() - 1).length(); n++){
                    arrGen[n] = genres.at(genres.size() - 1)[n];}
                mvprintw(4, rowPos, arrGen);
                mvprintw(4, rowPos + genres.at(genres.size() - 1).length(), ".");
            }
                
            mvprintw(5, 1, "Authors: ");
            rowPos = 10;
            for (int i = 0; i < authors.size() - 1; i++){
                char arrAu[authors.at(i).length()];
                for (int n = 0; n < authors.at(i).length(); n++){arrAu[n] = authors.at(i)[n];}
                mvprintw(5, rowPos, arrAu);
                mvprintw(5, rowPos + authors.at(i).length(), ", ");
                rowPos += authors.at(i).length() + 2;
            }
            if (authors.size() > 0){
                char arrAu[authors.at(authors.size() - 1).length()];
                for (int n = 0; n < authors.at(authors.size() - 1).length(); n++){
                    arrAu[n] = authors.at(authors.size() - 1)[n];}
                mvprintw(5, rowPos, arrAu);
                mvprintw(5, rowPos + authors.at(authors.size() - 1).length(), "."); 
            }

            mvprintw(6, 1,"Status: ");
            if (isReleasing == true){mvprintw(6, 9,"Releasing.");}
            else {mvprintw(6, 9,"Completed.");}

            mvprintw(7, 1, "Year of release: ");
            string yearRel = to_string(year);
            char arrYear[4];
            for (int n = 0; n < 4; n++){arrYear[n] = yearRel[n];}
            mvprintw(7, 18, arrYear);
            
            refresh();
            int stop = getch();

            erase();
            refresh();
            endwin();
        }

        //add to vector functions
        void manga_record::add_genre(string newGenre){genres.push_back(newGenre);}
        void manga_record::add_author(string newAuthor){authors.push_back(newAuthor);}

        ~manga_record(){}

    private:
        string name = "";
        vector<string> authors = {};
        vector <string> genres = {};
        bool isReleasing = false;
        int year = 0;
};
