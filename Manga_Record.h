//Manga_Record.h class

#ifndef Manga_Record_H
#define Manga_Record_H

#include <vector>
#include <string>
#include <ncurses.h>
using namespace std;

class Manga_Record{
    public:
        Manga_Record(string mangaName, vector<string> mangaAuthor, vector <string> mangaGenres, 
                       bool mangaStatus, int releaseYear);

        Manga_Record(string mangaName, vector<string> mangaAuthor);

        //default constructor
        Manga_Record();

        // Setters
        void set_name(string newName);
        void set_authors(vector<string> newAuthor);
        void set_genres(vector <string> newGenres);
        void set_status (bool newStat);
        void set_year(int newYear);
    
        // Getters
        string getName() const;
        vector<string> getAuthors() const;
        vector<string> getGenres() const;
        bool getStatus() const;
        int getYear() const ;

        //print everything
        void printEntry();

        //add to vector functions
        void add_genre(string newGenre);
        void add_author(string newAuthor);

        ~Manga_Record();

    private:
        string name;
        vector<string> authors;
        vector <string> genres;
        bool isReleasing;
        int year;
        WINDOW* win;
};

#endif