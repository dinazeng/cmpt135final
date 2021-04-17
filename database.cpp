//database class

#include "cmpt_error.h"
#include "manga_record.h"
#include "database.h"
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <ncurses.h>

using namespace std;

// Default constructor
database::database(){ 
    mangaList = {};
    readFile("database.txt");
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK); // FOR LABELS
    init_pair(2, COLOR_WHITE, COLOR_BLACK); // FOR INFO
    init_pair(3, COLOR_GREEN, COLOR_BLACK); // HELPFUL MESSAGES
    getmaxyx(stdscr, yMax, xMax);
    win = newwin(yMax*3/4, xMax*3/4,0, 0);
    box(win, 0, 0);
    refresh();
    }

// Reads in each entry in database.txt
void database::readFile (string input){    
    // Reads in the file containing manga manga
    fstream inFile(input);
    // Checks if file name is valid
    while (inFile.fail()){
        // Asks user if they meant something else. 
        // Yes = rerun function with correct name
        // No = quit program
        mvprintw(1, 1,"File does not exist. Did you mean something else? (Y)es or (N)o: ");
        wrefresh(win);
        char userResponse = tolower(getch());
        while (userResponse != 'n' && userResponse != 'y' && userResponse != 'r'){
            mvprintw(2, 1, "Your response is invalid, please try again: ");
            wrefresh(win);
            userResponse = tolower(getch());
        }
        if (userResponse == 'n'){
    
    cmpt::error("\nThe file inputted does not exist. Please try again.");}
        werase(win);
        box(win, 0, 0);
        mvprintw(1, 1, "What is the name of the file?");
        echo();
        wrefresh(win);
        char correctInput [100];
        getstr(correctInput);
        noecho();
        fstream inFile(correctInput);
    }

    // Read in each input (line) from the file
    while (true){
        string entry;
        manga_record manga;
        getline(inFile, entry);
        if (inFile.fail()){break;}

        // Getting title
        manga.set_name (entry.substr(0, entry.find("|")));
        entry = entry.substr(entry.find("|") + 1); // Get rid of trailing |

        // Getting Genres
        string mangaGenres = entry.substr(0, entry.find("|"));
        // Get rid of starting and trailing {}|
        mangaGenres = mangaGenres.substr(1, mangaGenres.size() - 2); 
        while (true){
            string mangaGenre;
            if (mangaGenres.find(",") != -1){ // There are remaining genres
                mangaGenre = mangaGenres.substr(0, mangaGenres.find(","));
                // Get rid of comma and space
                mangaGenres = mangaGenres.substr(mangaGenres.find(",") + 2); 
                manga.add_genre(mangaGenre);}
            else { // Last genre in the list
                manga.add_genre(mangaGenres);
                break;} 
        }
        entry = entry.substr(entry.find("|") + 1);
        
        // Getting authors
        string mangaAuthors = entry.substr(0, entry.find("|"));
        // Get rid of starting and trailing {}:
        mangaAuthors = mangaAuthors.substr(1, mangaAuthors.size() - 2); 
        while (true){
            string mangaAuthor;
            if (mangaAuthors.find(",") != -1){ // There are remaining genres
                mangaAuthor = mangaAuthors.substr(0, mangaAuthors.find(","));
                mangaAuthors = mangaAuthors.substr(mangaAuthors.find(",") + 2); 
                // Get rid of comma and space
                manga.add_author(mangaAuthor);}
            else { // Last genre in the list
                manga.add_author(mangaAuthors);
                break;} 
        }
        entry = entry.substr(entry.find("|") + 1);

        // Getting Status of releasing or completed
        if (entry.substr(0, entry.find("|")) == "releasing"){manga.set_status(true);}
        entry = entry.substr(entry.find("|") + 1);

        // Getting Release Date
        manga.set_year (stoi(entry));

        // Append all this information to mangaList as its own object
        mangaList.push_back(manga);
    }
    inFile.close();
} 

