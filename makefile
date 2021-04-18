####################################################################
#
# Makefile for CMPT 135 Spring 2021, SFU Surrey.
#
#####################################################################

# Set the C++ compiler options:
#   -std=c++17 compiles using the C++17 standard (or at least as 
#    much as is implemented by the compiler, e.g. for g++ see
#    http://gcc.gnu.org/projects/cxx0x.html)
#   -Wall turns on all warnings
#   -Wextra turns on even more warnings
#   -Werror causes warnings to be errors 
#   -Wfatal-errors stops the compiler after the first error
#   -Wno-sign-compare turns off warnings for comparing signed and 
#    unsigned numbers
#   -Wnon-virtual-dtor warns about non-virtual destructors
#   -g puts debugging info into the executables (makes them larger)
CPPFLAGS = -std=c++17 -Wall -Wextra -Werror -Wfatal-errors -Wno-sign-compare -Wnon-virtual-dtor -g

Final_Main: Final.o Database.o Manga_record.o Menu.o
	g++ -o app Final.o Database.o Manga_Record.o Menu.o -lncurses

Final: 
	g++ -c $(CPPFLAGS) Final.cpp 

Database:
	g++ -c $(CPPFLAGS) Database.cpp 

Manga_Record:
	g++ -c $(CPPFLAGS) Manga_Record.cpp

Menu:
	g++ -c $(CPPFLAGS) Menu.cpp

clean:
	rm -f Final_Main.o Final.o Database.o Manga_Record.o Menu.o 
