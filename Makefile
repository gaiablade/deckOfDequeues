# CS315 Makefile for Program 1: Deck of Dequeues
# Feel free to modify as needed.
# Original author: Raphael Finkel 1/2020

CFLAGS = -Wall -g
CPPFLAGS = -Wall -g

COMP = /usr/bin/g++

NUMPLAYERS = 4
NUMCARDS = 5
NUMTURNS = 1000

SEED = 43

cards: Cards.o cards.cpp
	$(COMP) $^ -o $@ $(CPPFLAGS)

sortedCards: Cards.o sortedCards.cpp
	$(COMP) $^ -o $@ $(CPPFLAGS)

Cards.o: Cards.cpp Cards.h
	$(COMP) $< -c -o $@

# compile and run the student program, placing the result in tmpRun.out
run: cards randGen.pl
	randGen.pl $(SEED) | cards $(NUMPLAYERS) $(NUMCARDS) $(NUMTURNS) > tmpRun.out
	less tmpRun.out

# compile and run a known working program, placing the result in tmpWorking.out
runWorking: workingCards randGen.pl
	randGen.pl $(SEED) | workingCards $(NUMPLAYERS) $(NUMCARDS) $(NUMTURNS) > tmpWorking.out
	less tmpWorking.out

# get the randGen.pl program
randGen.pl:
	wget http://www.cs.uky.edu/~raphael/courses/CS315/prog1/randGen.pl
	chmod +x randGen.pl

# get the workingCards program
workingCards:
	wget http://www.cs.uky.edu/~raphael/courses/CS315/prog1/workingCards
	chmod +x workingCards

# Modify the following recipe to zip exactly what you want to include.
zipAll: clean
	zip toSubmit.zip *
	
.PHONY: clean
clean:
	rm -f randGen.pl cards workingCards tmp* toSubmit.zip
