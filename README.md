# Overview

This program is meant to simulate the game of life, the zero player game invented by John 
Horton Conway. The game will be played on a 2d grid of boolean values, with true representing
a live cell, and false representing a dead cell. The values will change after each generation
according to the following rules:
1. Any live cell with two or three live neighbors survives.
2. Any dead cell with exactly three live neighbors becomes a live cell.
3. All other cells die, either due to loneliness or overcrowding.

## Using the program

To create the program you must first run the Makefile, you can do this by using the
commands; '$ make', '$ make all', or '$ make life'. You can use '$ make clean' to 
get rid of the extra files.

After you have created the executable, you can run it with ./life [tsn:i:o:]
The following are the details for these command line options:
-t		Specifies the game to be played on a toroidal universe
-s		Silences the ncurses function and does not display each generation
-n		Specifies the number of generations the game will be played with
-i		Specifies input file to get dimensions and live cells from
-o 		Specifies output file to write result to
