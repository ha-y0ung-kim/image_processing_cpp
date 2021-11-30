#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

main()
{
    int width, height, channels;
    uint8_t *rgb_image = stbi_load("image.png", &width, &height, &CHANNELS, 3);

    //unsigned char *img = stbi_load("sky.jpg", &width, &height, &channels, 0);
    if (img == NULL)
    {
        printf("Error in loading the image\n");
        exit(1);
    }

    printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n", width, height, channels);

    stbi_image_free(rgb_image);
    //https://solarianprogrammer.com/2019/06/10/c-programming-reading-writing-images-stb_image-libraries/
}