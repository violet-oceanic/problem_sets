#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
 
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");

    if (card == NULL)
    {
        printf("Error opening  %s\n", argv[1]);
        return 1;
    }

    BYTE buffer[512];
    char filename[8];
    int count = 0;

    FILE *output = NULL;


    while (fread(buffer, 512, 1, card) != 0)
    {
        //printf("0=%p\n", &buffer[0]);
        //printf("1=%p\n", &buffer[1]);
        //printf("2=%p\n", &buffer[2]);
        //printf("3=%p\n", &buffer[3]);
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (count != 0)
            {
                fclose(output);
            }
            sprintf(filename, "%03i.jpg", count);
            //printf(" > filename=%s\n", filename);
            output = fopen(filename, "w");
            fwrite(buffer, 512, 1, output);
            count++;
        }
        else
        {
            if (output != NULL)
            {
                fwrite(buffer, 512, 1, output);
            }
        }
    }

    fclose(output);
    fclose(card);
    return 0;

}