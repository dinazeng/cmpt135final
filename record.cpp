//record.cpp class

#include <iostream>
#include <vector>
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
            cout << "=========================================" << endl;
            cout << "Name: " << name << "." << endl;

            cout << "Genres: ";
            for (int i = 0; i < genres.size() - 1; i++){cout << genres.at(i) << ", ";}
            cout << genres.at(genres.size() - 1) << "." << endl;

            cout << "Authors: ";
            for (int i = 0; i < authors.size() - 1; i++){cout << authors.at(i) << ", ";}
            cout << authors.at(authors.size() - 1) << "." << endl;

            cout << "Status: ";
            if (isReleasing){cout << "Releasing." << endl;}
            else {cout << "Completed." << endl;}

            cout << "Year of release: " << year << "." << endl;
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