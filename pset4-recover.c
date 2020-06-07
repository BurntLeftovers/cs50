#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <cs50.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // reject any argv that is not a single argument.
    if (argc != 2)
    {
        printf("Error. Usage: ./recover data-to-be-scanned-for-jpg\n");
        return 1;
    }

    // open the data source using FILE *f = fopen(filename, "r") r for read only, w for write
    FILE *f = fopen(argv[1], "r");

    // reject invalid / missing files - not sure if needed
    if (f == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 1;
    }

    // Read the data, storing the data into a buffer block of 512 bytes (how to .jpg)
    // creating a buffer array to store the 512 byte block in.
    int chunk = 512;
    BYTE buffer[chunk];
    char filename[8];
    int fileCounter = 0;
    int bytesRead = 0;
    FILE *img = NULL;

    // fread the buffer bytes in a while loop until the end of the data
    while (fread(buffer, chunk, 1, f) == 1)
    {
        bytesRead += chunk;
        // looking for indicators that a file is a jpg. If true, write to a new file.
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
        {
            // if not first file, closing previous file so we can create a new one.
            if (fileCounter == 0)
            {
                // creating file name, img file, writing buffer data to img file.
                sprintf(filename, "%03i.jpg", fileCounter);
                img = fopen(filename, "w");
                fwrite(buffer, chunk, 1, img);
                printf("%i jpg\n", fileCounter);
                fileCounter ++;
            }
            else if (fileCounter > 0)
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", fileCounter);
                img = fopen(filename, "w");
                fwrite(buffer, chunk, 1, img);
                printf("%i jpg\n", fileCounter);
                fileCounter ++;
            }
        }
        else if (fileCounter > 0)
        {
            // continue writing data to img.
            fwrite(buffer, chunk, 1, img);
        }
    }
    // close files, print total bytes read for curiousity.
    fclose(img);
    fclose(f);
    printf("%i\n", bytesRead);
    return 0;
}
