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

final_main: final.o database.o manga_record.o menu.o
	g++ -o app final.o database.o manga_record.o menu.o -lncurses

final: 
	g++ -c $(CPPFLAGS) final.cpp 

database:
	g++ -c $(CPPFLAGS) database.cpp 

manga_record:
	g++ -c $(CPPFLAGS) manga_record.cpp

menu:
	g++ -c $(CPPFLAGS) menu.cpp

clean:
	rm -f final_main.o final.o database.o manga_record.o menu.o 
