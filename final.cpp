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

struct mangaInformation {

    string title;
    vector<string> authors;
    vector<string> genres;
    string status;
    string releaseDate;

};

vector<mangaInformation> readDatabase (string input){

    // Reads in the file containing manga information
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
            readDatabase(correctInput);
        }
    }

    // Read in each input from the file
    vector<mangaInformation> mangaList;
    while (true){

        string listing;
        mangaInformation information;
        getline(inFile, listing);

        if (inFile.fail()){
            break;
        }

        

    }

} 

int main(){
    cout << "The beginning of the end." << endl;
}