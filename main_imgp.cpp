#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main()
{
    int width, height, channels;
    uint8_t *rgb_image = stbi_load("img_lenna.png", &width, &height, &channels, 3);

    if (rgb_image == NULL)
    {
        printf("Error in loading the image\n");
        exit(1);
    }

    printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", width, height, channels);

    stbi_image_free(rgb_image);
}