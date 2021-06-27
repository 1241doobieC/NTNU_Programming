#include "all.h"


#define NAME 32
#define NEW_NAME 64
#define SIZE_NAME 32
struct option long_opts[] = 
{
    {"size",1,NULL,'z'},
    {"help",0,NULL,'h'},
    {0, 0, 0, 0}
};

void helpMe();

int main(int argc, char* argv[])
{   
    if (argc < 2)
    {
        printf("Wrong Parameter! \n");
        return 0;
    }
    FILE            *rv_File = NULL;
    FILE            *orig_File = NULL;
    char            old_fileName[NAME] = {0};
    char            input_size[SIZE_NAME] = {0};
    char            rv_fileName[NAME] = {0};
    int32_t         s = 0;
    int32_t         r = 0;
    int32_t         size = 1000;
    int32_t         v_getopt = 0;
    int32_t         split = 0;
    int32_t         recover = 0;
    int32_t         cg_size = 0; 
    int32_t         num_NOT_array = 0;
    long            fz = 0;
    uint32_t        num = 0;
    uint8_t         *buf = NULL;
    int32_t         count = 0;
    while ((v_getopt = getopt_long(argc, argv, "s:r:",long_opts , NULL )) != -1)
    {
        switch (v_getopt)
        {
        case 's':
            split = 1;
            strncpy(old_fileName, optarg, NAME);
        break;
        case 'r':
            recover = 1;
            num_NOT_array = optind;
            strncpy(rv_fileName,optarg, NAME);
        break;
        case 'z':
            cg_size = 1;
            strncpy(input_size, optarg, SIZE_NAME);
        break;
        case 'h': //done
            helpMe();
        break;
        case '?':
            printf("Wrong Input. \n");
            return 0;
        break;
        }
    }

    char            **trash = NULL;
    //========Important to know the size ===========
    if(cg_size)  size = (int32_t)strtol(input_size,trash,10); //receive the new file size
    //==============================================
    if (split)
    {
        uint8_t         number = 1;
        int32_t         leng = 0; 
        if ( (orig_File = fopen(old_fileName,"rb")) == NULL)
        {
            perror("Error");
            return 0;
        }
        else
        {   
            fz = ftell(orig_File);
            num = (uint32_t)ceil(((double)fz / size));
            while(!feof(orig_File))
            {
                char            new_fileName[NEW_NAME]= {0};
                FILE            *output = NULL;
                int32_t         order = 0;
                uint8_t         cnt = 0;
                strncpy(new_fileName, old_fileName, NAME);
                leng = strlen(new_fileName);
                new_fileName[leng] = '.';
                new_fileName[leng + 1] = 48 + number;
                new_fileName[leng + 2] = '\0';
                printf("%s ", new_fileName);
                //====================
                order = number;
                output = fopen(new_fileName, "wb");
                fwrite(&number, sizeof(uint8_t), 1 , output);
                uint8_t *dataarr = calloc(size,sizeof(uint8_t));
                cnt = fread(dataarr,sizeof(uint8_t),size,orig_File);
                fwrite(dataarr,1,cnt,output);
                number++;
                fclose(output);
                //./hw0401 -s a.out --size 100000
            }
            printf("\n");
            fclose(orig_File);
        }
        
    }
    
    if(recover)
    {
        if ( (rv_File = fopen(rv_fileName,"rb")) == NULL)
        {
            perror("Error");
            return 0;
        }

        if (argc < 4)
        {
            printf("Wrong Parameter \n");
            return 0;
        }
            while(num_NOT_array < argc && argv[num_NOT_array][0] != '-'){
            
            if(( orig_File = fopen(argv[num_NOT_array],"rb")) == NULL){
                perror("Error");
                return 0;
            }

            fread(&num,sizeof(num),1,orig_File);
            fread(&size,sizeof(size),1,orig_File);

            buf = (uint8_t*)malloc(sizeof(uint8_t) * size);
            count = fread(buf,1,size,orig_File);

            fseek(rv_File,size * (num - 1),SEEK_SET);
            fwrite(buf,1,count,rv_File);

            fclose(orig_File);          

            num_NOT_array++;
            free(buf);
        }

        fclose(rv_File);
        
    }
    
    return 0;
}

void helpMe()
{
    printf("Split: \n"); 
    printf("./hw0401 -s [file] --size [Small File Size] \n");
    printf("The default small file size is 1000 bytes. \n");
    printf("Recover: \n");
    printf("./hw0401 -r [output file] [small files] \n");
    printf("The input small files may not be in order. \n");
}