/* -------------------------- Searching for records ------------------------- */
// Searching by exact name
vector<manga_record> database::searchByExactName (string name){
    vector<manga_record>searchResults = {};

    for (manga_record manga : mangaList){

        string lowercaseName = toLowStr(name);
        string lowercaseTitle = toLowStr(manga.getName());

        if (lowercaseName == lowercaseTitle){
            searchResults.push_back(manga);
        }
        
    }
    return searchResults;
}
// Searching by sub string name
vector<manga_record> database::searchBySubName (string name){
    vector<manga_record>searchResults = {};

    for (manga_record manga : mangaList){

        string lowercaseName = toLowStr(name);
        string lowercaseTitle = toLowStr(manga.getName());

        if (lowercaseTitle.find(lowercaseName) != -1){
            searchResults.push_back(manga);
        }
        
    }
    return searchResults;
}
// Searching by exact year
vector<manga_record> database::searchByYear (int year){
    // For each manga with matching year, append to searchResults and return at end
    vector<manga_record> searchResults;
    for (manga_record manga : mangaList){
        if (manga.getYear() == year){
            searchResults.push_back(manga);
        }
    }
    if (searchResults.size() == 0){
        notFound();
    }
    return searchResults;
}
// Searching by year range
vector<manga_record> database::searchByYear (int yearStart, int yearEnd){
    // For each manga within year range, append to searchResults and return at end
    vector<manga_record> searchResults;
    for (manga_record manga: mangaList){
        // Checks if the years of each manga is within the range given
        if (manga.getYear() >= yearStart && manga.getYear() <= yearEnd){
            searchResults.push_back(manga);
        }
    }
    if (searchResults.size() == 0){
        notFound();
    }
    return searchResults;
}
// Searching by author
vector<manga_record> database::searchByAuthor(string name){
    vector<manga_record> searchResults = {};

    // Iterate through each manga entry within the vector
    for (manga_record manga : mangaList){
        for (string author : manga.getAuthors()){

            // Turns everything lowercase to prevent case sensitivity
            string lowercaseName = toLowStr(name);
            string lowercaseAuthor = toLowStr(author);

            // After both user input and manga's authors are made lowercase
            // .find() will check if the user's input matches any of the authors
            // Works for both exact string and substring
            if (lowercaseAuthor.find(lowercaseName) != -1){
                // If exact string or substring is found, append to searchResults
                searchResults.push_back(manga);
            }
        }
    }
    return searchResults;
}
// Searching by status
vector<manga_record> database::searchByStatus(bool status){
    vector<manga_record> searchResults = {};
    // Iterates through each manga entry
    for (manga_record manga : mangaList){
        if (status == manga.getStatus()){
            // True = releasing, false = completed.
            // Depending on bool value of status, push back entries to searchResults
            searchResults.push_back(manga);
        }
    }
    return searchResults;
}


