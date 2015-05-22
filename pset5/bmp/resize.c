/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Resizes a bmp image.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

// bytes per pixel (BPP)
#define BYTESPERPIXEL 3

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    // convert n argument to an int
    int n = atoi(argv[1]);
    
    // verify n argument is valid
    if (n < 0 || n > 100)
    {
        printf("Error: Invalid n argument (resize integer)\n");
        return 2;
    }
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }
       
    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // bounds to control iteration through read file
    LONG pixBound = bi.biWidth;
    LONG scanBound = abs(bi.biHeight);
    
    // determine padding for scanlines for original photo
    // pixBound variable is the biWidth of the original bmp file
    int padding =  (4 - (pixBound * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // update BITMAPINFOHEADER to scale
    bi.biWidth = bi.biWidth * n;
    bi.biHeight = bi.biHeight * n;
    
    // determine padding for scanlines for new photo
    int new_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // now that new_padding has been calculated finish BITMAPINFOHEADER update
    bi.biSizeImage = (bi.biWidth * BYTESPERPIXEL + new_padding) * abs(bi.biHeight);

    // update BITMAPFILEHEADER to scale
    bf.bfSize = bf.bfOffBits + bi.biSizeImage;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines (aka rows)
    for (int i = 0; i < scanBound; i++)
    {
        // counter to keep track of trips array
        int trip_count = 0;
        
        // array to hold triplets in scanline
        RGBTRIPLE trips_array[bi.biWidth];
        
        // iterate over pixels in scanline (aka columns)
        for (int j = 0; j < pixBound; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
        
            for (int k = 0; k < n; k++)
            {
                trips_array[trip_count] = triple;
                trip_count += 1;
            }
        } 
        
        // repeat row n times
            // write row
            // add padding
        for (int k = 0; k < n; k++)
        {
            for (int l = 0; l < bi.biWidth; l++)
            {
                fwrite(&trips_array[l], sizeof(RGBTRIPLE), 1, outptr);
            }
        
            // then add it back (to demonstrate how)
            for (int m = 0; m < new_padding; m++)
            {
                fputc(0x00, outptr);
            }
        }

        // skip over padding, if any (move to next line in read file)
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
