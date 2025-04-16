# Role:

#include <stdio.h>
#include <stdlib.h>

# Role:
# Parameter:
# Result:
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

void bmp8_printInfo(t_bmp8 * img) {
    printf("Image Info:\n");
    printf("\tWidth: %d\n\tHeight: %d\n", img->width, img->height);
    printf("\tColor depth: %d\n\tData Size: %d\n", img->colorDepth, img->dataSize);
}

void bmp8_brightness(t_bmp8 * img, int value) {

}

void bmp8_applyFilter(t_bmp8 * img, float ** kernel, int kernelSize) {

}