/* ------------------- Searching for and deleting records ------------------- */
// Searching by name
void database::deleteByExactName (string name){
    // The case where user enters in exact name of manga
    for (int i = 0; i < mangaList.size(); i++){
        string lowercaseName = toLowStr(name);
        string lowercaseTitle = toLowStr(mangaList.at(i).getName());
        if (lowercaseName == lowercaseTitle){
            bool userConfirmation = deleteConfirmation(i, mangaList.at(i));
            // Once the corresponding manga entry is found, ask user for confirmation
            // Return bool value to userConfirmation
            if (userConfirmation == true){
                // Uses the corresponding index to delete the manga entry
                mangaList.erase(mangaList.begin() + i);
                char stop = 'z';
                while (stop != 'x'){
                    mvprintw(1,1,"Entry Deleted. Press \'x\' to continue.");
                    wrefresh(win);
                    stop = getch();
                }
                werase(win);
                box(win, 0, 0);
        
                return;
            }else {
                char stop = 'z';
                while (stop != 'x'){
                    mvprintw(1,1,"Entry NOT Deleted. Press \'x\' to continue.");
                    wrefresh(win);
                    stop = getch();
                }
                werase(win);
                box(win, 0, 0);
        
                return;
            }
        }
    }
    notFound();
}
// Searching by sub string name
void database::deleteBySubName (string name){

    vector<manga_record> searchResults = {};

    // The case where user enters in a "substring" of the name of manga
    for (int i = 0; i < mangaList.size(); i++){
        // Turns all letters of manga's name lower case to remove case sensitivity
        string lowercaseName = toLowStr(mangaList.at(i).getName());
        // Turns all letters of user's input lower case to remove case sensitivity
        string lowercaseUserInput = toLowStr(name);
        if (lowercaseName.find(lowercaseUserInput) != -1){
            searchResults.push_back(mangaList.at(i));
        }
    }
    
    if (searchResults.size() == 0){
        notFound();
        return;
    }
    printDatabase(searchResults);
    deleteConfirmationYear(searchResults);
}
// Searching by exact year
void database::deleteByYear (int year){
    // For each manga with matching year, append to searchResults and return at end
    vector<manga_record> searchResults;
    for (manga_record manga : mangaList){
        if (manga.getYear() == year){
            searchResults.push_back(manga);
        }
    }
    // Display all matched entries and ask user for which one they want to delete
    printDatabase(searchResults);
    if (searchResults.size() == 0){
        notFound();
        return;}

    deleteConfirmationYear(searchResults);
}
// Searching by year range
void database::deleteByYear (int yearStart, int yearEnd){
    // For each manga within year range, append to searchResults and return at end
    vector<manga_record> searchResults;
    for (manga_record manga: mangaList){
        if (manga.getYear() >= yearStart && manga.getYear() <= yearEnd){
            searchResults.push_back(manga);
        }
    }
    if (searchResults.size() == 0){
        notFound();
        return;}
    printDatabase(searchResults);
    deleteConfirmationYear(searchResults);
}

// Ask for confirmation on deleting record
bool database::deleteConfirmation (int index, manga_record manga){
    // Use the parameter manga to display manga later once we have a function to do so
    char userResponse = displaySingular(index, manga);
    werase(win);
    box(win, 0, 0);
    wrefresh(win);
    if (userResponse == 'y'){return true;}
    return false;
}

void database::deleteConfirmationYear (vector<manga_record> searchResults){
    echo();
    mvprintw(11, 1, "Enter the entry # of the one you want to delete: ");
    wrefresh(win);
    char userStr [3];
    getstr(userStr);
    while (!realNum (userStr, searchResults.size())){
        attron(COLOR_PAIR(1));
        mvprintw(13, 1, "The entry # inputted is invalid please try again: ");
        wrefresh(win);
        getstr(userStr);
    }
    werase(win);
    box(win, 0, 0);
    noecho();
    // Account for index display, decrement by 1 for proper index
    int userInput = stoi (userStr) - 1;
    bool userConfirmation = deleteConfirmation (userInput, searchResults.at(userInput));
    if (userConfirmation == true){
        // Loop through the entries, find matching name of user's input then delete
        for (int i = 0; i < mangaList.size(); i++){
            if (mangaList.at(i).getName() == searchResults.at(userInput).getName()){
                mangaList.erase(mangaList.begin() + i);
            }
        }
        mvprintw(1, 1, "Entry has been deleted.");
    }
    else {mvprintw(1, 1, "Entry has NOT been deleted.");}
    wrefresh(win);
    char stop = 'z';
    while (stop != 'x'){
        mvprintw(3,1,"Press \'x\' to continue.");
        wrefresh(win);
        stop = getch();
    }
}

bool database::realNum (string userInput, int end){
    for (int pos = 0; pos < userInput.length(); pos++){
        if (!(userInput[pos] >= '0' && userInput[pos] <= '9')){
            return false;}}
    if (stoi (userInput) > end || stoi(userInput) < 1){return false;}

    return true;
}

