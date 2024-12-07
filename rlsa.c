#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include<Python.h>
#include<numpy/arrayobject.h>
#include<stdbool.h>
#include <android/log.h>


/*
 Function : get_horizontal_smeared_image
 Parameters : image - 1d array representing the 2d image
                         rows - number of rows in the image
                         cols - number of columns in the image
                         range - minimum distance required between 2 black pixels if they are not to be colored black
 Return Value : 1d array representing the smeared image
 Description : performs horizontal smearing on the image
 Example : int* out = get_horizontal_image(image, 50, 50, 10);

*/
int* get_horizontal_smeared_image(int* image, long int rows, long int cols, int range)
{
    // create a variable to store the output, and allocated memory to it
    int* smeared = (int*)malloc(rows * cols * sizeof(int));

    // repeat the following for all rows in the image
    for(int i = 0; i < rows; ++i)
    {
         int j = 0;
        // find the first pixel in this image which is 0
        while(image[i * cols + j] != 0 && j < cols)
        {
            // copy the value of this pixel in the smeared image variable
            smeared[i * cols + j] = 255;
            ++j;
        }

        // store the position of this pixel in a variable, to be used when calculating the range
        int prev_black = j;

        // repeat the following for the remaining pixels
        for(; j < cols; ++j)
        {
            // copy the value of current pixel in the smeared image variable
            smeared[i * cols + j] = image[ i * cols + j];

            // if the current pixel is black ( 0 ),
            if( image[i * cols + j] == 0 )
            {
                // if the distance from this pixel to the previous black pixel is less than the required range,
                if( j - prev_black <= range )
                {
                    // mark all pixels from the previous black pixel to current pixel as black
                    for(int k = prev_black; k < j; ++k)
                        smeared[i * cols + k] = 0;
                }

                // store the position of current black pixel
                prev_black = j;
            }
        }
    }

   // return the smeared image variable
    return smeared;
}

/*

 Function : get_vertical_smeared_image
 Parameters : image - 1d array representing the 2d image
                         rows - number of rows in the image
                         cols - number of columns in the image
                         range - minimum distance required between 2 black pixels if they are not to be colored black
 Return Value : 1d array representing the smeared image
 Description : performs vertical smearing on the image
 Example : int* out = get_vertical_image(image, 50, 50, 10);

*/
int* get_vertical_smeared_image(int* image, long int rows, long int cols, int range)
{
    // create a variable to store the output, and allocated memory to it
    int* smeared = (int*)malloc(rows * cols * sizeof(int));

    // repeat the following for all rows in the image
    for(int i = 0; i < cols; ++i)
    {
         int j = 0;
        // find the first pixel in this image which is 0
        while(j < rows && image[j * cols + i] != 0 )
        {
            // copy the value of this pixel in the smeared image variable
            smeared[j * cols + i] = 255;
            ++j;
        }

        // store the position of this pixel in a variable, to be used when calculating the range
        int prev_black = j;

        // repeat the following for the remaining pixels
        for(; j < rows; ++j)
        {
            // copy the value of current pixel in the smeared image variable
            smeared[j * cols + i] = image[ j * cols + i];

            // if the current pixel is black ( 0 ),
            if( image[j * cols + i] == 0 )
            {
                // if the distance from this pixel to the previous black pixel is less than the required range,
                if( j - prev_black <= range )
                {
                    // mark all pixels from the previous black pixel to current pixel as black
                    for(int k = prev_black; k < j; ++k)
                        smeared[k * cols + i] = 0;
                }

                // store the position of current black pixel
                prev_black = j;
            }
        }
    }

   // return the smeared image variable
    return smeared;
}

/*

 Function : rlsa_smear_c
 Parameters : image - Python object representation of the numpy array image
                         horizontal - boolean value indicating whether horizontal smearing has to be performed
                         vertical - boolean value indicating whether vertical smearing has to be performed
                         range - Python tuple indicating values for horizontal and vertical range. Can be of length 0, 1 or 2
 Return Value : Python Object representation of numpy array containing the smeared image
 Description : performs horizontal and / or vertical run-length smearing on the input image

*/
int* rlsa_smear_c(int* image, long int rows, long int cols, int range)
{
    __android_log_print(ANDROID_LOG_INFO, "REFLOW", "beginning smear\n");
    // create a pointer to store the output of run-length smearing
    int* out = NULL;

    // perform horizontal smearing on the input image and store the result in out
    printf("horizontal\n");
    out = get_horizontal_smeared_image(image, rows, cols, range);
    // perform vertical smearing on out and store this result in out
    printf("vertical\n");
    out = get_vertical_smeared_image(out, rows, cols, range);

    // return this python array object
    return out;
}

