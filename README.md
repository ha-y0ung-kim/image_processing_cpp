# image_processing_cpp

image_processing_cpp is a image filtering, modification tool.

The image is filtered in the spatial domain using kernel and convolution.
Currently provided filtering methods are :

    (1) Mean blurring
    (2) Gaussian blurring
    (3) Laplacian edge detection
    (4) Unsharp image


## How to use 

The user can input an image file by typing the image file name : image_directory/image_file.png

Then user should type the size of the kernel

The output of the image is saved as "output.png"

## Dependencies
    
    image load/write library 
    https://github.com/nothings/stb


## Compilation
~~~bash
g++ -g main.cpp -o main
./main
~~~


## Limitations 
- Currently, only .PNG is supported.
- Filtering of an image is done in greyscale domain.
- Kernel of the filter is a square kernel with odd size

