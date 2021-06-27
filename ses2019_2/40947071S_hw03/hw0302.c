#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define NAME 128
#define INFO 256
#define EXIST 1
#define NONEXIST 0

typedef struct ssRecord
{
    char        name[NAME]; //Team name
    int32_t     exist;      //(Ini)
    int32_t     point;
//============================
    int32_t     win;
    int32_t     draw;       //(1)Winner
    int32_t     lose;
//============================
    int32_t     homeGoal;   //(2)Scores
    int32_t     awayGoal;
//============================
    int32_t     redCard;    //(3) red cards
//============================
    int32_t     winH;
    int32_t     winA;       //(4) most games

} __attribute__((packed)) sRecord;

int32_t     differ = 0; // caculate difference for each game
char        hVS[NAME] = {0};
char        aVS[NAME] = {0};
char        dateVS[NAME] = {0};
int32_t     score_HomeVS = 0;
int32_t     score_AwayVS = 0;

void gDataStorage(FILE *a, sRecord *b);

int main(){
    FILE         *pFile = NULL;
    char         fileName[NAME] = {0};
    int32_t      temp = 0;
    int32_t      choice = 0;
    sRecord      team[INFO] = {0};
//==================Pre-Work===========================
    printf("Please open a season record:");
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
//=====================================================
    printf("1) Who is the winner in this season? \n");
    printf("2) Which team gets the most scores? \n");
    printf("3) Which team gets the most red cards? \n");
    printf("4) Which team wins the most games at home?\n");
    printf("5) Which team wins the most games away from home?\n");
    printf("6) Which game has the most scoring gap?\n");
    printf("7) Team information.\n");
    printf("8) Exit \n");

    gDataStorage(pFile, team);

    do
    {
        printf("Choice (1-7, 8:exit):");
        scanf("%d", &choice);
        int32_t     num = 0;
        int32_t     goals = 0;
        char        input[NAME] = {0};
        int32_t     point = 0;
        switch (choice)
        {
            case 1: //Who is the winner in this season?
            /*
                for (int32_t i = 0; i < 20; i++)
                {
                    printf("Team %s got %d points. \n", team[i].name, team[i].point);
                }
            */
                for (int32_t i = 0; i < 20; i++)
                {
                    for (int32_t j = 0; j <= i; j++)
                    {
                        if (point < team[i].point)
                        {
                            point = team[i].point;
                        }
                    }
                }
                for (int32_t i = 0; i < 20; i++)
                {
                    if(team[i].point == point)
                    {
                        printf("The Winner is %s. \n",team[i].name);
                    }
                }
                num = 0;
            break;
            case 2: //Which team gets the most scores? 
                goals = 0;
                for(int32_t i = 0; i < 20; i++)
                {
                    for (int32_t j = 0; j < 20; j++)
                    {
                        if (goals < team[j].homeGoal)
                        {
                            goals = team[j].homeGoal;
                        }
                    }
                }
                for (int32_t i = 0; i < 20; i++)
                {
                    if(team[i].homeGoal == goals)
                    {
                        printf("%s, %d\n",team[i].name, team[i].homeGoal);
                    }
                }
            break;
            case 3: //Which team gets the most red cards?
                goals = 0;
                for(int32_t i = 0; i < 20; i++)
                {
                    for (int32_t j = 0; j < 20; j++)
                    {
                        if (goals < team[j].redCard)
                        {
                            goals = team[j].redCard;
                        }
                    }
                }
                for (int32_t i = 0; i < 20; i++)
                {
                    if(team[i].redCard == goals)
                    {
                        printf("%s: %d \n",team[i].name, goals);
                    }
                }
            break;
            case 4: //Which team wins the most games at home?
                goals = 0;
                for(int32_t i = 0; i < 20; i++)
                {
                    for (int32_t j = 0; j < 20; j++)
                    {
                        if (goals < team[j].winH)
                        {
                            goals = team[j].winH;
                        }
                    }
                }
                for (int32_t i = 0; i < 20; i++)
                {
                    if(team[i].winH == goals)
                    {
                        printf("%s: %d \n",team[i].name, team[i].winH);
                    }
                }
                //season-1617_csv.csv
            break;
            case 5: //Which team wins the most games away from home?
                goals = 0;
                for(int32_t i = 0; i < 20; i++)
                {
                    for (int32_t j = 0; j < 20; j++)
                    {
                        if (goals < team[j].winA)
                        {
                            num = j;
                            goals = team[j].winA;
                        }
                    }
                }
                for (int32_t i = 0; i < 20; i++)
                {
                    if(team[i].winA == goals)
                    {
                        printf("%s: %d \n",team[i].name, team[i].winA);
                    }
                }
            break;
            case 6: //Which game has the most scoring gap?
                printf("%s, %s(%d) vs %s(%d) \n", dateVS, hVS, score_HomeVS, aVS, score_AwayVS);
            break;
            case 7: // Team information
                fgets(input, NAME, stdin);
                printf("Team: ");
                fgets(input, NAME, stdin);
                input[strlen(input)-1] = '\0';
                for(int32_t i = 0; i < 20; i++)
                {
                    if(strncmp(input, team[i].name, NAME) == 0)
                    {
                        printf("Points:%d \n", team[i].point);
                        printf("Win/ Draw/ Lose: %d/ %d/ %d \n", team[i].win, team[i].draw, team[i].lose);
                        printf("Goals Scored/ Goals Against: %d/ %d \n", team[i].homeGoal, team[i].awayGoal);
                        break;
                    }
                    if (i == 19) printf("No such team. \n");
                    
                }
            break;
            case 8:
                fclose(pFile);
            return 0;
            break;
            default:
                printf("Wrong Command! \n");
            break;
        }
    } while (choice);
}

