#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define NAME 1024
#define CONTENT 1024
#define TRUE 1
#define FALSE 0

//==========================
#define KNRM  "\x1b[0m"
#define KRED  "\x1b[31m"
#define KGRN  "\x1b[32m"
#define KYEL  "\x1b[33m"
#define KBLU  "\x1b[34m"
#define KMAG  "\x1b[35m"
#define KCYN  "\x1b[36m"
#define KWHT  "\x1b[39m"
//==========================

/*Global Variable for character and color*/
char          character[16][256]={0}; //Name, Color and message
int32_t       person = 0;
char *pLRC(char *line, double *pTime);

int32_t       color[8] = {0};
int32_t       count = 0;
int32_t       ttt = 0;
int32_t       saved_Character = 0; //already exist
int32_t       basic = 49;
int32_t       choice = 0;
int32_t       gg = 0;

int main()
{
    FILE         *pFile = NULL;
    int32_t      temp = 0;
    char         fileName[NAME] = {0};
    char         ckFile[NAME] = {0};
    int32_t      flag = FALSE;

    printf("Open a LRC file: ");
    if ((fgets(fileName, sizeof(fileName), stdin)) == NULL)
    {
        printf("Error");
        return 0;
    }
    temp = strlen(fileName);
    if (fileName[temp - 1] == '\n')
        fileName[temp - 1] = 0;
    if ((pFile = fopen(fileName, "r")) == NULL)
    {
        printf("File could not be opened!\n");
        perror("Error");
        return 0;
    }
    temp = 0;

    char         *token = strtok(fileName, ".");
    int32_t       count = 0;
    int32_t       i = 0;

    while (token != NULL)
    {
        if ((temp = strncmp(token, "lrc", 3)) == 0)
        {
            flag = TRUE;
            break;
        }
        token = strtok(NULL, ".");
    }
    if (flag == FALSE)
    {
        printf("File doesn't end with lyc. \n");
        return 0;
    }

    char          content[CONTENT] = {0};
    char         *check = NULL;
    double        time[ 3 ] = {0};
    double        tmp_time[ 2 ] = {0};
    int32_t       minisecond = 0;
    while(fgets(content,CONTENT,pFile))
    {
        tmp_time[1] = time[1];
        tmp_time[0] = time[0];

        pLRC(content, time);//parse lrc

        if (time[1] == tmp_time[1] && tmp_time[0] == time[0])
        {
            minisecond = 0;
            usleep(minisecond);
        }
    }  
    fclose(pFile);
    return 0;
}

char *pLRC(char *line, double *pTime)
{   
    char         *p = NULL;
    char         *t = NULL;
    int32_t       leng = strlen(line);  // there are \0 and \n at the end
    char          songL[CONTENT] = {0};
    strncpy(songL, line, leng);
    p = strrchr(songL, ']');
    t = strrchr(songL, ':');

    int32_t       test = 0;
    int32_t      position = strrchr(line, ']') - line;
    int32_t      min = position - 8;
    int32_t      second = position - 5; 
    char         real_Mins[3] = {0};
    char         real_Seconds[6] = {0};
    int32_t      tmp_m = pTime[0];
    int32_t      tmp_s = pTime[1];


    for (int32_t i = 0; i < 2; i++)
    {
        real_Mins[i] = songL[i+1];
    }
    real_Mins[2] = '\0';
    for (int32_t i = 0; i < 5; i++)
    {
        real_Seconds[i] = songL[i+4];
    }
    real_Seconds[5] = '\0';
    double      seconds = atof(real_Seconds);
    int         mins = atoi(real_Mins);
    double      copyNum = 0;

//time check
    if(seconds == 0 && mins == 0 )
    {
        pTime[2] = 0;
    }
    else
    {
        if (pTime[0] == 0 && pTime[1] == 0 && pTime[2] == 0)
        {
            usleep(seconds * 1000 * 1000);
            pTime[1] = seconds;
            pTime[2] = seconds;
        }
        else
        {
            copyNum = pTime[1];
            pTime[2] = seconds - pTime[1]; 
            pTime[1] = seconds;
            if (pTime[2] < 0)
            {
                pTime[2] = seconds + (60.0 - copyNum);
            }
            usleep(pTime[2] * 1000 * 1000);
        }
    } 
    int32_t         setting = 0;
    if (p == NULL)
    {
        int32_t     flag = 0;
        if(t != NULL && p == NULL)
        {
            if (person == 0)
            {
                strncpy(character[person],songL ,leng);
                flag = 0;
                choice = basic;
                basic++;
                person++;
            }
            else
            {
                // p = strrchr(songL, ']');
                // t = strrchr(songL, ':');
                for (int32_t i = 0; i < 8; i++)
                {
                    if ( (strncmp(character[i] , songL, leng)) == 0 )
                    {
                        flag = 1; //exist
                        ttt = i;

                        switch (ttt)
                            {
                            case 0:
                                choice = 49;
                            break;
                            case 1:
                                choice = 50;
                            break;
                            case 2:
                                choice = 51;
                            break;
                            case 3:
                                choice = 52;
                            break;
                            case 4:
                                choice = 53;
                            break;
                            case 5:
                                choice = 54;
                            break;
                            case 6:
                                choice = 55;
                            break;
                            case 7:
                                choice = 56;
                            break;
                            }  
                    break;
                    }
                }
                if (flag == 0)
                {
                    strncpy(character[person],songL ,leng);
                    choice = basic;
                    basic++;
                    person++;
                }
            }
        } 
        return p;    
    }
    else
    {
        for (int32_t i = position+1 ; songL[i] != '\0' ; i++)
        {
            if (songL[ position+3 ] == '\0' && songL[ position+2 ] == '\0'){}
            else 
            {
                switch (choice)
                {
                    case 49:
                    printf( KNRM"%c", songL[i]);
                    break;
                    case 50:
                    printf( KRED"%c", songL[i]);
                    break;
                    case 51:
                    printf( KGRN"%c", songL[i]);
                    break;
                    case 52:
                    printf( KYEL"%c", songL[i]);
                    break;
                    case 53:
                    printf( KBLU"%c", songL[i]);
                    break;
                    case 54:
                    printf( KMAG"%c", songL[i]);
                    break;
                    case 55:
                    printf( KCYN"%c", songL[i]);
                    break;
                    case 56:
                    printf(KWHT"%c", songL[i]);
                    break;
                }   
            }
        }  
    }
}
//p.f.o.lrc