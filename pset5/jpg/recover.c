/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * Common Data Types 
 *
 * The data types in this section are essentially aliases for C/C++ 
 * primitive data types.
 *
 * Adapted from http://msdn.microsoft.com/en-us/library/cc230309.aspx.
 * See http://en.wikipedia.org/wiki/Stdint.h for more on stdint.h.
 */
typedef uint8_t  BYTE;

typedef struct
{
    BYTE byteOne;
    BYTE byteTwo;
    BYTE byteThree;
    BYTE byteFour;
    BYTE img[508];
} __attribute__((__packed__))
JPEGBLOCK;

int main(int argc, char* argv[])
{
    // open the "memory card" file
    FILE* file = fopen("card.raw", "r");
    if (file == NULL)
    {
        printf("Could not open file");
        return 1;
    }
    
    // count to keep track of file name
    int jpgCount = 0;
    
    // create struct to act as buffer
    JPEGBLOCK jpg;
    
    // flag value
    bool jpgInProgress = false;
    
    FILE* jpgImage;
    
    while (fread(&jpg, sizeof(JPEGBLOCK), 1, file) == 1)
    {
        // check to see if this is start of a jpg   
        if (jpg.byteOne == 0xff && jpg.byteTwo == 0xd8 && jpg.byteThree == 0xff
            && (jpg.byteFour == 0xe0 || jpg.byteFour == 0xe1))
        {
            if (jpgInProgress == true)
            {
                fclose(jpgImage);
            }

            // create a new file name
            char title[8];
            sprintf(title, "%03d.jpg", jpgCount);
            
            // create new file
            jpgImage = fopen(title, "a");
            if (jpgImage == NULL)
            {
                printf("Could not create new image file");
                return 2;
            }
            
            // increment jpgCount to be used as next file name
            jpgCount += 1;
            
            jpgInProgress = true;
        }
        
        if (jpgInProgress == true)
        {
            fwrite(&jpg, sizeof(JPEGBLOCK), 1, jpgImage);
        }
    }
    
    fclose(jpgImage);
    
    fclose(file);
    
    return 0;
}
