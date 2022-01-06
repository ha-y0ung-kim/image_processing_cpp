# image_processing_cpp

image_processing_cpp is a image filtering, modification tool.

The image is filtered in the spatial domain using kernel and convolution.
Currently provided filtering methods are :

    (1) Mean blurring
    (2) Gaussian blurring
    (3) Laplacian edge detection
    (4) Sobal_x
    (5) Sobal_y


## How to use 

The user can input an image file by typing the image file name : image_directory/image_file.png

Then user should type the size of the kernel

The output of the image is saved as "output.png"

## Dependencies
    
    image load/write library 
    https://github.com/nothings/stb


## Compilation
~~~bash
cmake .
make
./main
~~~


- File extension of .png, jpeg supported
- Kernel of the filter is a square kernel with odd size

