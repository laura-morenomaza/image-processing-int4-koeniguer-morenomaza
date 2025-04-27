#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp8_bis.h"

/*
Role:
Parameter:
Result:
*/
t_bmp8 * bmp8_loadImage(const char * filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error");
        return NULL;
    }

    t_bmp8 *img = (t_bmp8 *)malloc(sizeof(t_bmp8));
    if (img == NULL) {
        fclose(file);
        printf("Error");
        return NULL;
    }

    // Lire en-tête
    fread(img->header, sizeof(unsigned char), 54, file);

    // Extraire infos
    img->width = *(unsigned int *)&img->header[18];
    img->height = *(unsigned int *)&img->header[22];
    img->colorDepth = *(unsigned short *)&img->header[28];
    img->dataSize = *(unsigned int *)&img->header[34];

    if (img->colorDepth != 8) {
        fprintf(stderr, "Error: Only 8-bit images are supported.\n");
        free(img);
        fclose(file);
        return NULL;
    }
}

/*
Role:
Parameter:
Result:
*/
void bmp8_free(t_bmp8 * img) {

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
    treshold: an integer
Result: Return nothing as a void function.
*/
void bmp8_threshold(t_bmp8 * img, int threshold) {
    for (int i = 0; i < img->width * img->height; i++) {
        if (img->data[i] < treshold) {
            img->data[i] = 0;
        }
        else {
            img->data[i] = 255;
        }
    }
}