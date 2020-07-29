#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCK_SIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover infile\n");
        return 1;
    }
    
    //file adress
    char *fadress = argv[1];
    
    
    // open input file
    FILE *inptr = fopen(fadress, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", fadress);
        return 2;
    }

    BYTE buffer[512];
    int imageCount = 0;

    char filename[8];
    FILE *outptr = NULL;
    // read a block(512) of the memory
    size_t bytesRead = fread(buffer, sizeof(BYTE), BLOCK_SIZE, inptr);
    while (bytesRead > 0 && !feof(inptr))
    {
        // check if it is a JPEG
        bool containsJpegHeader = buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;

        // close the last JPEG
        if (containsJpegHeader && outptr != NULL)
        {
            fclose(outptr);
            imageCount++;
        }

        // open a new JPEG
        if (containsJpegHeader)
        {
            sprintf(filename, "%03i.jpg", imageCount);
            outptr = fopen(filename, "w");
        }

        // write open file
        if (outptr != NULL)
        {
            fwrite(buffer, sizeof(BYTE), bytesRead, outptr);
        }
        size_t bytesRead = fread(buffer, sizeof(BYTE), BLOCK_SIZE, inptr);
    }

    // close last jpeg file
    fclose(outptr);

    // close original file
    fclose(inptr);

    // success
    return 0;
}