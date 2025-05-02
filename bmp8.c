// Role:

#include <stdio.h>
#include <stdlib.h>
#include "bmp8.h"
#include "bmp8_bis.h"

/*
Role: Save an image in a file name (path).
Parameter:
    *filename: Pointer to a string.
    *img: Pointer to the t_bmp8 structure.
Result: Return nothing as a void function.
*/
void bmp8_saveImage(const char * filename, t_bmp8 * img) {
    //
    FILE open = fopen (filename, "w");
    if (open == NULL) {
        printf ("Error opening file.\n");
        return;
    }

    //
    size_t write = fwrite(img,sizeof(t_bmp8), 1, filename);
    if (write != 1) {
        printf ("Error writing to file.\n");
        return;
    }

    //
    int close = fclose(filename);
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
bmp8_printInfo(t_bmp8 * img) {
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
    for (int x = 0; i < kernelSize; i++) {
        for (int y = 0; j < kernelSize; j++) {
            sum = 0;
            for (int i = - halfKernelSize; i < halfKernelSize; i++) {
                for (int j = - halfKernelSize; j < halfKernelSize; j++) {
                    sum += (img -> data[((x - i)) * width + (y - j)]) * kernel[(halfKernelSize - i][halfKernelSize - j];
                }
            }
            t_bmp8 *new_image;
            t_bmp8 *new_kernel -> data[x * width + y];
        }
    }