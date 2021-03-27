## Final Project: A Database

In this project, your task is to create a database that can search, sort, and
add/delete data. All the data in the database consists of **records**, and
each record consists of **fields** of different types. For example, if your
database is storing songs, then its records might have fields for the song
name (a string), the artist (a string), and the year of publication (a whole
number).

Your record must have **at least three fields**, and at least one field must
be a string, and at least one field must be a number.

You should make your database about something you're interested in. For
example, your records could be songs, movies, books, games, celebrities,
sports teams, etc.


## Working with a Partner

You can do this project on your own, or with a partner.

If you work with a partner, both you and your partner must do and equal amount
of work, and you must *both* understand the whole program. Markers will expect
that projects done by teams of 2 to have more features/functionality/polish
than single-person programmers.

**Late time**: If you are working with a partner, then you can add your late
time together. For instance, if both you and your partner have have 24 hours
of late time, then you can submit your project up to 48 hours late.

Teams of more than 2 are **not** permitted under any circumstances.


## General Implementation Constraints

Please use standard C++ techniques as discussed in the course. Only use code
written by you (and your partner, if you have one). **Don't** use any code or
libraries written by others. You **can** use any standard C++ libraries.


## Submitting Your Work

On Canvas, please submit [a5.zip](a5.zip), containing **all** the source code
so the marker can compile and run your project. As described below, make sure
to also include the filled-in [README.txt](README.txt) file.


## Basic Requirements

Before we give your program any marks, it must meet the following basic
requirements:

- It must compile on Ubuntu Linux. If the marker can't compile your code, your
  mark for this project will be 0.

- It must have no memory leaks or memory errors, according to `valgrind`,
  e.g.:

  ```
  $ valgrind ./a5
    
  // ... lots of output ... 
  ```

  A program is considered to have no memory errors if:

  - In the `LEAK SUMMARY`, `definitely lost`, `indirectly lost`, and `possibly
    lost` must all be 0.

  - The `ERROR SUMMARY` reports 0 errors.

  - It is usually okay if **still reachable** reports a non- zero number of
    bytes.

- **You must include the large comment section with student info and the
  statement of originality in the file with main()**. If your submitted
  program does not have this, then we will assume your work is not original
  and it might not be marked.
  
If your program meets all these basic requirements, then it will be graded
using the marking scheme below.


## Marking Scheme

If you're working with a partner, then both partners will get the same marks.

### Source Code Readability (6 marks)

**(1 mark)** All names of variables, functions, structs, classes, etc. are
sensible, self-descriptive, and consistent.

**(1 mark)** Indentation and spacing is perfectly consistent and matches the
structure of the program. All blank lines and indents have a reason.

**(1 mark)** All lines are 100 characters in length, or less.

**(1 mark)** Comments are used when appropriate, e.g to describe code that is
tricky or very important. There are no unnecessary comments, and no
commented-out code.

**(1 mark)** Appropriate features of C++ are used in an appropriate way. For
example, do **not** use a feature of C (like C-style strings) when there is a
better C++ feature (e.g. the standard `string` class). Don't use any features
you don't understand.

**(1 mark)** Overall, the source code is easy to read and understand.

### Design Features

**(1 mark)** A class that stores a single database record. The name of this
class is up to you, but it should describe what it stores. For instance, if
your database is storing songs, then a good name for this class is `Song`.

**(1 mark)** A class called `Database` that stores all the records. The
methods of this class are probably where you want to implement the searching
and sorting functions.

**(1 mark)** A class called `Menu` that represents a menu of choices that the
user can choose from.

**(2 marks)** The three classes above are separately compiled and their `.o`
files are linked together using a makefile. To build your programs executable,
the marker should only have to type `make`.

You can create more classes than the three above, but you must have at *least*
these three classes.

**(3 marks)** Sensible use of `public`, `private`, constructors, destructors,
and methods. You can use inheritance if it makes sense, but it's not required.

**(1 mark)** Fill in [README.txt](README.txt) and include it in your submission.


### Menus

**(1 mark)** Menus are used to give the user choices. For example, the main
menu might look like this:

```
Welcome to the Song Database!
-----------------------------

(A)dd a song.
(F)ind a song.
(D)elete a song.
(L)ist songs.
(Q)uit

Enter the letter of your choice: 
```

