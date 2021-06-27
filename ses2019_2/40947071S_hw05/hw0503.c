#include "all.h"
#include <cjson/cJSON.h>
#include <curl/curl.h>

#define LENGTH 8192

void print_help()
{
    printf("Format should be following: \n");
    printf("\n./hw0503 -q YOUR_KEYWORK\n");
}

size_t test_function(char *buffer, size_t itemsize, size_t nitems, void *garbage)
{
    size_t bytes = itemsize * nitems;
    // printf("Chunk (%zu bytes) \n", bytes);
    int32_t line_num = 1;
    printf("%d:\t", line_num);

    for(int32_t i = 0; i < bytes; i++)
    {
        printf("%c", buffer[i]);
        if (buffer[i] == '\n')
        {
            line_num++;
            printf("%d:\t", line_num);
        }
        
    }
    printf("\n\n");
    return bytes;
}

int main(int argc, char *argv[])
{
    int         ch = 0;
    int32_t     opt_q = 0;
    int32_t     opt_default = 0;
    char        addr[LENGTH] = "https://dblp.org/search/publ/api?format=json&h=10&q=";
    char        buffer[LENGTH] = {0};
    int32_t     ct_buffer = 0;
    while( (ch = getopt(argc, argv, "q:h")) != -1)
    {
        switch(ch)
        {
            case 'q':
                opt_q = 1;
                strncpy(buffer, optarg, LENGTH);
            break;
            case 'h':
                print_help();
            break;
            case '?':
                opt_default = 1;
            break;
        }

    }
    
    if(opt_default)
    {
        printf("Please Submit a Valid argument! \n");
        return 0;
    }

    if(opt_q)
    {
        for (int32_t i = strlen(addr); i < strlen(addr) + strlen(buffer); i++)
        {
            addr[i] = buffer[ct_buffer];
            ct_buffer++;
        }
        
        CURL    *curl = curl_easy_init();
        FILE    *bufferFile = NULL;
        CURLcode result;
        if(!curl)
        {
            fprintf(stderr, "Initialized Failed. \n");
            return 0; 
        }
        
        //set options
        curl_easy_setopt(curl, CURLOPT_URL, addr);
        bufferFile = fopen("abc.json","w");
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, bufferFile);

        //perform out action
        result = curl_easy_perform(curl);
        if (result != CURLE_OK) fprintf(stderr, "Download Problem: %s. \n", curl_easy_strerror(result));

        /*
            It is important to close the file here!!
            otherwise the file size could [NOT] be read.
        */
        fclose(bufferFile);

    //============CJSON===============

        FILE        *file_json = NULL;
        int32_t     size = 0;
        cJSON       *json = NULL;
        int64_t     length = 0;  //file lenth
        char        *content = NULL; //file content

        file_json = fopen("abc.json", "rb");
        if (!file_json) perror("ERROR:");
        
        //length for a malloc 
        fseek(file_json,0 ,SEEK_END );
        length = ftell(file_json);
        fseek(file_json, 0, SEEK_SET);
        content = (char *)malloc(length + 1);

        size = fread(content ,1, length , file_json);
        if (size <=0)
        {
            printf("Error:Empty file. \n");
            return 0;
        } 
    //=======
        json = cJSON_Parse(content);
        if (!json) fprintf(stderr, "Error: %s \n",  cJSON_GetErrorPtr());
        
        /**/
        cJSON       *title = NULL;
        cJSON       *author = NULL;
        cJSON       *source = NULL;
        cJSON       *volume = NULL;
        cJSON       *nummer = NULL;
        cJSON       *pages = NULL;
        cJSON       *year = NULL;
        /**/
        cJSON       *value = NULL;
        cJSON       *value2 = NULL;
        char        *query = NULL;
        int32_t     to_cut = '"';
        int32_t     element_count = 0;
        int32_t     i = 0;  //take out the first one
        value = cJSON_GetObjectItem(json, "result");
        if (!value)
        {
            printf("Get Object Item fail. \n");
            return 0;
        } 
        value = cJSON_GetObjectItem(value, "hits");
        value2 = cJSON_GetObjectItem(value, "hit");
        if (!value2)
        {
            printf("Result: No matches! \n");
            return 0;
        }
        
        element_count = cJSON_GetArraySize(value2);
        if (element_count > 10) element_count = 10;
        for (int32_t i = 0; i < element_count; i++)
        {
            //=====
            value = cJSON_GetArrayItem(value2 , i);
            value = cJSON_GetObjectItem(value, "info");  //Original one
            
            title = cJSON_GetObjectItem(value, "title");
            year = cJSON_GetObjectItem(value, "year");
            source = cJSON_GetObjectItem(value, "venue");
            volume = cJSON_GetObjectItem(value, "volume");
            nummer = cJSON_GetObjectItem(value, "number");
            pages = cJSON_GetObjectItem(value, "pages");
            cJSON       *tmp = cJSON_GetObjectItem(value, "authors");
            //=====
            query = cJSON_Print(title);
            if (!query) {printf("No Matches. \n");}
            else
            {
                printf("Paper%d: \n", i+1);
                printf("\tTitle: ");
                while(*query != '\0')
                {
                    if (*query == '"')
                    {
                        *query++;
                    }
                    else printf("%c", *query++);
                } 
            } 

            printf("\n\tAuthor(s): ");
            
            tmp = cJSON_GetObjectItem(tmp, "author");
            int32_t     count_tmp =cJSON_GetArraySize(tmp);
            cJSON       *arrayItem_tmp = NULL;
            for (int32_t j = 0; j < count_tmp; j++)
            {
                arrayItem_tmp = cJSON_GetArrayItem(tmp, j);
                author = cJSON_GetObjectItem(arrayItem_tmp, "text");
                query = cJSON_Print(author);
                if (!query) {printf("No Matches."); break;}
                else
                {
                    while(*query != '\0')
                    {
                        if (*query == '"')
                        {
                            *query++;
                        }
                        else printf("%c", *query++);
                    } 
                    if (j != count_tmp-1)
                    {
                        printf(", ");
                    }
                    
                }
            }
            printf("\n");
            
            query = cJSON_Print(source);
            if (!query) printf("\n");
            else
            {
                printf("\tSources: ");
                while(*query != '\0')
                {
                    if (*query == '"' || *query == '[' || *query == ']')
                    {
                        *query++;
                    }
                    else printf("%c", *query++);
                } 
                printf(" ");
                if (volume)
                {
                    query = cJSON_Print(volume);
                    while(*query != '\0')
                        {
                            if (*query == '"')
                            {
                                *query++;
                            }
                            else printf("%c", *query++);
                        } 
                }
                if (nummer)
                {
                   printf("(");
                    query = cJSON_Print(nummer);
                    while(*query != '\0')
                        {
                            if (*query == '"')
                            {
                                *query++;
                            }
                            else printf("%c", *query++);
                        } 
                   printf(")");
                }
                if(pages)
                {
                    printf(": ");
                    query = cJSON_Print(pages);
                    while(*query != '\0')
                        {
                            if (*query == '"')
                            {
                                *query++;
                            }
                            else printf("%c", *query++);
                        } 
                }
            } 
            printf("\n");
            query = cJSON_Print(year);
            if (!query) {printf("\n");}
            else
            {
                printf("\tYear:");
                while(*query != '\0')
                {
                    if (*query == '"')
                    {
                        *query++;
                    }
                    else printf("%c", *query++);
                } 
                printf("\n");
            } 
        }
    //============CJSON===============
        fclose(file_json);
        curl_easy_cleanup(curl);
    }

    return 0;
}

//encryption