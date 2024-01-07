# Overview

This program is meant to simulate the game of life, the zero player game invented by John 
Horton Conway. The game will be played on a 2d grid of boolean values, which will be 
updated according to the rules; which can be found in the asgn4 pdf for those unfamiliar.

## Using the program

To create the program you must first run the Makefile, you can do this by using the
commands; '$ make', '$make all', or '$make life'. You can use '$make clean' to 
get rid of the extra files.

After you have created the executable, you can run it with ./life [tsn:i:o:]
The following are the details for these command line options:
-t		Specifies the game to be played on a toroidal universe
-s		Silences the ncurses function and does not display each generation
-n		Specifies the number of generations the game will be played with
-i		Specifies input file to get dimensions and live cells from
-o 		Specifies output file to write result to
