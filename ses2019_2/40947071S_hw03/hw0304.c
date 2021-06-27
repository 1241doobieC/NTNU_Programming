#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

#define NAME 256


struct _sBmpHeader
{
    char		bm[2];
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
}__attribute__ ((__packed__));

typedef struct _sBmpHeader sBmpHeader;

FILE *checkValid(char* mode);
int main()
{
    FILE        *input_FileName = NULL;
    FILE        *output_FileName = NULL;
    uint8_t     alpha = 0;
    printf("Please input a BMP file:");
    input_FileName = checkValid("rb");
    if (input_FileName == NULL) return 0;
    printf("Please input the output BMP file name:");
    output_FileName = checkValid("wb");
    if( output_FileName == NULL) return 0;

    printf("Alpha (0-31): ");
    scanf("%hhd",&alpha);
    if(alpha < 0 || alpha > 31)
    {
        printf("Invalid Value\n");
        return 0;
    }
    sBmpHeader header = {0};
    fread(&header, sizeof(header), 1, input_FileName);
    if(header.bpp != 24)
    {
        printf("Input BMP is not a 24-bit depth\n");
        return 0;
    }
    header.size = 70 + header.width * header.height * 4;
    header.offset = 70;
    header.header_size = 56;
    header.bpp = 32;
    header.compression = 3;
    header.bitmap_size = header.width * header.height * 4;
    uint32_t mask[4] = {0x00FF0000,0x0000FF00,0x000000FF,0xFF000000};
    fwrite(&header, sizeof(header), 1, output_FileName);
    fwrite(&mask, sizeof(uint32_t), 4, output_FileName);
    int32_t rpixel = header.width * 3 + header.width % 4;
    int32_t wpixel = header.width * 4;
    uint8_t *rpixelarr = malloc(sizeof(uint8_t) * rpixel);
    uint8_t *wpixelarr = malloc(sizeof(uint8_t) * wpixel);
    while(!feof(input_FileName))
    {
        fread(rpixelarr, 1, rpixel, input_FileName);
        int writepos = 0;
        for(int32_t i = 0; i < header.width * 3; i++)
        {
            if(writepos % 4 == 3)
            {
                wpixelarr[writepos] = alpha;
                writepos++;
            }
            wpixelarr[writepos] = rpixelarr[i];
            writepos++;
        }
        fwrite(wpixelarr, 1, wpixel, output_FileName);
    }
    fclose(input_FileName);
    fclose(output_FileName);
    return 0;
}

FILE *checkValid(char* mode)
{
    char        name[NAME] = {0};
    FILE        *check = NULL;
    fgets(name, NAME, stdin);
    if (name[strlen(name) - 1] == '\n') name[strlen(name) - 1] = 0;
    if( (check = fopen(name, mode)) == NULL )
    {
        printf("File Could not be opened. \n");
        return NULL;
    }
    if( (strncmp(&name[strlen(name) - 4], ".bmp", 4) != 0))
    {
        printf("File Name is Invalid. \n");
        return NULL;
    } 

    return fopen(name, mode);
}
//maldives.bmp