/* -------------- Listing records in multiple different orders -------------- */

//changes all characters in a string to lower case
string database::toLowStr (string str){
    string returnStr = "";
    for (int pos = 0; pos < str.length(); pos++){
        returnStr += tolower(str[pos]);}
    return returnStr;
}

vector<manga_record> database::listAlphabetical(){

    // Using selection sort, sort the manga based on the first character of names
    int minIndex = 0;
    vector<manga_record> alphaList = mangaList;

    // Iteration for beginning index in unsorted section of alphabeticalList
    for (int i = 0; i < alphaList.size() - 1; i++){
        // Finding the minimum element in the current unsorted alphabeticalList
        // Set index of the 'minimum element' default 
        //to the first index of unsorted alphabeticalList
        minIndex = i;
        // Iterate through the unsorted section of the vector
        for (int j = i + 1; j < alphaList.size(); j++){
            // Compare the names of the titles
            if (toLowStr(alphaList.at(j).getName()) 
                < toLowStr(alphaList.at(minIndex).getName())){
                minIndex = j;
            }
        }
        // Swap element at the minIndex with beginning of unsorted vector
        swap(alphaList.at(minIndex), alphaList.at(i));
    }
    return alphaList;
}

vector<manga_record> database::listAlphabeticalReverse(){
    // Using selection sort, sort the manga based on the first character of names
    vector<manga_record> alphabeticalListReverse = listAlphabetical();
    reverse(alphabeticalListReverse.begin(), alphabeticalListReverse.end());
    return alphabeticalListReverse;
}

vector<manga_record> database::listNumerical(){
    vector <manga_record> numericalList = mangaList;
    // Uses selection sort to sort each manga entry by release year
    for (int start = 0; start < numericalList.size()-1; start++){
        int min = start;
        for (int check = start + 1; check < numericalList.size(); check++){
            if (numericalList.at(check).getYear() < numericalList.at(min).getYear()){
                min = check;
            }
        }
        swap(numericalList.at(min), numericalList.at(start));
    }
    return numericalList;   
}

vector<manga_record> database::listNumericalReverse(){
    vector <manga_record> numericalList = listNumerical();
    reverse(numericalList.begin(), numericalList.end());
    return numericalList;
}

vector<manga_record> database::listAuthor(){
    // Using selection sort, sort the manga based on the first author name (alphabetical order)
    int minIndex;
    vector<manga_record> authorList = {};
    for (manga_record entry: mangaList){
        manga_record rec = entry;
        vector <string> alphaAuthors = {};
        for (string author: entry.getAuthors()){
            string alphaAu = toLowStr(author);
            alphaAuthors.push_back(alphaAu);
        }
        sort(begin(alphaAuthors), end(alphaAuthors));
        rec.set_authors(alphaAuthors);
        authorList.push_back(rec);
    }

    // Iteration for beginning index in unsorted section of authorList
    for (int i = 0; i < authorList.size() - 1; i++){
        // Finding the minimum element in the current unsorted authorList
        // Set index of the 'minimum element' default
        // to the first index of unsorted authorList
        minIndex = i;
        // Iterate through unsorted section of the vector
        for (int j = i + 1; j < authorList.size(); j++){
            // Compare the first authors of mangas
            if (toLowStr(authorList.at(j).getAuthors()[0])
                 < toLowStr(authorList.at(minIndex).getAuthors()[0])){
                minIndex = j;
            }
        }
        // Swap element at the minIndex with beginning of unsorted vector
        swap(authorList.at(minIndex), authorList.at(i));
    }
    return authorList;
}

vector <manga_record> database::listAuthorReverse(){
    vector<manga_record> revAu = listAuthor();
    reverse(begin(revAu), end(revAu));
    return revAu;
}

