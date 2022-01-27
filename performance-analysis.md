# Code Performance analysis

### For profiling,  gprof was used

The code was compiled with `cmake .. -DCMAKE_CXX_FLAGS=-pg` to run gprof.

The profiled data was analysed using `gprof ./main gmon.out > analysis.txt`


Full results can be found in the folder [code_performance](code_performance)

the following 3 cases were analyzed to check the improvement of the code

> 1. Mean blur with kernel size 5  : [before(ver1_1151)](code_performance/ver1_1151.txt), [after(ver2_1151)](code_performance/ver2_1151.txt)
>2. Laplacian edge detection with kernel size 5 : [before(ver1_2151)](code_performance/ver1_2151.txt), [after(ver2_2151)](code_performance/ver2_2151.txt)
>3. Sobal edge detection in y direction : [before(ver1_231)](code_performance/ver1_231.txt), [after(ver2_231)](code_performance/ver2_231.txt)


Here, we only check the 1st case, Mean blur with kernel size 5 is analyzed.


### Performance result before modification

~~~bash 
		     Call graph (explanation follows)


granularity: each sample hit covers 2 byte(s) for 0.07% of 14.21 seconds

index % time    self  children    called     name
                                                 <spontaneous>
[1]     99.9    0.00   14.19                 main [1]
                0.14   13.86       1/1           Image::convolution(Filter const&) [2]
                0.01    0.15       1/1           Image::export_image(FileType const&) [57]
                0.01    0.02       1/1           Image::Image(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&) [92]
                0.00    0.00       1/1           MeanBlur::set_filter() [151]

-----------------------------------------------

                0.14   13.86       1/1           main [1]
[2]     98.5    0.14   13.86       1         Image::convolution(Filter const&) [2]
                0.04   10.42 19660804/19660804     Filter::get_kernel() const [3]
                0.06    3.04 19660804/19660807     std::vector<std::vector<double, std::allocator<double> >, std::allocator<std::vector<double, std::allocator<double> > > >::~vector() [10]
                0.11    0.00 19660801/19660801     std::vector<std::vector<double, std::allocator<double> >, std::allocator<std::vector<double, std::allocator<double> > > >::operator[](unsigned long) [75]
-----------------------------------------------
                0.04   10.42 19660804/19660804     Image::convolution(Filter const&) [2]
[3]     73.6    0.04   10.42 19660804         Filter::get_kernel() const [3]
                0.25   10.17 19660804/19660804     std::vector<std::vector<double, std::allocator<double> >, std::allocator<std::vector<double, std::allocator<double> > > >::vector(std::vector<std::vector<double, std::allocator<double> >, std::allocator<std::vector<double, std::allocator<double> > > > const&) [4]
-----------------------------------------------

~~~


- One can observe the Image::convolution function takes most of the computation time
- Additionally, Flter::get_kernel() function used inside the Image::convolution, takes time to compute 


### Optimization of the Code

convolution function of image class (Image::convolution) is modified as followed

- Removed unnecessary 'if' statement and replaced it to std::min, std::max

- Stored the result of Filter::get_kernel() into a variable, rather than calling on each loop

- Moved an if statement to outside of for loops, instead of using if every loop.



### Optimization results


~~~bash 

granularity: each sample hit covers 2 byte(s) for 1.79% of 0.56 seconds

index % time    self  children    called     name
                                                 <spontaneous>
[1]    100.0    0.00    0.56                 main [1]
                0.17    0.17       1/1           Image::convolution(Filter const&) [2]
                0.01    0.16       1/1           Image::export_image(FileType const&) [3]
                0.00    0.03       1/1           Image::Image(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&) [12]
                0.00    0.01       1/1           MeanBlur::set_filter() [36]
                0.00    0.01       1/1           std::unique_ptr<Filter, std::default_delete<Filter> >::~unique_ptr() [65]

-----------------------------------------------
                0.17    0.17       1/1           main [1]
[2]     60.7    0.17    0.17       1         Image::convolution(Filter const&) [2]
                0.05    0.00 22020097/23592962     std::vector<std::vector<unsigned char, std::allocator<unsigned char> >, std::allocator<std::vector<unsigned char, std::allocator<unsigned char> > > >::operator[](unsigned long) [7]
                0.03    0.00 22020096/23592960     std::vector<unsigned char, std::allocator<unsigned char> >::operator[](unsigned long) [10]

-----------------------------------------------
                0.03    0.01       1/1           main [1]
[3]     34.1    0.03    0.01       1         Image::convolution(Filter const&) [3]
                0.01    0.00 3145728/5767168     std::vector<unsigned char, std::allocator<unsigned char> >::operator[](unsigned long) [24]


~~~


- code runtime decreased from 14.21 seconds to 0.56 seconds.
- Filter::get_kernel() function  no longer taking using up time.
