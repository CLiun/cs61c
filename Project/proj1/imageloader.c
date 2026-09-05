/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				CLiun
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	//YOUR CODE HERE
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		fprintf(stderr, "Fail to open file.\n");
		exit(EXIT_FAILURE);
	}

	Image *loaded_image = (Image *) malloc(sizeof(*loaded_image));
	if (loaded_image == NULL) {
		fprintf(stderr, "Fail to malloc.\n");
		exit(EXIT_FAILURE);
	}

	char P3[12];
	uint32_t row, col;
	int rgb_val;
	int R, G, B; 
	if (fscanf(file, "%3s %d %d %d", P3, &col, &row, &rgb_val) != 4) {
		fprintf(stderr, "Fail at fscanf.\n");
		exit(EXIT_FAILURE);
	}
	
	loaded_image->rows = row;
	loaded_image->cols = col;
	loaded_image->image = (Color**) malloc(row * sizeof(Color*));
	for (int r = 0; r < row; r++) {
		loaded_image->image[r] = (Color *) malloc(sizeof(Color) * col);
		for (int c = 0 ; c < col; c++) {
			// read a triplet as (R, G, B) to init a Color in image[r][c]
				if(fscanf(file, "%d %d %d", &R, &G, &B) != 3) {
					fprintf(stderr, "Fail to scan pixel.\n");
					exit(EXIT_FAILURE);
				}
				loaded_image->image[r][c].R = R;	
				loaded_image->image[r][c].G = G;	
				loaded_image->image[r][c].B = B;	
				}
	}


	fclose(file);
	return loaded_image;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	//YOUR CODE HERE
	uint32_t rows = image->rows;
	uint32_t cols = image->cols;
	printf("P3\n");
	printf("%u %u\n255\n", image->cols, image->rows);
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			Color pixel = image->image[r][c];
			printf("%3d %3d %3d", pixel.R, pixel.G, pixel.B);
			printf((c < cols - 1) ? "   ": "");
		}
		printf("\n");
	}

}

//Frees an image
void freeImage(Image *image)
{
	//YOUR CODE HERE
	// Iterate image, free each Color* array, then free image
	for (int r = 0; r < image->rows; r++) {
		free(image->image[r]);
	}
	free(image);
}
