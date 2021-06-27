#include "all.h"
#define NAME 64

uint8_t signature[4] = {'P','K',3,4};

typedef struct{
    uint16_t version;
    uint16_t flags;
    uint16_t compression;
    uint16_t modtime;
    uint16_t moddate;
    uint32_t checksum;
    uint32_t compresssize;
    uint32_t uncompresssize;
    uint16_t filenamelen; //Only this is important
    uint16_t extralen;
}__attribute__ ((__packed__)) sZIP;

int main (int32_t argc, char *argv[])
{
    char        fileName[NAME] = {0};
    FILE        *file_zip = NULL;
    //Check for parameter
    if (argc < 2)
    {
        printf("Wrong Parameter! \n");
        return 0;
    } else strncpy(fileName, argv[1], NAME);

    int32_t         count = 0;
    int32_t         ind = 0;
    char            nameS[NAME][NAME] = {0};
    if( (file_zip = fopen(fileName, "rw")) == NULL)
    {
        printf("Error with ZIP file. \n");
        return 0;
    }
    else
    {
        printf(".\n");
        while( !feof(file_zip) )
        {
            if (count == 4)
            {
                sZIP *header = malloc(sizeof(sZIP));
                fread(header, sizeof(sZIP), 1 , file_zip);
                //========Parse============
                char        nameStr[(header -> filenamelen) +1];

                fread(nameStr,sizeof(uint8_t),header->filenamelen,file_zip);
                nameStr[header->filenamelen] = '\0';
                if (nameStr[header->filenamelen-1] == '/')
                {
                    strncpy(nameS[ind],nameStr, NAME);
                    while(strncmp(nameS[ind-1],nameStr,strlen(nameS[ind-1])) != 0 && ind != 0)
                    {
                        ind--;
                    }
                    nameStr[header->filenamelen-1] = '\0';
                    //========================
                    for (int32_t i = 0; i < ind; i++)
                    {
                        printf("    ");
                    }
                    printf("+-- ");
                    //========================
                    if(ind == 0) printf("%s",nameStr);
                    else
                    {
                        for(int i=strlen(nameS[ind-1]); nameStr[i] != '\0'; i++)
                        {
                            fputc(nameStr[i],stdout);
                        }
                    }
                    ind++;
                }
                else
                {
                     while(strncmp(nameS[ind-1],nameStr,strlen(nameS[ind-1])) != 0 && ind != 0)
                    {
                        ind--;
                    }
                    //========================
                    for (int32_t i = 0; i < ind; i++)
                    {
                        printf("    ");
                    }
                    printf("+-- ");
                    //========================
                    if (ind == 0)printf("%s ",nameStr);
                    else
                    {
                        for(int i=strlen(nameS[ind-1]); nameStr[i] != '\0'; i++)
                        {
                            fputc(nameStr[i],stdout);
                        }
                    }
                    
                }
                printf("\n");
                count = 0;
            }

            uint8_t *tmp = malloc(sizeof(uint8_t));
            fread(tmp,sizeof(uint8_t),1,file_zip);
            if(*tmp == signature[count])
            {
                count++;
            }
            else
            {  
                count = 0;
            }
            
        }
    }
    fclose(file_zip);
    return 0;
}