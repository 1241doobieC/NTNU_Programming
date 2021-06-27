#include "all.h"
#define NAME 128
struct option long_option[] = {
    {"help", 0, NULL, 'h'},
    {0, 0, 0, 0}
};

typedef struct variable{
    char origin[32];
    char modified[16];
    int32_t isOccupied;
} _sVariable;

FILE *checkValid(char* mode);

void call_HELP()
{
    printf("./hw0402 -l [options] -i [input file] -o [output file] \n");
    printf("./hw0402 -h\n");
    printf("./hw0402 --help \n");
    printf(" Display this help manual. \n");
}

int main(int32_t argc, char *argv[])
{
    int32_t     c = 0;
    int32_t     level = 0;
    int32_t     opt_l = 0;
    int32_t     opt_i = 0;
    int32_t     opt_o = 0;
    int32_t     opt_h = 0;
    int32_t     instr = 0;
    char        input_filename[32] = "";
    char        output_filename[32] = "";

    srand(time(0));

    while((c = getopt_long(argc,argv,"l:i:o:h",long_option,NULL)) != -1){   //get option
        switch(c){
            case 'l':
                opt_l = 1;
                level = (int32_t)strtol(optarg,NULL,10);
                break;
            case 'i':
                opt_i = 1;
                strncpy(input_filename,optarg,strlen(optarg));
                break;
            case 'o':
                opt_o = 1;
                strncpy(output_filename,optarg,strlen(optarg));
                break;
            case 'h':
                call_HELP();
                break;
        }
    }

    if (opt_l && opt_i && opt_o)
    {
        FILE* input_file = NULL;
        FILE* output_file = NULL;
        FILE* tmp_file = NULL;
        int32_t isString = 0;
        char str[1024] = "";
        _sVariable var[128] = {0};

        if(( (input_file = fopen(input_filename,"rb")) == NULL) || ((output_file = fopen(output_filename,"wb+")) == NULL) || ((tmp_file = fopen("tmp.c","wb+")) == NULL) ){
            perror("Error");
            return 0;
        } 
        if(level == 1)
        {
        while(!feof(input_file))
        {
            char line[200]={0};              
            fgets(line,200,input_file);
            for(int i=0; i<strlen(line); i++)
            {
                if(instr == 0)
                {
                    if(line[i] == ',' || line[i] == ';' || line[i] == '[' || line[i] == '(')
                    {
                        int randnum = rand()%4;
                        if(randnum == 0 || randnum == 1)
                        {
                            int randspace = rand()%100;
                            for(int k=0; k<randspace; k++)
                            {
                                fputc(' ',output_file);
                            }
                        }
                    }
                }
                if(line[i] == '"')
                {
                    if(instr){
                        instr = 0;
                    }
                    else
                    {
                        instr = 1;
                    }
                }
                else if(line[i] == '\\')
                {
                    fputc(line[i],output_file);
                    i++;
                }
                fputc(line[i],output_file);
            }
        }
    }
        
    }
    
    return 0;
}
