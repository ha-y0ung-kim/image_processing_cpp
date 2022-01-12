# image-processing

image-processing is a image filtering tool.

The image is filtered in the spatial domain using kernel and convolution.
Currently provided filtering methods are :

    (1) Mean blurring
    (2) Gaussian blurring
    (3) Laplacian edge detection
    (4) Sobal in x direction
    (5) Sobal in y direction
    (6) Robert cross in x direction
    (7) Robert cross in y direction

## How to use 

The user can input an image file by typing the image file name : ../image_directory/image_file.png

For using sample image, type : sample_img/lena.png

Then user should type the size of the kernel.

The output of the image is saved as "output.png".

## Dependencies
    image load/write library 
    https://github.com/nothings/stb


## Compilation
~~~bash
mkdir build
cd build
cmake ..
make
./main
~~~


## Limitations 
- File extension .PNG, .JPG are supported.
- Filtering of an image is done in greyscale domain for edge detection.
- Kernel of the filter is a square kernel with odd size.