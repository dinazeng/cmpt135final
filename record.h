//record.h class

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
        single_record(){}

        // Setters
        void set_name(string newName);
        void set_authors(vector<string> newAuthor);
        void set_genres(vector <string> newGenres);
        void set_status (bool newStat);
        void set_year(int newYear);
    
        // Getters
        string getName() const;
        vector<string> getAuthors() const ;
        vector<string> getGenres() const ;
        bool getStatus() const ;
        int getYear() const ;

        //print everything
        void printEntry();

        //add to vector functions
        void add_genre(string newGenre);
        void add_author(string newAuthor);

        ~single_record(){}

    private:
        string name ;
        vector<string> authors ;
        vector <string> genres ;
        bool isReleasing;
        int year;
};