#include "all.h"
#define LENGTH 256

struct option long_option[] = {
    {"help", 0, NULL, 'h'},
    {"enc", 1, NULL, 'e'},
    {"doc", 1, NULL, 'd'},
    {"output", 1, NULL, 'o'},
    {0, 0, 0, 0}
};

void Base64_decode(uint8_t a[3], uint8_t b[4]);
void toEncode(uint8_t a[4], uint8_t b[3]);
void print_help()
{
    printf("./hw0501 [options] \n");
    printf("-e, --enc Encode a file to a text file. \n");
    printf("-d, --dec Decode a text file to a file. \n");
    printf("-o, --output Output file name. \n");
    printf("\nGiven Example could be following... \n");
    printf("./hw0501 -e maldives.bmp -o maldives.txt \n");
    printf("./hw0501 -0 maldives.bmp -d maldives.txt \n");
}
static const unsigned char base64_List[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const unsigned char decode_List[] = 
{
    66,66,66,66,66,66,66,66,66,66,64,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,62,66,66,66,63,52,53,
    54,55,56,57,58,59,60,61,66,66,66,65,66,66,66, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,66,66,66,66,66,66,26,27,28,
    29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,
    66,66,66,66,66,66
};

int main(int32_t argc, char *argv[])
{
    int32_t         c = 0;
    int32_t         opt_e = 0;
    int32_t         opt_d = 0;
    int32_t         opt_o = 0;
    int32_t         opt_h = 0;
    char            fileName_input[LENGTH] = {0};
    char            fileName_output[LENGTH] = {0};
    FILE            *file_input = NULL;
    FILE            *file_output = NULL;
    uint8_t        array_input[3] = {0};
    uint8_t        array_base64[4] = {0};
    while((c = getopt_long(argc,argv,"e:d:o:h",long_option,NULL)) != -1)
    {   //get option
        switch (c)
        {
        case 'e':
                opt_e = 1;
                strncpy(fileName_input, optarg ,LENGTH);
            break;
        
        case 'd':
                opt_d = 1;
                strncpy(fileName_input, optarg ,LENGTH);
            break;
        
        case 'o':
                opt_o = 1;
                strncpy(fileName_output, optarg ,LENGTH);
            break;

        case 'h':
                opt_h = 1;
            break; 

        case '?':
                printf("Wrong Parameter. \n");
                return 0;
            break;
        }
    }

//=====After Parameter arg.=========

    if (opt_h) print_help();
    if (opt_e)
    {   
        file_input = fopen(fileName_input, "r+");
        file_output = fopen(fileName_output, "w");


        if ((file_input == NULL) || (file_output == NULL) )
        {
            perror("Error");
            return 0;
        }
        while(!feof(file_input))
        {
            int32_t     size = fread(array_input,1 , 3, file_input);
            toEncode(array_base64, array_input);
            if(size < 3)
            {
                for(int32_t i = 3; i > size; i--)
                {
                    array_base64[i] = '=';
                }
            } 
            fwrite(array_base64, 1, 4, file_output);
        }
        fclose(file_input);
        fclose(file_output);
    }
    
    if (opt_d)
    {
        file_input = fopen(fileName_input, "r+");
        file_output = fopen(fileName_output, "w");


        if ((file_input == NULL) || (file_output == NULL) )
        {
            perror("Error");
            return 0;
        }
        while (!feof(file_input))
        {
            int32_t     size = fread(array_base64 ,1, 4, file_input);
            Base64_decode(array_input, array_base64);
            fwrite( array_input, 1, 3, file_output);
        }
        fclose(file_input);
        fclose(file_output);
    }
    //maldives.bmp
    return 0;
}

void toEncode(uint8_t to[4], uint8_t from[3])
{

    to[0] = from[0] >> 2;
    to[1] = (((from[0] & 0x03) << 4) | (from[1] >> 4));
    to[2] = (((from[1] & 0x0F) << 2) | (from[2] >> 6));
    to[3] = (from[2] & 0x3F);
    to[0] = base64_List[ to[0] ];
    to[1] = base64_List[ to[1] ];
    to[2] = base64_List[ to[2] ];
    to[3] = base64_List[ to[3] ];

}

void Base64_decode(uint8_t to[3], uint8_t from[4])
{
    from[0] = decode_List[ from[0] ];
    from[1] = decode_List[ from[1] ];
    from[2] = decode_List[ from[2] ];
    from[3] = decode_List[ from[3] ];
    to[0] = (from[0] << 2 ) | ((from[1] & 0x30) >> 4);
    to[1] = ((from[1] & 0x0F) << 4) | ((from[2] & 0x3C) >> 2);
    to[2] = ((from[2] & 0x03) << 6) | (from[3]);
}

/*
    ./hw0501 -e maldives.bmp -o maldives.txt
    ./hw0501 -0 maldives.bmp -d maldives.txt
*/