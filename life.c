#include "universe.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <ncurses.h>

#define DELAY 500000

int main(int argc, char **argv) {
	int opt;
	bool toroidal = false;
	bool silence = false;
	uint32_t generations = 100;
	FILE *infile = stdin;
	FILE *outfile = stdout;
	while ((opt = getopt(argc, argv, "tsn:i:o:")) != -1) {
        switch (opt) {
        	case 't':
        		toroidal = true;
        		break;
        	case 's':
        		silence = true;
        		break;
        	case 'n':
        		generations = strtod(optarg, NULL);
        		if(generations < 0){
        			fprintf(stderr, "Invalid number of generations\n");
        			return 1;
        		}
        		break;
        	case 'i':
        		fclose(stdin);
        		infile = fopen(optarg, "r");
        		if(infile == 0){
        			fprintf(stderr, "Input file does not exist\n");
        		}
        		break;
        	case 'o':
        		fclose(stdout);
        		outfile = fopen(optarg, "w");
        		if(outfile == 0){
        			fprintf(stderr, "Output file does not exist\n");
        		}
        		break;
        	default:
        		printf("Please specify input\n");
        		break;
        }
    }
    uint32_t rows, cols;
    fscanf(infile, "%" SCNu32 " %" SCNu32 "\n", &rows, &cols);
    if(rows < 0 && cols < 0){
    	fprintf(stderr, "invalid dimensions\n");
    	return 1;
    }
    Universe *a = uv_create(rows, cols, toroidal);
    Universe *b = uv_create(rows, cols, toroidal);
	uv_populate(a, infile);
	if(silence == false){initscr();}
	for(uint32_t i = 0; i < generations; i += 1){
		clear();
		for(uint32_t r = 0; r < uv_rows(a); r += 1){
			for(uint32_t c = 0; c < uv_cols(a); c +=1){	//for every cell
				if(uv_get_cell(a, r, c) == 1){			//if cell is live
					if(uv_census(a, r, c) == 2 || uv_census(a, r, c) == 3){	//and has 2 or 3 live neighbors
						uv_live_cell(b, r, c);			//set equivalent cell as live
						mvprintw(r, c, "o");
					}
					else{				
						uv_dead_cell(b, r, c);			//else set as dead
						mvprintw(r, c, ".");
					}
				}
				else {									//if cell is dead
					if(uv_census(a, r, c) == 3){		//and has 3 live neighbors
						uv_live_cell(b, r, c);			//set equivalent cell as live
						mvprintw(r, c, "o");
					}
					else{	
						uv_dead_cell(b, r, c);			//else set as dead
						mvprintw(r, c, ".");
					}
				}
			}
			
		}
		refresh();
		if(silence == false){usleep(DELAY);}
		Universe *t = a;
		a = b;
		b = t;	
	}
	endwin();
	fclose(infile);
 	uv_print(a, outfile);
	fclose(outfile);
	return 0;
}
