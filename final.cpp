#include "cmpt_error.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <fstream>
#include <cassert>
#include <cmath>
//#include <ncurse>
using namespace std;

struct manga {

    string title;
    vector<string> genres;
    vector<string> authors;
    bool isReleasing;
    int releaseYear;

};

vector<manga> readFile (string input){

    // Reads in the file containing manga mangaInformation
    fstream inFile(input);
    // Checks if file name is valid
    if (inFile.fail()){
        // Asks user if they meant something else. 
        //Yes = rerun function with correct name
        //No = quit program
        cout << "The file you are looking for does not exist. Did you mean something else? (Y)es or (N)o: ";
        char userAnswer;
        cin >> userAnswer;
        if (tolower(userAnswer) == 'n'){
            cout << endl;
            cmpt::error("The file you have specified does not exist. Please try again later.");
        }
        else {
            cout << "What is the name of the file? (Your response requires case sensitivity and '.txt' at the end): ";
            string correctInput;
            cin >> correctInput;
            readFile(correctInput);
        }
    }

    // Read in each input from the file
    vector<manga> mangaList;
    while (true){

        string entry;
        manga mangaInformation;
        getline(inFile, entry);

        if (inFile.fail()){
            break;
        }

        // Getting title
        string mangaTitle = entry.substr(0, entry.find(":"));
        mangaInformation.title = mangaTitle; 
        entry = entry.substr(entry.find(":") + 1); // Get rid of trailing :

        // Getting Genres
        string mangaGenres = entry.substr(0, entry.find(":"));
        mangaGenres = mangaGenres.substr(1, mangaGenres.size() - 2); // Get rid of starting and trailing {}:
        bool gotGenres = false;
        while (gotGenres == false){
            string mangaGenre;
            if (mangaGenres.find(",") != -1){ // There are remaining genres
                mangaGenre = mangaGenres.substr(0, mangaGenres.find(","));
                mangaGenres = mangaGenres.substr(mangaGenres.find(",") + 2); // Get rid of comma and space
                mangaInformation.genres.push_back(mangaGenre);
            }
            else { // Last genre in the list
                mangaGenre = mangaGenres;
                mangaInformation.genres.push_back(mangaGenre);
                gotGenres = true;
            } 
        }
        entry = entry.substr(entry.find(":") + 1);
        
        // Getting Authors
        string mangaAuthors = entry.substr(0, entry.find(":"));
        mangaAuthors = mangaAuthors.substr(1, mangaAuthors.size() - 2); // Get rid of starting and trailing {}:
        bool gotAuthors = false;
        while (gotAuthors == false){
            string mangaAuthor;
            if (mangaAuthors.find(",") != -1){ // There are remaining genres
                mangaAuthor = mangaAuthors.substr(0, mangaAuthors.find(","));
                mangaAuthors = mangaAuthors.substr(mangaAuthors.find(",") + 2); // Get rid of comma and space
                mangaInformation.authors.push_back(mangaAuthor);
            }
            else { // Last genre in the list
                mangaAuthor = mangaAuthors;
                mangaInformation.authors.push_back(mangaAuthor);
                gotAuthors = true;
            } 
        }
        entry = entry.substr(entry.find(":") + 1);

        // Getting Status
        string mangaStatus = entry.substr(0, entry.find(":"));
        if (mangaStatus == "releasing"){
            mangaInformation.isReleasing = true;
        }
        else {
            mangaInformation.isReleasing = false;
        }
        //mangaInformation.status = mangaStatus;
        entry = entry.substr(entry.find(":") + 1);

        // Getting Release Date
        string mangaDate = entry;
        mangaInformation.releaseYear = stoi(mangaDate);

        // Append all this information to mangaList
        mangaList.push_back(mangaInformation);
    }

    inFile.close();
    return mangaList;

} 

int main(){
    cout << "The beginning of the end." << endl;
    vector<manga> mangaList = readFile("mangaList.txt");
}