void gDataStorage(FILE *record, sRecord *teamInfo)
{
    char        data[999] = {0};
//================================
    char        homeT[NAME] = {0};
    char        awayT[NAME] = {0};
    char        date[NAME] = {0};
    int32_t     FTHG = 0;
    int32_t     FTAG = 0;
    char        result = 'a';
    int32_t     win = 0;
    int32_t     draw = 0;
    int32_t     lose = 0;
    int32_t     homeR = 0;
    int32_t     awayR = 0;
//================================
    char        *p = NULL;
    int32_t     leng = 0;
    int32_t     order = 1;
    int32_t     temp = 0;
    while ( (p = fgets(data, 999, record) ) != NULL )
    {
        data[ strlen(data) - 1 ] = '\0';

        if (order == 1)
        {
            order = 0;
            continue;
        }
        
        sscanf(data, "%[^,],%[^,],%[^,],%d,%d,%c,%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%d,%d,%*s"
               ,date,homeT,awayT, &FTHG, &FTAG, &result, &homeR, &awayR); 
//========Home Team=========
        for (int32_t i = 0; i < 20; i++)
        {
            if ( (strncmp(teamInfo[i].name, homeT, sizeof(homeT)) == 0) || (teamInfo[i].exist == NONEXIST) ) //Nonexist
            {
                if (teamInfo[i].exist == NONEXIST)
                {
                    teamInfo[i].exist = EXIST;
                    strncpy(teamInfo[i].name, homeT, NAME);
                }
                if(result == 'H')
                {
                    teamInfo[i].point +=3;
                    teamInfo[i].win +=1;
                    teamInfo[i].winH +=1;
                }
                else if(result == 'A')
                {
                    teamInfo[i].lose +=1;
                }
                else if(result == 'D')
                {
                    teamInfo[i].point +=1;
                    teamInfo[i].draw +=1;
                }

                teamInfo[i].homeGoal += FTHG;
                teamInfo[i].awayGoal += FTAG;
                teamInfo[i].redCard += homeR;
                break;
            }
        }
//========Away Team=========
        for (int32_t i = 0; i < 20; i++)
        {
            if ( (strncmp(teamInfo[i].name, awayT, NAME) == 0) || (teamInfo[i].exist == NONEXIST) ) //Nonexist
            {
                if (teamInfo[i].exist == NONEXIST)
                {
                    teamInfo[i].exist = EXIST;
                    strncpy(teamInfo[i].name, awayT, NAME);
                }
                if(result == 'A')
                {
                    teamInfo[i].winA +=1;
                    teamInfo[i].point +=3;
                    teamInfo[i].win +=1;
                }
                else if(result == 'H')
                {
                    teamInfo[i].lose +=1;
                }
                else if(result == 'D')
                {
                    teamInfo[i].point +=1;
                    teamInfo[i].draw +=1;
                }

                teamInfo[i].homeGoal += FTAG;
                teamInfo[i].awayGoal += FTHG;
                teamInfo[i].redCard += awayR;
                break;
            }   
        }

        if (FTHG > FTAG) temp = FTHG - FTAG;
        else if (FTAG > FTHG) temp = FTAG - FTHG;
        else { } //No shitty thing happened
        if (temp > differ)
        {   
            differ = temp;
            strncpy(hVS, homeT, NAME);
            strncpy(aVS, awayT, NAME);
            strncpy(dateVS, date, NAME);
            score_HomeVS = FTHG;
            score_AwayVS = FTAG;
        }
    }


}
//season-1617_csv.csv