Make your menus neat and tidy and easy to use. In this example, the choices
are made by choosing letters, but you could use numbers instead. Do what you
think is best.

**(1 mark)** When the user enters an invalid menu choice, the program re-asks
the user to pick a choice.


### Adding a Record

**(1 mark)** When the user chooses to enter a record, then your program asks
them to enter each piece of data in the record. After the user enters valid
data, then your program should say the record has been added, and go back to
the main menu.

**(1 mark)** If the record already exists in the database, then you should
tell the user the record already exists and *not* add a new record.

**(1 mark)** *Don't* let the user enter invalid data. For instance, when
entering the year a song was published, if the user enters out-of-range
numbers, like -343 or 2201, then your program should re-ask the user for a
valid number.

**(1 mark)** If the user enters the wrong *type* of data, then your program
should re-ask the user for correct data. For instance, when entering the year
a song was published, if the user enters a string like "this year", then your
program should re-ask the user for a valid number.

### Finding a Record

**(1 mark)** When the user chooses this option they are shown a sub-menu that
lists the different ways they can search for a record. The user should be
allowed to search for any kind of data in the record. For example, in a song
database where song records consist of a name, artist, and year, the sub-menu
might look like this:

```
Find a Song
-----------

You can search by:

(N)ame of song
(A)rtist who performed the song
(Y)ear of song

(R)eturn to main menu

Enter the letter of your choice: 
```

**(1 mark)** For including an option to return to the main menu.

**(1 mark)** When searching for strings, one kind of search should print all
records where the typed-in string from the user exactly matches the
appropriate field of a record.

**(1 mark)** When searching for strings, one kind of search should print all
records where the typed-in string from the user occurs as a *substring* in the
appropriate field of a record.

**(1 mark)** When searching for numbers, one kind of search should print all
records where the typed-in number from the user exactly matches the
appropriate field of a record.

**(1 mark)** When searching for numbers, one kind of search should print all
records where the number the appropriate field of a record is in a range, from
low to high. This would, for example, let the user see all songs in a song
database from the year 2005 to 2015.

In all cases of finding records, if no matching records are found, then print
a helpful message to the screen telling the user this.


### Deleting a Record

**(1 mark)** When deleting a record, one way to do this is to search by the
*exact* string that occurs in a field of the record. 

**(1 mark)** When deleting a record, one way to do this is to search by for a
*substring* that occurs in a field of the record. 

**(1 mark)** When deleting a record, one way to do this is to search by the
*exact* number that occurs in a field of the record. 

**(1 mark)** When deleting a record, one way to do this is to search for
numbers in a field that appear in a low to high range of numbers.

In all cases of deleting records:

- display the searched-for records to the user, and then ask them if they are
  sure they want to delete them

- if no matching records are found, then print a helpful message to the screen
  telling the user this


### Listing Records

**(1 mark)** For each string field in your record, allow the user to list all
records in *alphabetical order*.

**(1 mark)** For each string field in your record, allow the user to list all
records in *reverse alphabetical order*.

**(1 mark)** For each numeric field in your record, allow the user to list all
records in *ascending order*.

**(1 mark)** For each numeric field in your record, allow the user to list all
records in *descending order*.


### Starting and Quitting the Database

**(1 mark)** When your program starts it reads the records from a text file
`database.txt` into memory.

**(1 mark)** In the main menu, there is an option for the user to quit the
database. When the user chooses it the program ends.

**(1 mark)** When the user quits the database, all the records are saved to a
text file named `database.txt`. The exact format of the file is up to you, but
you might want to use comma-separated values, e.g.:

```
What About Me?, Snarky Puppy, 2014
Let the Mystery Be, Iris DeMent, 1992
```

*Be careful*: an issue with comma-separated values is that you need to do
something to handle commas that appear in strings that are not separators.

Please put *at least* 20 records (ideally more!) in `database.txt` when you
submit it. That way the marker will have something to try when they test your
program.


## Peer Review

When your program is finished and submitted, another student in the class will
be given a copy of your program so they can compile it, run it, and provide
feedback about the program and the source code.

The peer review will be set up as a separate assignment on Canvas, so you
don't have to do anything for it as part of this assignment. Just keep in mind
that other students will be running your project and reading your source code.
