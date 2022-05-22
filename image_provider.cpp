#include "image_provider.h"

// You can modify this function to get image from either camera module or internet.
// In this file, i do just set every pixel in image to zero
void GetDummyImage(uint8_t* input, int size)
{
    for (int i = 0; i < size; i++) {
        input[i] = 0;
    }
}