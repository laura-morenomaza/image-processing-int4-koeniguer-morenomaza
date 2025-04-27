#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp8_bis.h"

/*
Role: load an image
Parameter:
    filename: a file
Result: an image of type t_bmp8
*/
t_bmp8 * bmp8_loadImage(const char * filename) {
    FILE *file = fopen(filename, "rb");
    t_bmp8 * img = malloc(sizeof(t_bmp8));
    if (file == NULL) {
        printf("Error, file inexistant.\n");
        return NULL;
    }

    fread(img->header, sizeof(unsigned char), 54, file);

    img->width = *(unsigned int *)&img->header[18];
    img->height = *(unsigned int *)&img->header[22];
    img->colorDepth = *(unsigned short *)&img->header[28];
    img->dataSize = *(unsigned int *)&img->header[34];

    if (img->colorDepth != 8) {
        printf("Error, not an 8-bit image.\n");
        fclose(file);
        return NULL;
    }
    fread(img->colorTable, sizeof(unsigned char), 1024, file);
    img->data = malloc(img->dataSize);
    fread(img->data, sizeof(unsigned char), img->dataSize, file);

    fclose(file);
    return img;
}

/*
Role:free the memory allocated for an image
Parameter:
    *img:  pointer to a t_bmp8 object
Result: Return nothing as a void function.
*/
void bmp8_free(t_bmp8 * img) {
    if (img != NULL) {
        free(img->data);
        free(img);
    }
}

/*
Role:reverse the color of avery pixels of the image
Parameter:
    *img: Pointer to the t_bmp8 structure.
Result: Return nothing as a void function.
*/
void bmp8_negative(t_bmp8 * img) {
    for (int i = 0; i < img->width * img->height; i++) {
        img->data[i] = 255-(img->data[i]);
    }
}


/*
Role: transforms a grayscale image into a binary image
Parameter:
    *img: Pointer to the t_bmp8 structure.
    threshold: an integer
Result: Return nothing as a void function.
*/
void bmp8_threshold(t_bmp8 * img, int threshold) {
    for (int i = 0; i < img->width * img->height; i++) {
        if (img->data[i] < threshold) {
            img->data[i] = 0;
        }
        else {
            img->data[i] = 255;
        }
    }
}