#include "universe.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <inttypes.h>

struct Universe {
    uint32_t rows;
    uint32_t cols;
    bool **grid;
    bool toroidal;
};

Universe *uv_create(uint32_t rows, uint32_t cols, bool toroidal){
	Universe *u = (Universe *)malloc(sizeof(Universe));
	u->grid = (bool **)calloc(rows, sizeof(bool *));
	assert(u->grid);
	for (uint32_t r = 0; r < rows; r += 1) {
		u->grid[r] = (bool *)calloc(cols , sizeof(bool));
		assert(u->grid[r]);
	}
	u->rows = rows;
	u->cols = cols;
	u->toroidal = toroidal;
	return u;
}

void uv_delete(Universe *u){
	free(u->grid);
	free(u);
}

uint32_t uv_rows(Universe *u){
	return u->rows;
}

uint32_t uv_cols(Universe *u){
	return u->cols;
}

void uv_live_cell(Universe *u, uint32_t r, uint32_t c){
	if((r>= 0 && r <= uv_rows(u)) && (c >= 0 && c <= uv_cols(u))){
		u->grid[r][c] =  1;
	}
}
	
void uv_dead_cell(Universe *u, uint32_t r, uint32_t c){
	if((r>= 0 && r <= uv_rows(u)) && (c >= 0 && c <= uv_cols(u))){
		u->grid[r][c] =  0;
	}
}

bool uv_get_cell(Universe *u, uint32_t r, uint32_t c){
	if((r>= 0 && r <= uv_rows(u)) && (c >= 0 && c <= uv_cols(u))){
		return u->grid[r][c];
	}
	return -1;
}

bool uv_populate(Universe *u, FILE *infile){
	for(uint32_t i = 0; i < (u->rows*u->cols); i +=1){
		uint32_t x, y;
		fscanf(infile, "%" SCNu32 "%" SCNu32 "\n", &x, &y);
		if(x < 0 && x > u->rows && y < 0 && y > u->cols){
			fprintf(stderr, "invalid coordinates\n");
			return 1;
		}
		uv_live_cell(u, x, y);
    }
    return 0;
}


uint32_t OOR(Universe *u, uint32_t r, uint32_t c){  //OOR, checks indexes out of standard 
	if(u->toroidal){								//range and returns 1 if cell is 
		uint32_t p = -1;
		if(r == p){r = uv_rows(u)-1;}				//live and grid is toroidal
		if(c == p){c = uv_cols(u)-1;}
		if(r > uv_rows(u)-1){r = 0;}
		if(c > uv_cols(u)-1){c = 0;}
		if(u->grid[r][c] == 1){return 1;}
	}
	return 0;
}

uint32_t uv_census(Universe *u, uint32_t r, uint32_t c){
	uint32_t row;
	uint32_t col;
	uint32_t count = 0;
	for(uint32_t i = -1; i != 2; i += 1){
		row = r + i;
		for(uint32_t t = -1; t != 2; t += 1){
			col = c + t;
			if(row != r || col != c){
				if(row < 0 || row > uv_rows(u)-1 || col < 0 || col > uv_cols(u)-1){ 
					count += OOR(u, row, col);	//if cell out of range
				}
				else{
					count += uv_get_cell(u, row, col);
				}
			}

		}
	}
	return count;
}

uint32_t y;
uint32_t i;

void uv_print(Universe *u, FILE *outfile){
	for(y = 0; y < u->rows; y += 1){
		for(i = 0; i < u->cols; i += 1){
			if(uv_get_cell(u, y, i) ==  true){
				fprintf(outfile, "o");
			}
			else{
				fprintf(outfile, ".");
			}
		}
		fprintf(outfile, "\n");
	}
}

