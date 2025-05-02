// Role:

#include <stdio.h>
#include <stdlib.h>
#include "bmp8.h"

/*
Role: Save an image in a file name (path).
Parameter:
    *filename: Pointer to a string.
    *img: Pointer to the t_bmp8 structure.
Result: Return nothing as a void function.
*/
void bmp8_saveImage(const char * filename, t_bmp8 * img) {
    //
    FILE* open = fopen (filename, "w");
    if (open == NULL) {
        printf ("Error opening file.\n");
        return;
    }

    //
    size_t write = fwrite(img,sizeof(t_bmp8), 1, open );
    if (write != 1) {
        printf ("Error writing to file.\n");
        return;
    }

    //
    int close = fclose(open);
    if (close != 0) {
        printf ("Error closing file.\n");
        return;
    }
}
/*
Role: Display informations on the image.
Parameter:
    *img: Pointer to the t_bmp8 structure.
Result: Return nothing as a void function.
*/
void bmp8_printInfo(t_bmp8 * img) {
    printf("Image Info:\n");
    printf("\tWidth: %d\n\tHeight: %d\n", img->width, img->height);
    printf("\tColor depth: %d\n\tData Size: %d\n", img->colorDepth, img->dataSize);
}

/*
Role: Modify the brightness of a grayscale image.
Parameter:
    *img: Pointer to the t_bmp8 structure.
    value (integer): Amount by which the grayscale image will be adjusted.
Result: Return nothing as a void function.
*/
void bmp8_brightness(t_bmp8 * img, int value) {
    for (int i = 0; i < img->width * img->height; i++) {
        img->data[i] += value;

        if (img->data[i] < 0) {
            img->data[i] = 0;
        }
        if (img->data[i] > 255) {
            img->data[i] = 255;
        }
    }
}

/*
Role:
Parameter:
    *img: Pointer to the t_bmp8 structure.
    **kernel (pointer of a 2D arrays of float): Represent the matrix (mask or kernel) to be applied on the image.
    kernelSize (integer): Size of the kernel (the size must be odd).
Result: Return nothing as a void function.
*/
void bmp8_applyFilter(t_bmp8 * img, float ** kernel, int kernelSize) {
    if (kernelSize % 2 != 1) {
        printf("Kernel Size must be odd.\n");
    }

    int halfKernelSize = kernelSize / 2;
    for (int x = 1; x < (img -> width - 2); x++) {
        for (int y = 1; (img -> height - 2); y++) {
            int sum = 0;
            for (int i = - halfKernelSize; i < halfKernelSize; i++) {
                for (int j = - halfKernelSize; j < halfKernelSize; j++) {
                    sum += (img -> data[(x - i) * (img->width) + (y - j)]) * kernel[halfKernelSize - i][halfKernelSize - j];
                }
            }
            t_bmp8 *new_image;
            t_bmp8 *new_kernel= img-> data[x*(img->width) + y];
        }
    }
}


/*-----------------------------------------bmp8_bis below----------------------------------------------------------*/

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