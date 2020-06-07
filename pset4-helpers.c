#include "helpers.h"
#include <stdio.h>
#include <math.h>

// This is the program we will be developing as part of this exercise. Do not touch other files.
// Quick refresh - The goal of each function is to modify the pixels in the source image, and produce an output image
// The data of each image is stored in an array image[height][width]
// To modify the colour of a pixel at address image[x][y], we can use image[x][y].rgbtBlue and so on.

// Convert image to grayscale
// This function will output an image that includes gray pixels only.
// A gray pixel has all RGB values the same. (i.e. Red = 100, Green = 100, Blue = 100)
// To change a pixel from a colour to a gray of the same tone, then the average of RGB values can be used.
// e.g. a green pixel of R = 50, G = 190, B = 90 has an average value of 110. The gray value can be set as RGB = 110.
// Program needs to round averages to whole int values, not floats
// Pseudocode
// Access each row of the image file using image[x]
// Within each row, access each pixel using image[x][y]
// Store the average RGB value for conversion to grayscale in float average.
// Pass the gray value to an integer for editing.
// Convert the RGB value of the pixel based on the average
// Return the modified pixel for output. End.
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int gray;
    float average = 0;
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            // need to delcare a float twice to avoid rounding errors?
            average = (float)(image[x][y].rgbtRed + image[x][y].rgbtGreen + image[x][y].rgbtBlue) / 3;
            gray = round(average);
            image[x][y].rgbtRed = gray;
            image[x][y].rgbtGreen = gray;
            image[x][y].rgbtBlue = gray;
        }
    }
    // testing math.
    printf("Red: %i\n", image[10][10].rgbtRed);
    printf("Gre: %i\n", image[10][10].rgbtGreen);
    printf("Blu: %i\n", image[10][10].rgbtBlue);
    printf("Gray: %i\n", gray);
    printf("Avg: %0.5f\n", average);
    return;
}

// Convert image to sepia
// Formula for Sepia function
// sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
// sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
// sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue

// repeat steps from above function, but using the above calculation.
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed, sepiaGreen, sepiaBlue;
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            sepiaRed = (float)((image[x][y].rgbtRed * 0.393) + (image[x][y].rgbtGreen * 0.769) + (image[x][y].rgbtBlue * 0.189));
            sepiaGreen = (float)((image[x][y].rgbtRed * 0.349) + (image[x][y].rgbtGreen * 0.686) + (image[x][y].rgbtBlue * 0.168));
            sepiaBlue = (float)((image[x][y].rgbtRed * 0.272) + (image[x][y].rgbtGreen * 0.534) + (image[x][y].rgbtBlue * 0.131));
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[x][y].rgbtRed = roundf(sepiaRed);
            image[x][y].rgbtGreen = roundf(sepiaGreen);
            image[x][y].rgbtBlue = roundf(sepiaBlue);
        }
    }
    return;
}

// Reflect image vertically
// psuedocode description
// create temporary storage space
// access each row of the image, starting with column a (left most)
// store value of column a into a temporary storage row
// move pixel column z (right most) to column a's location.
// move pixel column a from temporary storage into column z.
// repeat with column b and column y, c and x, etc. until all columns have been swapped

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int redTemp = 0;
    int greenTemp = 0;
    int blueTemp = 0;
    for (int x = 0; x < (height); x ++)
    {
        for (int y = 0; y < width / 2; y ++)
        {
            //setting final pixel location
            // not sure why the - 1 is needed. Get an out of bounds error without.
            // future Ash - go back and do this using the swap function.
            int z = (width - y - 1);
            // copy first pixel to swap space
            redTemp = image[x][y].rgbtRed;
            greenTemp = image[x][y].rgbtGreen;
            blueTemp = image[x][y].rgbtBlue;
            // copy last pixel to first space
            image[x][y].rgbtRed = image[x][z].rgbtRed;
            image[x][y].rgbtGreen = image[x][z].rgbtGreen;
            image[x][y].rgbtBlue = image[x][z].rgbtBlue;
            // copy temp values to final space
            image[x][z].rgbtRed = redTemp;
            image[x][z].rgbtGreen = greenTemp;
            image[x][z].rgbtBlue = blueTemp;
        }
    }
    return;
}

// Blur image
// Pseudocode for this function
// Blur forumla is based on changing the colour of a pixel to the average colour value of all the adjacent pixels (9 - including center)
// Creat copy array to store averages during calcuation
// Loop through pixels in sequence, and store the values of each colour in the temporary array
// store the average colour value based on those totals divided by the calcuation case.
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //setting up temp array based on original RGPTRIPLE
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // Loop through each pixel and copy the values.
    // If values used to handle edge and corner cases to ensure that only valid values are being copied.
    // 
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            int red = 0;
            int green = 0;
            int blue = 0;
            float counter = 0;
            
            // 5
            red += copy[x][y].rgbtRed;
            green += copy[x][y].rgbtGreen;
            blue += copy[x][y].rgbtBlue;
            counter++;

            //1
            if (x - 1 > -1 && y - 1 > -1)
            {
                red += copy[x - 1][y - 1].rgbtRed;
                green += copy[x - 1][y - 1].rgbtGreen;
                blue += copy[x - 1][y - 1].rgbtBlue;
                counter++;
            }
            // 2
            if (x - 1 > -1)
            {
                red += copy[x - 1][y].rgbtRed;
                green += copy[x - 1][y].rgbtGreen;
                blue += copy[x - 1][y].rgbtBlue;
                counter++;
            }
            // 3
            if (x - 1 > -1 && y + 1 < height)
            {
                red += copy[x - 1][y + 1].rgbtRed;
                green += copy[x - 1][y + 1].rgbtGreen;
                blue += copy[x - 1][y + 1].rgbtBlue;
                counter++;
            }
            // 4
            if (y - 1 > -1)
            {
                red += copy[x][y - 1].rgbtRed;
                green += copy[x][y - 1].rgbtGreen;
                blue += copy[x][y - 1].rgbtBlue;
                counter++;
            }
            // 6
            if (y + 1 < width)
            {
                red += copy[x][y + 1].rgbtRed;
                green += copy[x][y + 1].rgbtGreen;
                blue += copy[x][y + 1].rgbtBlue;
                counter++;
            }
            // 7
            if (x + 1 < height && y - 1 > -1)
            {
                red += copy[x + 1][y - 1].rgbtRed;
                green += copy[x + 1][y - 1].rgbtGreen;
                blue += copy[x + 1][y - 1].rgbtBlue;
                counter++;
            }
            // 8
            if (x + 1 < height)
            {
                red += copy[x + 1][y].rgbtRed;
                green += copy[x + 1][y].rgbtGreen;
                blue += copy[x + 1][y].rgbtBlue;
                counter++;
            }
            // 9
            if (x + 1 < height && y + 1 < width)
            {
                red += copy[x + 1][y + 1].rgbtRed;
                green += copy[x + 1][y + 1].rgbtGreen;
                blue += copy[x + 1][y + 1].rgbtBlue;
                counter++;
            }

            image[x][y].rgbtRed = round(red / counter);
            image[x][y].rgbtGreen = round(green / counter);
            image[x][y].rgbtBlue = round(blue / counter);
            
        }
    }
    return;
}

