###########################################################
# Makefile for CS570 Assignment #2
# Cody Morgan, Andrew Levandowski
###########################################################

CC = g++
CPPFILES = driver.cpp FileEditor.cpp
FLAG = -std=c++11
EXEC = filem

all:
	$(CC) $(CPPFILES) -o $(EXEC) $(FLAG)
	rm -f *.o

run: all
	./$(EXEC)

clean:
	rm -f *.o core a.out $(EXEC)
	rm -r fileEditing

#######################[ EOF: Makefile ]###################
