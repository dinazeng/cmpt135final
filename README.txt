CMPT 135 Assignment 5
=====================

Names of Team Members
---------------------
Dina Hui Zeng
301421388
dhz1@sfu.ca

Yejun (Jonathan) Kang
301428398
yka92@sfu.ca

Instructions for Compiling and Running
--------------------------------------

1. in a linux terminal enter "make" to make the executionable file 'app'
2. subsequently enter "./app"
3. the screen will print as much information as needed for navigation but, general 
   navigation involves pressing 'x' or other characters provided on screen 

Limitations
-----------

--terminal must be at least 100 characters wide and 20 lines long

--limit of 99 characters per manga name and 9 charaters per year

--user cannot enter any new entries with "exit" or for: name, genres or authors

--user cannot enter any new entries with the exact string "stop" for genres or authors

--no spell check available (if a user enters a string it will be displayed in that exact format)

--the user CANNOT use '{}' or '|' or ',' as a part of an author/genre entry

--the user CANNOT use '|' as a part of a title entry 

Known Bugs
----------

--if the user makes a mistake while entering information,it must be deleted and reupdated

--(valgrind only) scrolling through entries will flash between the window and the terminal

Extra Features
--------------

--scrolling is enabled when multiple entries need to be displayed

--display is featured in a window

--user can exit at any point while adding a new extry by typing in exit

--user can confirm additions and deletions to the database

--the alphabetical/reverse alphabetical vector<string> of authors can be used to sort the database

--text is color coded (white for information, red and green for instructions and helpful messages)
