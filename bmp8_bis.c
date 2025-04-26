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