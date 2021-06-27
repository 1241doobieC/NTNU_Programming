#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#define NAME 128

typedef struct _sBmpHeader
{
    char    	bm[2];
    uint32_t	size;
    uint32_t	reserve;
    uint32_t	offset;
    uint32_t	header_size;
    uint32_t	width;
    uint32_t	height;
    uint16_t	planes;
    uint16_t	bpp;
    uint32_t	compression;
    uint32_t	bitmap_size;
    uint32_t	hres;
    uint32_t	vres;
    uint32_t	used;
    uint32_t	important;
}__attribute__ ((__packed__))  BMPHeader;

int main()
{
//===============Pre-Work===============
    FILE            *input_FileName = NULL;
    FILE            *output_FileName = NULL;
    char            input[NAME] = {0};
    char            output[NAME] = {0};
    int32_t         angle = 0;
    BMPHeader       bmpHeader = {0};

    printf("Please input a BMP file: ");
    fgets(input, NAME, stdin);
    if (input[strlen(input) - 1] == '\n') input[strlen(input) - 1] = 0;
    if((input_FileName = fopen(input, "rb")) == NULL)
    {
        printf("File Could Not be Opened. \n");
        return 0;
    }
    if( (strncmp(&input[strlen(input) - 4], ".bmp", 4) != 0))
    {
        printf("File Name is Invalid. \n");
        return 0;
    }
    printf("Please input the output BMP file name: ");
    fgets(output, NAME, stdin);
    if(output[strlen(output) -1] == '\n') output[strlen(output) - 1] = 0;
    if ( (output_FileName = fopen(output, "wb")) == NULL )
    {
        printf("File Could Not be Opened. \n");
        return 0;
    }
    if((strncmp(&output[strlen(output) - 4], ".bmp", 4) != 0))
    {
        printf("File Name is Invalid. \n");
        return 0;
    }
    printf("Angle: ");
    scanf("%d", &angle);
    if (angle < 0 || angle > 90)
    {
        printf("Invalid Angle \n");
        return 0;
    }
//======================================
    if (angle == 90)
    {   // Nothing actually happens
        fread(&bmpHeader, sizeof(BMPHeader), 1, input_FileName);
        fwrite(&bmpHeader, sizeof(BMPHeader), 1, output_FileName);
        while(!feof(input_FileName))
        {
            uint8_t     buffer[512] = {0};
            int32_t     count = fread(buffer, 1, 512, input_FileName); //Take 512 at once
            fwrite(buffer, count, 1, output_FileName);
        }
    }
    else if( angle == 0)
    {   //Becomes a line
        fread(&bmpHeader, sizeof(BMPHeader), 1, input_FileName);
        bmpHeader.width *=2; //width becomes two times
        bmpHeader.height = 1; //Same
        fwrite(&bmpHeader, sizeof(BMPHeader), 1, output_FileName);
        uint8_t *x = NULL;
        uint8_t y = 0;
        y = bmpHeader.width * 3 + bmpHeader.width % 4;  //From Corgi
        x = (uint8_t *)malloc(sizeof(uint8_t)* y);
        for (int32_t i = 0; i < y; i++)
        {
            x[i] = 0;
        }
        fwrite(x, 1, y, output_FileName);
    }
    else if(angle < 90 && angle > 0)
    {
//==================Pre-Work==================
        double      slope = 0;
        int32_t     ch_wid = 0;
        uint8_t     *old_x = NULL;
        uint8_t     *new_x = NULL;
        int32_t     old_y = 0;
        int32_t     new_y = 0;
        fread(&bmpHeader, sizeof(BMPHeader), 1, input_FileName);
    /**/
        bmpHeader.compression = 0;
        bmpHeader.bpp = 24;
        bmpHeader.header_size = 40;
        bmpHeader.offset = 54;
        // bmpHeader.bitmap_size = 3279360;
        // bmpHeader.height = 854;
        // bmpHeader.hres = 9449;
        // bmpHeader.vres = 9449;
    /**/
        slope = tan(angle * M_PI /180.0);
        ch_wid = (int32_t)(bmpHeader.height * (1.0 / slope));
        bmpHeader.width += ch_wid;
        fwrite(&bmpHeader, sizeof(BMPHeader), 1, output_FileName);
//============================================
        old_y = (bmpHeader.width - ch_wid) * 3 + (bmpHeader.width - ch_wid) % 4;
        new_y = (bmpHeader.width) * 3 + (bmpHeader.width) % 4;
        old_x = (uint8_t *)malloc(sizeof(uint8_t) * old_y);
        new_x = (uint8_t *)malloc(sizeof(uint8_t) * new_y);

        for (int32_t i = 0; i < bmpHeader.height; i++)
        {
            fread(old_x, 1, old_y, input_FileName);

            for (int32_t j = 0; j < new_y; j++)
            {
                new_x[j] = 255; //White
            }
            for (int32_t pixel = 0; pixel < new_y; pixel= pixel +3)
            {
                if (slope * pixel / 3 - i >= 0)
                {
                    for (int32_t w = 0; w < old_y; w++)
                    {
                        new_x[pixel + w] = old_x[w];
                    }
                    fwrite(new_x, 1 , new_y, output_FileName);
                    break;
                }
            }
        }
    }
    else
    {
        printf("Error: Invalid Input. \n");
        fclose(input_FileName);
        fclose(output_FileName);
        return 0;
    }
    
    fclose(input_FileName);
    fclose(output_FileName);
    return 0;
}
//naruto.bmp