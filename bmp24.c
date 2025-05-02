#include <bmp8.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <bmp24.h>
#include <bmp24_bis.h>

void bmp24_freeDataPixels (t_pixel ** pixels, int height) {




/*
* @brief Set the file cursor to the position position in the file file,
* then read n elements of size size from the file into the buffer.
* @param position The position from which to read in file.
* @param buffer The buffer to read the elements into.
* @param size The size of each element to read.
* @param n The number of elements to read.
* @param file The file descriptor to read from.
* @return void
*/
void file_rawRead (uint32_t position, void * buffer, uint32_t size, size_t n, FILE * file) {
    fseek(file, position, SEEK_SET);
    fread(buffer, size, n, file);
}
/*
* @brief Set the file cursor to the position position in the file file,
* then write n elements of size size from the buffer into the file.
* @param position The position from which to write in file.
* @param buffer The buffer to write the elements from.
* @param size The size of each element to write.
* @param n The number of elements to write.
* @param file The file descriptor to write to.
* @return void
*/
void file_rawWrite (uint32_t position, void * buffer, uint32_t size, size_t n, FILE * file) {
    fseek(file, position, SEEK_SET);
    fwrite(buffer, size, n, file);
}