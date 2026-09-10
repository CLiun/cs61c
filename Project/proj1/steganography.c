/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	//YOUR CODE HERE
	Color *pixel = (Color *) malloc(sizeof(*pixel));
	pixel->R = image->image[row][col].R;
	pixel->G = image->image[row][col].G;
	pixel->B = image->image[row][col].B;
	return pixel;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	//YOUR CODE HERE
	Image *secret = malloc(sizeof(Image));
	if (secret == NULL) {
		exit(EXIT_FAILURE);
	}
	int row = image->rows;
	int col = image->cols;
	secret->rows = row;
	secret->cols = col;
	secret->image = (Color **) malloc(sizeof(Color *) * row);
	if (secret->image == NULL) {
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < row; i++) {
		secret->image[i] = (Color *) malloc(sizeof(Color) * col);
		if (secret->image[i] == NULL) {
			exit(EXIT_FAILURE);
		}
		for (int j = 0; j < col; j++) {
			Color *pixel = evaluateOnePixel(image, i, j);
			secret->image[i][j] = *pixel;
			int LMB = (pixel->B) & 1;	
			secret->image[i][j].R = (LMB == 1) ? 255 : 0;
			secret->image[i][j].G = (LMB == 1) ? 255 : 0;
			secret->image[i][j].B = (LMB == 1) ? 255 : 0;
			free(pixel);
		}	
	}
	return secret;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	//YOUR CODE HERE
	if (argc != 2) {
		fprintf(stderr, "Usage: ./func ppm.\n");
		exit(EXIT_FAILURE);
	}
	Image *input = readData(argv[1]);
	Image *secret = steganography(input);
	writeData(secret);
	freeImage(secret);
	freeImage(input);
}