// Getters
vector<manga_record> database::getMangaList() const{ return mangaList; }; 

//Modify the vector
void database::add_entry (manga_record newEntry){mangaList.push_back(newEntry);}

// Displaying a manga's information
void database::printDatabase(vector<manga_record> mangaList)
{
    char input = '0';
    int loc = 0;
    while (input != 'e')
    {
        input = displayMultiple(loc, mangaList[loc]);
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

char database::displayMultiple(int index, manga_record manga){
// Displays information with proper formatting and colour coding

    werase(win);
    box(win, 0, 0);
    wrefresh(win);

    attron(COLOR_PAIR(1));
    mvprintw(1, 1, "Entry #");
    char entry[to_string(index).length()];
    for (int n = 0; n < 3; n++){entry[n] = to_string(index +1)[n];}
    mvprintw(1, 8, entry);

    mvprintw(2, 1,"=========================================");
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

    attron(COLOR_PAIR(3));
    mvprintw(6, 1,"Status: ");
    attron(COLOR_PAIR(2));
    if (manga.getStatus() == true){mvprintw(6, 9,"Releasing.");}
    else {mvprintw(6, 9,"Completed.");}

    attron(COLOR_PAIR(3));
    mvprintw(7, 1, "Year of release: ");
    attron(COLOR_PAIR(2));
    string yearRel = to_string(manga.getYear());
    char arrYear[4];
    for (int n = 0; n < 4; n++){arrYear[n] = yearRel[n];}
    mvprintw(7, 18, arrYear);
    
    attron(COLOR_PAIR(3));
    mvprintw(9, 1, "Enter \'z\' to move backwards \'c\' to move forward and \'e\' to exit");
    wrefresh(win);
    char output = tolower(getch());
    while (output != 'z' && output != 'c' && output != 'e')
    {
        attron(COLOR_PAIR(1));
        mvprintw(11, 1, "Enter a valid action: ");
        wrefresh(win);
        output = tolower(getch());
    }
    return output;
}

char database::displaySingular(int index, manga_record manga){
// Displays information with proper formatting and colour coding

    werase(win);
    box(win, 0, 0);
    wrefresh(win);

    attron(COLOR_PAIR(1));
    mvprintw(1,1,"You are deleting: Entry #");
    char entry[to_string(index).length()];
    for (int n = 0; n < 3; n++){entry[n] = to_string(index +1)[n];}
    mvprintw(1, 25, entry);

    mvprintw(2, 1,"=========================================");
    
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

    attron(COLOR_PAIR(3));
    mvprintw(6, 1,"Status: ");
    attron(COLOR_PAIR(2));
    if (manga.getStatus() == true){mvprintw(6, 9,"Releasing.");}
    else {mvprintw(6, 9,"Completed.");}

    attron(COLOR_PAIR(3));
    mvprintw(7, 1, "Year of release: ");
    attron(COLOR_PAIR(2));
    string yearRel = to_string(manga.getYear());
    char arrYear[4];
    for (int n = 0; n < 4; n++){arrYear[n] = yearRel[n];}
    mvprintw(7, 18, arrYear);
    
    mvprintw(9, 1, "Confirm (Y)es or (N)o: ");
    wrefresh(win);
    int userResponse = tolower(getch());
    while (userResponse != 'n' && userResponse != 'y'){
        mvprintw(11, 1, "Your response is invalid, please try again: ");
        wrefresh(win);
        userResponse = tolower(getch());
    } 

    return userResponse;
}

void database::notFound(){
    start_color(); 
    wrefresh(win);
    char stop = 'z';
    while (stop != 'x'){
        mvprintw(1,1,"The manga that you are looking for cannot be found. Please try again.");
        mvprintw(3,1, "Press \'x\' to continue");
        wrefresh(win);
        stop = getch();
    }
    werase(win);
    box(win, 0, 0);
}

// Deconstructor
database::~database(){
    delwin(win);
    endwin();}