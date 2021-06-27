#include "all.h"

//define Functions
#define find(x) findCard(player ,numberOfPlayer, x)

//Global Variable
    char*           clean_screen = "\e[1;1H\e[2J";
    sCard           deck[139];
    sCard           discardDeck[139];
    int32_t         deckIndex = 0;
    int32_t         discardDeckIndex = 0;
    bool            profession_table[6] = {0};
    bool            bank_used_table[5] = {0};
    int32_t         price_table[5][6] = {{0, 1, 1, 1, 2, 2},  //販賣卡
                                         {0, 1, 1, 2, 2, 2},
                                         {0, 1, 1, 2, 2, 3},
                                         {0, 1, 2, 2, 2, 3},
                                         {0, 1, 2, 2, 3, 3}};
    int32_t*        price = NULL;

//Main Function!
int main()
{
    int32_t         choiceForMenu = 0;
    int32_t         numberOfPlayers = 0;
    bool            flagForPlayers = true;
    int32_t         governor = 0;
    int32_t         amount_InitializedCard = 0;
    int32_t         round = 1;
    int32_t         professionOfPlayer = 0;
    static int32_t  numberOfround = 1;
    int32_t         amountOfPlayers = 0;
    bool            isEnd = false;

    memset(deck, 0 , sizeof(sCard) * 139);
    memset(discardDeck , 0 , sizeof(sCard) * 139);
    memset(profession_table, 0, sizeof(bool) * 6);
    memset(bank_used_table, 0, sizeof(bool) * 5);

    srand(time(NULL));
    printIntroduction();
    choiceForMenu = showSelectionList();

    while(flagForPlayers)
    {
        switch (choiceForMenu)
        {
        case 1:
            numberOfPlayers = getPlayerNumber();
            if (numberOfPlayers < 2 || numberOfPlayers > 4)
            {
                printErrorMessage(WRONG_PLAYER_NUMBER);
            }
            else flagForPlayers = false;
                      
            break;
        case 2:
                printf("%s" , clean_screen);
                printf("\n\n\n\n\n");
                printf("　　　　　　　　　　　　　　　╔════════════════════════════════════════════════╗\n");
                printf("　　　　　　　　　　　　　　　║　　　　　　　　　　　　　　　　　　　　　　　　║\n");
                printf("　　　　　　　　　　　　　　　║　　　　　　　　　　　　　　　　　　　　　　　　║\n");
                printf("　　　　　　　　　　　　　　　║　　　　Ｅｎｄ　ｏｆ　ｔｈｅ　Ｇａｍｅ　　　　　║\n");
                printf("　　　　　　　　　　　　　　　║　　　　　　　　　　　　　　　　　　　　　　　　║\n");
                printf("　　　　　　　　　　　　　　　║　　　　　　　　　　　　　　　　　　　　　　　　║\n");
                printf("　　　　　　　　　　　　　　　╚════════════════════════════════════════════════╝\n");
                printf("\n\n\n\n\n");
                flagForPlayers = false;
                return 0;
            break;
        default:
                choiceForMenu = showSelectionList();
            break;
        }
    }
    
    //Initialize
    governor = rand() % numberOfPlayers + 1;
    /*
        特色設計：總督隨機or指定對象？
    */
    sPlayer *player = NULL;

    /*
    Memory Size of Player could be actual amount of total players. 
    But just for our convenience, we set one more unit.
    */
    player = (sPlayer *)malloc(sizeof(sPlayer) * (numberOfPlayers + 1));

    initialize_Player(player, numberOfPlayers);
    initialize_Deck();
    amount_InitializedCard = deckIndex;
    shuffle(amount_InitializedCard);
    cardDistribute(player, numberOfPlayers, governor);
    printf("\n\n\t棄牌完成，遊戲即將開始....");
    sleep(3);

    while(round)
    {
        printf("\n\n\tReminder:【回合%d， 總督為 %d 玩家。】\n", numberOfround, governor);  
        sleep(2);
        
        professionOfPlayer = governor;    
        round_start(player, numberOfPlayers, governor);

        for (int32_t i = 0; i < numberOfPlayers; i++) //玩家選擇職業
        {
            int32_t     action_NumberOfPlayer = professionOfPlayer; 
            int32_t     profession_choice = chooseProfession(player, numberOfPlayers, professionOfPlayer);
            bool        sellRecord = false;

            for (int32_t j = 0; j < numberOfPlayers; j++) //該職業進行特權
            {
                switch (profession_choice)
                {
                    case BUILDER: //建築工人
                        pro_Builder(player, numberOfPlayers, professionOfPlayer, action_NumberOfPlayer);
                        if(j == numberOfPlayers - 1)
                        {
                            amountOfPlayers = numberOfPlayers;
                            for(int32_t numberOfPlayer = 1; numberOfPlayer <= amountOfPlayers; numberOfPlayer++)
                            {
                                if(find(TAVERN)) tavern(player, amountOfPlayers, numberOfPlayer);

                            }
                            amountOfPlayers = 0;
                        }
                        break;
                    
                    case COUNCILLOR: //議員
                        pro_Councillor(player, numberOfPlayers, professionOfPlayer, action_NumberOfPlayer);
                        break;

                    case PRODUCER: //製造商
                        pro_Producer(player, numberOfPlayers, professionOfPlayer, action_NumberOfPlayer);
                        break;

                    case PROSPECTOR: //礦工
                        pro_Prospector(player, numberOfPlayers, professionOfPlayer, action_NumberOfPlayer);
                        break;

                    case TRADER: //貿易商
                        {
                            int32_t handcardBefore = player[action_NumberOfPlayer].number_cardOnHand;
                            pro_Trader(player, numberOfPlayers, professionOfPlayer, action_NumberOfPlayer);

                            if(handcardBefore != player[action_NumberOfPlayer].number_cardOnHand) 
                                sellRecord = true;
                            if(j == numberOfPlayers - 1 && !sellRecord)
                            {
                                amountOfPlayers = numberOfPlayers;
                                for(int32_t numberOfPlayer = 1;numberOfPlayer <= amountOfPlayers;numberOfPlayer++)
                                {
                                    if(find(COTTAGE)) cottage(player, amountOfPlayers, numberOfPlayer);
                                }
                                amountOfPlayers = 0;
                            }
                        }
                        break;
                    
                    default:
                        printf("\e[1;38;2;255;0;64m輸入值有誤。\n\e[m");
                        action_NumberOfPlayer--;
                        break;
                }
                
                

                //Prepare for next player to take action

                action_NumberOfPlayer++;
                if(action_NumberOfPlayer > numberOfPlayers) 
                    action_NumberOfPlayer = 1;

                if(game_end(player, numberOfPlayers))
                {
                    isEnd = true;
                    break;
                }
            }
            professionOfPlayer++;
            if(professionOfPlayer > numberOfPlayers) professionOfPlayer = 1; 

             if(isEnd) break;
        }
        
        governor++;
        if(governor > numberOfPlayers) governor = 1;

        numberOfround++;
    }
    
    amountOfPlayers = numberOfPlayers;

    for(int32_t numberOfPlayer = 1;numberOfPlayer <= amountOfPlayers ;numberOfPlayer++)
    {

        showCardsOnTable(player ,numberOfPlayers);
        printf("遊戲結束\n\n");
        if(find(GUILD_HALL)) guild_hall(player, numberOfPlayer);
        if(find(CITY_HALL)) city_hall(player, numberOfPlayer);
        if(find(TRIUMPHAL_ARCH)) triumphal_arch(player, numberOfPlayer);
        if(find(PALACE)) palace(player, numberOfPlayer);
        if(find(RESIDENCE)) residence(player, numberOfPlayer);

        if(!find(GUILD_HALL) && !find(CITY_HALL) && !find(TRIUMPHAL_ARCH) && !find(PALACE) && !find(RESIDENCE))
        {
            printf("%d 號玩家沒有【建築】點數加成效果。\n", numberOfPlayer);
        }

        sleep(2);
    }
    
     bool record[5] = {0};

    showCardsOnTable(player, amountOfPlayers);
    printf("排名如下：\n");

    for(int32_t i = 1;i <= amountOfPlayers;i++)
    {

        int32_t max = 0;
        int32_t maxNum = 0;

        for(int32_t numberOfPlayer = 1;numberOfPlayer <= amountOfPlayers;numberOfPlayer++)
        {
            if(record[numberOfPlayer]) continue;
            if(max < player[numberOfPlayer].pointsReceive)
            {
                max = player[numberOfPlayer].pointsReceive;
                maxNum = numberOfPlayer;
            }
        }

        record[maxNum] = true;

        if(maxNum == 1) printf("\t第%d名 → 玩家，  獲得: %d分。 \n", i, max);
        else printf("\t第 %d 名 → %d 號玩家　獲得: %d分。\n", i, maxNum, max);

    }
    printf("\n\n\t\t6秒過後遊戲結束 \n\n");
    sleep(6);
    //Free

    if(player != NULL) 
    {
        sCard* pre = NULL;
        sCard* now = player->cardOnHand;

        while(now != NULL)
        {
            pre = now;
            now = now->linkedListNext;
            free(pre);
        }
    }


    return 0;
}

//Before Start Function
    void            printErrorMessage(int32_t messageNumber)
{
    char c = 0;
    printf("%s", clean_screen);
    printf("\n\n\n\n\n\n\n\n\n");
    switch (messageNumber)
    {
    case WRONG_PLAYER_NUMBER:
        printf("\e[1;38;2;255;0;64m輸入值有誤。\n\e[m");
        printf("\t\t\t請輸入介於2-4的有效值。");
        break;
    }
    printf("\n\n\n\n\n\n\n\n\n");
    printf("請按Enter繼續。");
    setbuf(stdin, NULL);
    c = getchar();
}

    void            printIntroduction()
{
    char c = 0;
    printf("%s", clean_screen);
    printf("\n\n\n\n\n\t\t\t\t\t注意事項：");
    printf("\n\n\t\t\t  請將終端機開成全螢幕，否則顯示可能會將有問題。");
    printf("\n\n\n\n\n請按Enter繼續。");
    setbuf(stdin, NULL);
    c = getchar();
    printf("%s", clean_screen);
    printf("\n\n\n\n\n\n\n\n\n");
    printf("　　　　　　　　　　　　　　　╔════════════════════════════════════════════════╗\n");
    printf("　　　　　　　　　　　　　　　║　　　　　　　　　　　　　　　　　　　　　　　　║\n");
    printf("　　　　　　　　　　　　　　　║　　　　　　　　　　　　　　　　　　　　　　　　║\n");
    printf("　　　　　　　　　　　　　　　║　　　　　　　　　　　　　　　　　　　　　　　　║\n");
    printf("　　　　　　　　　　　　　　　║　　　　　　　Ｓａｎ　　Ｊｕａｎ　　　　　　　　║\n");
    printf("　　　　　　　　　　　　　　　║　　　　　　　　　　　　　　　　　　　　　　　　║\n");
    printf("　　　　　　　　　　　　　　　║　　　　　　　　　　　　　　　　　　　　　　　　║\n");
    printf("　　　　　　　　　　　　　　　║　　　　　　Ｆｉｎａｌ　Ｐｒｏｊｅｃｔ　　　　　║\n");
    printf("　　　　　　　　　　　　　　　║　　　　　　　　　　　　　　　　　　　　　　　　║\n");
    printf("　　　　　　　　　　　　　　　║　　　　　　　　　　　　　　　　　　　　　　　　║\n");
    printf("　　　　　　　　　　　　　　　║　　     　　             designed by 許証淵　　║\n");
    printf("　　　　　　　　　　　　　　　║　　　　  　　　　　　　　　　　40947071S 　　　║\n");
    printf("　　　　　　　　　　　　　　　╚════════════════════════════════════════════════╝\n");
    printf("\n\n\n\n\n\n\n\n\n");
    printf("請按Enter繼續。");
    setbuf(stdin, NULL);
    c = getchar();
}

    int32_t         showSelectionList()
{
    int32_t choice = 0;
    printf("%s", clean_screen);
    printf("\n\n\n\n\n\n\n\n\n");
    printf("　　　　　　　　　　　　　　　╔════════════════════════════════════════════════╗\n");
    printf("　　　　　　　　　　　　　　　║　　　　　　　　　　　　　　　　　　　　　　　　║\n");
    printf("　　　　　　　　　　　　　　　║　　　　　　　　　　　　　　　　　　　　　　　　║\n");
    printf("　　　　　　　　　　　　　　　║　　　　　　　　　　　　　　　　　　　　　　　　║\n");
    printf("　　　　　　　　　　　　　　　║　　　　　　　Ｓａｎ　　Ｊｕａｎ　　　　　　　　║\n");
    printf("　　　　　　　　　　　　　　　║　　　　　　　　　　　　　　　　　　　　　　　　║\n");
    printf("　　　　　　　　　　　　　　　║　　　　　　Ｆｉｎａｌ　Ｐｒｏｊｅｃｔ　　　　　║\n");
    printf("　　　　　　　　　　　　　　　║　　　　　　　　　　　　　　　　　　　　　　　　║\n");
    printf("　　　　　　　　　　　　　　　║　　　　　　　　　　　　　　　　　　　　　　　　║\n");
    printf("　　　　　　　　　　　　　　　║　　　　　　　（１）　開始遊戲　　　　　　　　　║\n");
    printf("　　　　　　　　　　　　　　　║　　　　　　　（２）　　離開　　　　　　　　　　║\n");
    printf("　　　　　　　　　　　　　　　║　　　　　　　　　　　　　　　　　　　　　　　　║\n");
    printf("　　　　　　　　　　　　　　　║　　　　　　　　　　　　　　　　　　　　　　　　║\n");
    printf("　　　　　　　　　　　　　　　╚════════════════════════════════════════════════╝\n");
    printf("\n\n\n\n\n\n\n\n\n");
    printf("請選擇:\n");
    while(1)
    {
        if( (scanf("%d" , &choice)) == 0)
        {
            fflush(stdin);
            getchar();
        }
        else break;
    }
    
    return choice;
}

    int32_t         getPlayerNumber()
{
    int32_t numberOfPlayers = 0;
    printf("%s" , clean_screen);
    printf("\n\n\n\n\n");
    printf("　　　　　　　　　　　　　　　╔════════════════════════════════════════════════╗\n");
    printf("　　　　　　　　　　　　　　　║　　　　　　　　　　　　　　　　　　　　　　　　║\n");
    printf("　　　　　　　　　　　　　　　║　　　　　　　　　　　　　　　　　　　　　　　　║\n");
    printf("　　　　　　　　　　　　　　　║　　　　　 　請輸入玩家數量（2 - 4）：　　　　　║\n");
    printf("　　　　　　　　　　　　　　　║　　　　　　　　　　　　　　　　　　　　　　　　║\n");
    printf("　　　　　　　　　　　　　　　║　　　　　　　　　　　　　　　　　　　　　　　　║\n");
    printf("　　　　　　　　　　　　　　　╚════════════════════════════════════════════════╝\n");
    printf("\n\n\n\n\n");
    while(1)
    {
        if( (scanf("%d" , &numberOfPlayers)) == 0)
        {
            fflush(stdin);
            getchar();
        }
        else break;
    }
    return numberOfPlayers;
}

    void            initialize_Player(sPlayer *player, int32_t numberOfPlayer)
{
    for (int32_t i = 1; i <= numberOfPlayer; i++)
    {
        player[i].pointsReceive = 1;  //染坊直接得1分
        player[i].cardOnHand = NULL; 
        player[i].number_cardOnHand = 0;
        player[i].number_cardOnTable = 1;
        player[i].cardOnTable[1].cardNumber = 1;
        player[i].cardOnTable[1].cardName = "　染　坊　";
        player[i].cardOnTable[1].cardDescription = "生產階段 → 你生產一份染料。";
        player[i].cardOnTable[1].cardCost = 1;
        player[i].cardOnTable[1].cardScore = 1;
        player[i].cardOnTable[1].subcard = 0;
        player[i].cardOnTable[1].linkedListNext = NULL;

        for (int32_t j = 2; j <= 12; j++)
        {
            player[i].cardOnTable[j].cardNumber = 0;
            player[i].cardOnTable[j].cardName = NULL;
            player[i].cardOnTable[j].cardDescription = NULL;
            player[i].cardOnTable[j].cardCost = 0;
            player[i].cardOnTable[j].cardCost = 0;
            player[i].cardOnTable[j].subcard = 0;
            player[i].cardOnTable[j].linkedListNext = NULL;
        }
        //

    }
    
}

    void            initialize_Card(int32_t cardAmount, int32_t cardNumber, char* cardName, 
                                char* cardDescription, int32_t cardCost, int32_t cardPoint)
{
    for(int32_t i = deckIndex;i < deckIndex + cardAmount;i++){
        deck[i].cardNumber = cardNumber;
        deck[i].cardName = cardName;
        deck[i].cardDescription = cardDescription;
        deck[i].cardCost = cardCost;
        deck[i].cardScore = cardPoint;
        // deck[i].subcard = 0;
        deck[i].linkedListNext = NULL;
    }
    deckIndex = deckIndex + cardAmount;
}

    void            initialize_Deck()
{
    initialize_Card(10, 1 ,"　染 坊　", "生產階段 → 你生產一份染料。"      ,1 , 1);
    initialize_Card(8 , 2 ,"　製糖廠　", "生產階段 → 你生產一份砂糖。"    ,2 , 1);
    initialize_Card(8 , 3 ,"　菸草場　", "生產階段 → 你生產一份菸草。"    ,3 , 2);
    initialize_Card(8 , 4 ,"咖啡烘焙場", "生產階段 → 你生產一份咖啡。" ,4 , 2);
    initialize_Card(8 , 5 ,"　煉銀場　", "生產階段 → 你生產一份銀錠。"    ,5 , 3);

    initialize_Card(3 , 6 ,"　鐵匠鋪　", "建築階段 → 你建築工廠建築時少付一張牌。"    ,1 , 1);
    initialize_Card(3 , 7 ,"　金 礦　", 
                    "礦工階段 → 你抽4張牌，若它們的建築費用皆不同，保留其中費用最便宜的一張。", 1 , 1);
    initialize_Card(3 , 8 ,"　檔案室　", "議員階段 → 你可以從手牌及 / 或剛抽的牌中棄牌。",1 , 1);
    initialize_Card(3 , 9 ,"　濟貧院　", "建築階段 → 你在建造完後如果只剩0或1張手牌，則抽1張牌。",2 , 1);
    initialize_Card(3 , 11 ,"　黑 市　", "建築階段 → 你可以棄掉任何一份貨物降低建築費用1張牌，或棄掉任何兩份貨物降低建築費用2張手牌。",2 , 1);
    initialize_Card(3 , 12 ,"　貿易站　", "交易階段 → 你可以額外賣1份貨物。",2 , 1);
    initialize_Card(3 , 13 ,"　水 井　", "生產階段 → 你生產至少2份貨物時，抽1張牌。",2 , 1);
    initialize_Card(3 , 10 ,"　攤 販　", "交易階段 → 你賣至少2份貨物時，抽1張牌。",2 , 1);
    initialize_Card(3 , 14 ,"　起重機　", "建築階段 → 你可以改建1棟建築（費用為新建築的費用減舊建築的費用，但費用不得低於0）。",2 , 1);
    initialize_Card(3 , 15 ,"　教 堂　", "回合開始 → 你可以從手牌放1張牌至教堂下（在遊戲結束時每張值1分）。",3 , 2); //done
    initialize_Card(3 , 16 ,"　高 塔　", "回合開始 → 你的手牌上限為12張。",3 , 2); //done
    initialize_Card(3 , 17 ,"　上水道　", "生產階段 → 你多生產1份貨物。",3 , 2);
    initialize_Card(3 , 18 ,"　木工坊　", "建築階段 → 你建造城市建築後抽一張牌。",3 , 2);
    initialize_Card(3 , 19 ,"　總督府　", "議員階段 → 你在抽牌時多保留1張牌。",4 , 2);
    initialize_Card(3 , 20 ,"　市 場　", "交易階段 → 你賣至少1份貨物時，抽1張牌。",4 , 2);
    initialize_Card(3 , 21 ,"　採石場　", "建築階段 → 你在建造城市建築時少付1張牌。",4 , 2);
    initialize_Card(3 , 22 ,"　圖書館　", "所有階段 → 你所選的職業特權加倍。",5 , 3);
    initialize_Card(3 , 23 ,"　雕 像　", "紀念碑 → 無特殊功能（不可重複建造）。",3 , 3);
    initialize_Card(3 , 25 ,"　英雄像　", "紀念碑 → 無特殊功能（不可重複建造）。",4 , 4);
    initialize_Card(3 , 24 ,"勝利紀念柱", "紀念碑 → 無特殊功能（不可重複建造）。",5 , 5);
    initialize_Card(2 , 26 ,"　公 會　", "遊戲結束 → 你的每棟工廠建築額外得1分，且每種工廠建築在額外得1分。",6 , INCONCLUSIVE);
    initialize_Card(2 , 27 ,"　市政廳　", "遊戲結束 → 你的每棟城市建築額外得1分。",6 , INCONCLUSIVE);
    initialize_Card(2 , 28 ,"　凱旋門　", "遊戲結束 → 若你有1/2/3座紀念碑便額外獲得4/6/8分。",6 , INCONCLUSIVE);
    initialize_Card(2 , 29 ,"　皇 宮　", "遊戲結束 → 你每擁有4分就額外獲得1分（無條件捨去）。",6 , INCONCLUSIVE);
    //Extension
    initialize_Card(3 , 30 ,"　警衛室　", "回合開始 → 所有沒有警衛室的玩家手牌減少為6張（若擁有高塔，則依舊為12張）。",1 , 1); //done
    initialize_Card(3 , 31 ,"　辦公樓　", "回合開始 → 你可以棄掉1或2張牌，然後抽等量的新牌。",1 , 1); //done
    initialize_Card(3 , 32 ,"　茅 屋　", "交易階段 → 如果沒有任何玩家賣貨物，則你抽一張牌。",1 , 1);
    initialize_Card(3 , 33 ,"　酒 館　", "建築階段 → 在建築階段結束時，若你的建築物數量最少，則抽1張牌。",2 , 1);
    initialize_Card(3 , 34 ,"　公 園　", "建築階段 → 當你透過起重機將公園改建時，新建築的建造費用降低6張牌（最低0張）。",3 , 2);
    initialize_Card(3 , 36 ,"　海 關　", "議員階段 → 放一份貨物至海關。 交易階段 →賣此貨物得2張牌。",3 , 2);
    initialize_Card(3 , 35 ,"　銀 行　", "回合開始 → 你在一場遊戲中有一次機會將任意張數的手牌放置銀行下（在遊戲結束時每張值1分）。",3 , 2);//done
    initialize_Card(3 , 37 ,"　港 口　", "交易階段 → 你將1份剛賣掉的貨放在港口下（遊戲結束時每張值1分）。",4 , 2);
    initialize_Card(3 , 38 ,"　金工坊　", "礦工階段 → 你抽1張牌，若尚未有任何玩家建造此建築，即可保留它，否則丟入棄牌堆。",5 , 3);
    initialize_Card(2 , 39 ,"　官 邸　", "遊戲結束 → 將3棟費用相同的不同建築視為一組，若你擁有1/2/3/4組，則額外獲得4/7/9/10分。",6 , INCONCLUSIVE);
    // printf("初始化(deckIndex) %d 張卡片。\n", deckIndex);
    deckIndex = 138;
    discardDeckIndex = 0;
}

    void            shuffle(int32_t amount)
{
    srand(time(0));

    for (int32_t i = 0; i < amount; i++)
    {
        int32_t         numberRandom = rand() % amount;
        sCard           tmp = {0};

        while(i == numberRandom) numberRandom = rand() % amount;

        tmp = deck[i];
        deck[i] = deck[numberRandom];
        deck[numberRandom] = tmp;
    }
    
}

    void            draw(sPlayer* player, int32_t numberOfPlayer, int32_t amountOfCard)
    {
        if(deckIndex + 1 < amountOfCard)
        {

            memcpy(&deck[deckIndex + 1], discardDeck, sizeof(sCard) * discardDeckIndex);
            memset(discardDeck, 0, sizeof(sCard) * 139);

            deckIndex = deckIndex + discardDeckIndex;
            shuffle(deckIndex + 1);

            deckIndex = 0;
            player[0].number_cardOnTable = discardDeckIndex;

        }

        for (int32_t i = 0; i < amountOfCard; i++)
        {
            sCard* preCard = NULL;
            sCard* currentCard = player[numberOfPlayer].cardOnHand;

            while(currentCard != NULL)
            {
                preCard = currentCard;
                currentCard = currentCard -> linkedListNext;
            }
            currentCard = (sCard*) malloc(sizeof(sCard));
            memcpy(currentCard, &deck[deckIndex], sizeof(sCard));
            memset(&deck[deckIndex], 0, sizeof(sCard));

            if(player[numberOfPlayer].number_cardOnHand == 0) 
                player[numberOfPlayer].cardOnHand = currentCard;
            else 
                preCard -> linkedListNext = currentCard;
            
            player[numberOfPlayer].number_cardOnHand++;
            deckIndex--;
            player[0].number_cardOnHand = deckIndex + 1;   //紀錄用
        }
    }

    void            cardDistribute(sPlayer *player, int32_t amountOfPlayers, int32_t governor)
    {
        int32_t         numberOfPlayer = governor;
        int32_t         choiceAction = 0;
        for (int32_t amountOfCard = 5; amountOfCard < 5 + amountOfPlayers; amountOfCard++)
        {
            draw(player, numberOfPlayer, amountOfCard);
            numberOfPlayer++;
            if (numberOfPlayer > amountOfPlayers)  numberOfPlayer = 1;

        }

        for(int32_t numberOfPlayer = 1; numberOfPlayer <= amountOfPlayers; numberOfPlayer++)
        {
            showCardsOnTable(player, amountOfPlayers);
            
            if(numberOfPlayer != HUMAN)
            {
                printf("%d 號玩家棄牌中。\n", numberOfPlayer);
                sleep(2);

                /*手牌只能有4張*/
                int32_t amountOfDiscardCards = player[numberOfPlayer].number_cardOnHand - 4;

                sCard* preCard = NULL;
                sCard* cuerrentCard = player[numberOfPlayer].cardOnHand;

                for(int32_t i = 0;i < amountOfDiscardCards;i++)
                {

                    preCard = cuerrentCard;
                    cuerrentCard = cuerrentCard->linkedListNext;

                    discard(player, numberOfPlayer, preCard);
                }
                continue;
            }

            cardOnHands(player, numberOfPlayer);

            while(1)
            {
                printf("\n1.棄牌 2.查看卡片敘述\n");
                printf("請選擇(輸入01 or 02)：   ");
                scanf("%d", &choiceAction);
                bool        flag_checkDiscard = false;
                int32_t     amountOfDiscardCard = 0;

                switch (choiceAction)
                {
                case 1:  //棄牌
                    amountOfDiscardCard = player[numberOfPlayer].number_cardOnHand - 4;
                    flag_checkDiscard = discardFromHand(player, amountOfPlayers, numberOfPlayer, amountOfDiscardCard);
                    break;
                    
                case 2:
                    displayCardDescription(player, amountOfPlayers, numberOfPlayer);
                    break;

                default:
                    showCardsOnTable(player, amountOfPlayers);
                    cardOnHands(player, numberOfPlayer);
                    printf("\e[1;38;2;255;0;64m輸入值有誤。\n\e[m");
                    // printf("\e[1;38;2;255;0;64m\n1.棄牌 2.查看卡片敘述\n\e[m");
                    // printf("\e[1;38;2;255;0;64m請選擇(輸入01 or 02)：  \e[m");
                    printf("\n");
                    break;
                }
                if (flag_checkDiscard == true) break;
                
            }
        }
    }



//Game start
    bool            discardFromHand(sPlayer *player, int32_t amountOfPlayers, int32_t numberOfPlayer, int32_t amountOfDiscardCard)
    {
        printf("你需要棄掉 %d 張牌，請輸入要丟棄的卡牌之號碼(須間隔空格)。\n ", amountOfDiscardCard);

        int32_t *listOfDiscard = (int32_t*) malloc(sizeof(int32_t) * amountOfDiscardCard);

        for(int32_t i = 0;i < amountOfDiscardCard; i++)
        {
            scanf("%d", &listOfDiscard[i]);

            if(find_handcard(player, numberOfPlayer, listOfDiscard[i]) == NULL)
            {
                showCardsOnTable(player, amountOfPlayers);
                cardOnHands(player, numberOfPlayer);
                printf("\e[1;38;2;255;0;64m沒有此號碼。\n\e[m");
                return false;
            }
        }

        for(int32_t i = 0; i < amountOfDiscardCard; i++)
        {

            sCard* card = NULL;
            int32_t card_id = listOfDiscard[i];

            if((card = find_handcard(player, numberOfPlayer, card_id)) != NULL) discard(player, numberOfPlayer, card);

        }

        free(listOfDiscard);

        return true;
    }

    void            displayCardDescription(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer)
    {   
        printf("%s", clean_screen);
        sCard       *currentCard = player[numberOfPlayer].cardOnHand;
        char        c = 0;
        printf("\n\n\n\n\n\t====================================================================================================\n\n");
        while(currentCard != NULL)
        {
            printf("\t %s  %s \n\n", currentCard->cardName, currentCard->cardDescription);
            currentCard = currentCard->linkedListNext;
        }
        printf("\t====================================================================================================\n");
        printf("\n按 Enter 返回上一頁。.");
        setbuf(stdin, NULL);
        c = getchar();
        printf("%s", clean_screen);
        showCardsOnTable(player, amountOfPlayers);
        cardOnHands(player, numberOfPlayer);
        // printf("\n1.棄牌 2.查看卡片敘述\n");
        // printf("請選擇(輸入01 or 02)：   ");
    }

    void            display_TableCardDescription(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer)
    {
        printf("%s", clean_screen);
        char        c = 0;
        showCardsOnTable(player, amountOfPlayers);


        printf("\n\n\n\n\n\t====================================================================================================\n\n");
        
        for(int32_t i = 1;i <= amountOfPlayers;i++)
        {
            for(int32_t j = 1;j <= player[i].number_cardOnTable;j++)
            {

                printf("%s %s\n", player[i].cardOnTable[j].cardName, player[i].cardOnTable[j].cardDescription);

            }
        }
        printf("\t====================================================================================================\n");
        printf("\n按 Enter 返回上一頁。");
        setbuf(stdin, NULL);
        c = getchar();

        printf("%s", clean_screen);
        showCardsOnTable(player, amountOfPlayers);
        cardOnHands(player, numberOfPlayer);
        printf("請選擇動作（1:抽牌 2:查看手牌敘述 3:查看場上卡牌敘述）:");
    }

    void            showCardsOnTable(sPlayer *player,int32_t numberOfPlayers)
    {
        printf("%s", clean_screen);
        // printf("當前牌堆尚有【%d】張牌，棄牌堆有【%d】張牌。\n\n", player[0].number_cardOnHand, player[0].number_cardOnTable);
        printf("1 號玩家(你):\t\t目前得分:【%d】\n\n", player[1].pointsReceive);
        printf("2 號玩家:\t\t目前得分:【%d】\n\n", player[2].pointsReceive);
        if (numberOfPlayers == 4)
        {
            printf("3 號玩家:\t\t目前得分:【%d】\n\n", player[3].pointsReceive);
            printf("4 號玩家:\t\t目前得分:【%d】\n", player[4].pointsReceive);
        }
        else if(numberOfPlayers == 3) printf("3 號玩家:\t\t目前得分:【%d】\n", player[3].pointsReceive);

        printf("\n");
        
        printf("當前牌堆尚有【%d】張牌，棄牌堆有【%d】張牌。\n\n", player[0].number_cardOnHand, player[0].number_cardOnTable);
    }

    void            round_start(sPlayer* player,int32_t amountOfPlayers,int32_t governor)
    {
        printf("%s", clean_screen);
        showCardsOnTable(player, amountOfPlayers);

        //教堂、銀行、辦公樓 ==> 遊戲效果
        for (int32_t numberOfPlayer = 1; numberOfPlayer <= amountOfPlayers; numberOfPlayer++)
        {
            //教堂、銀行、辦公樓
            int32_t tableCardIndex = 0;

            if(numberOfPlayer != HUMAN)
            {
                showCardsOnTable(player, amountOfPlayers);    
                printf("%d號玩家正在採取行動。\n", numberOfPlayer);
                sleep(1);
            }

            if(tableCardIndex = find(CHAPEL)) chapel(player, amountOfPlayers, numberOfPlayer, tableCardIndex);
            if(tableCardIndex = find(OFFICE_BUILDING)) office(player, amountOfPlayers, numberOfPlayer, tableCardIndex);
            if(tableCardIndex = find(BANK) && !bank_used_table[numberOfPlayer])
            {
                bank_used_table[numberOfPlayer] = true;
                bank(player, amountOfPlayers, numberOfPlayer, tableCardIndex);
            }       
        }
        
        bool        playerHasGuardroom = false;
        int32_t     whoGuardroom = 0;

        // 警衛室、高塔 ==> 手牌張數限制
        for(int32_t numberOfPlayer = 1; numberOfPlayer <= amountOfPlayers; numberOfPlayer++)
        {
            if(find(GUARD_ROOM))
            {
                playerHasGuardroom = true;
                whoGuardroom = numberOfPlayer;
                break;
            }
        }

        for(int32_t numberOfPlayer = 1; numberOfPlayer <= amountOfPlayers; numberOfPlayer++)
        {
            //機器人隨便亂來就行
            if (numberOfPlayer != HUMAN)
            {
                if(find(TOWER)) //塔的上限只有12張
                {
                    if(player[numberOfPlayer].number_cardOnHand > 12)
                    {
                        int32_t num_of_discard = player[numberOfPlayer].number_cardOnHand - 12;
                        for(int32_t i = 0;i < num_of_discard;i++) 
                        {
                            discard(player, numberOfPlayer, player[numberOfPlayer].cardOnHand);
                        }
                        printf(" %d 號玩家建造了【高塔】，因此 %d 號玩家棄掉了%d張牌，剩 %d 張牌\n",
                                numberOfPlayer, numberOfPlayer, num_of_discard, player[numberOfPlayer].number_cardOnHand);
                        sleep(1);

                    }

                    continue;
                }

                if (playerHasGuardroom)
                {
                    if(player[numberOfPlayer].number_cardOnHand > 6 && numberOfPlayer != whoGuardroom)
                    {

                        int32_t num_of_discard = player[numberOfPlayer].number_cardOnHand - 6;
                        for(int32_t i = 0;i < num_of_discard;i++) 
                        {
                            discard(player, numberOfPlayer, player[numberOfPlayer].cardOnHand);
                        }
                        printf("由於 %d 號玩家建造了【警衛室】，因此 %d 號玩家棄掉了 %d 張牌，剩 %d 張牌。\n",
                                whoGuardroom, numberOfPlayer, num_of_discard, player[numberOfPlayer].number_cardOnHand);
                        sleep(1);
                    }
                    else if(player[numberOfPlayer].number_cardOnHand > 7 && numberOfPlayer == whoGuardroom)
                    {
                        int32_t num_of_discard = player[numberOfPlayer].number_cardOnHand - 7;
                        for(int32_t i = 0;i < num_of_discard;i++) 
                        {
                            discard(player, numberOfPlayer, player[numberOfPlayer].cardOnHand);
                        }
                        printf("由於 %d 號玩家建造了【警衛室】，因此 %d 號玩家棄掉了 %d 張牌，剩 %d 張牌。\n",
                                whoGuardroom, numberOfPlayer, num_of_discard, player[numberOfPlayer].number_cardOnHand);
                        sleep(1);
                    }
                }
                else
                {
                    if(player[numberOfPlayer].number_cardOnHand > 7)
                    {

                    int32_t num_of_discard = player[numberOfPlayer].number_cardOnHand - 7;
                    for(int32_t i = 0;i < num_of_discard;i++) 
                    {
                       discard(player, numberOfPlayer, player[numberOfPlayer].cardOnHand);
                    }
                    printf("%d 號玩家棄掉了%d 張牌，剩 %d 張牌\n", numberOfPlayer, num_of_discard, player[numberOfPlayer].number_cardOnHand);
                    sleep(2);

                    }
                }
                continue;                
            }
            

            //有選擇的人類
            if (find(TOWER))
            {
                if (player[numberOfPlayer].number_cardOnHand > 12)
                {
                    int32_t amount_ToDiscard = player[numberOfPlayer].number_cardOnHand - 12;
                    printf("【高塔】使手牌限制不得超過 12 張，因此你需要棄掉 %d 張牌。\n", amount_ToDiscard);

                    while(1)
                    {

                        bool flag = false;

                        amount_ToDiscard = player[numberOfPlayer].number_cardOnHand - 12;
                        flag = discardFromHand(player, amountOfPlayers, numberOfPlayer, amount_ToDiscard);

                        if(flag) break;
                        else
                        {
                            char c = 0;
                            printf("請按Enter繼續。\n");
                            setbuf(stdin, NULL);
                            c = getchar();
                        }

                    }
                }
                continue;
            }

            if (playerHasGuardroom)
            {
                //沒警衛室的人
                if(player[numberOfPlayer].number_cardOnHand > 6 && numberOfPlayer != whoGuardroom)
                {

                    int32_t amount_ToDiscard = player[numberOfPlayer].number_cardOnHand - 6;
                    printf("由於 %d 號玩家建造了【警衛室】，因此你需要棄掉 %d 張牌。\n", whoGuardroom, amount_ToDiscard);

                    while(1)
                    {

                        bool flag = false;

                        amount_ToDiscard = player[numberOfPlayer].number_cardOnHand - 6;
                        flag = discardFromHand(player, numberOfPlayer, numberOfPlayer, amount_ToDiscard);
                        if(flag) break;
                        else
                        {
                            char c = 0;
                            printf("請按Enter繼續。\n");
                            setbuf(stdin, NULL);
                            c = getchar();
                        }

                    }

                }
                else if(player[numberOfPlayer].number_cardOnHand > 7 && numberOfPlayer == whoGuardroom)
                {
                    int32_t num_of_discard = player[numberOfPlayer].number_cardOnHand - 7;
                    printf("由於你建造了【警衛室】，因此你需要棄掉 %d 張牌(手牌不可超過7張)。\n", num_of_discard);

                    while(1)
                    {

                        bool flag = false;

                        num_of_discard = player[numberOfPlayer].number_cardOnHand - 7;
                        flag = discardFromHand(player, numberOfPlayer, numberOfPlayer, num_of_discard);
                        if(flag) break;
                        else
                        {
                            char c = 0;
                            printf("請按Enter繼續。\n");
                            setbuf(stdin, NULL);
                            c = getchar();
                        }

                    }
                }
            }
            //手牌限制不得超過7張
            else
            {

                if(player[numberOfPlayer].number_cardOnHand > 7)
                {
                    int32_t amount_ToDiscard = player[numberOfPlayer].number_cardOnHand - 7;
                    while(1)
                    {

                        bool flag = false;

                        amount_ToDiscard = player[numberOfPlayer].number_cardOnHand - 7;
                        flag = discardFromHand(player, amountOfPlayers, numberOfPlayer, amount_ToDiscard);
                        if(flag) break;
                        else
                        {
                            char c = 0;
                            printf("請按Enter繼續。\n");
                            setbuf(stdin, NULL);
                            c = getchar();
                        }
                    }
                }
            }

        }
    }

    void            discard(sPlayer* player, int32_t numberOfPlayer, sCard* card)
    {
        sCard*       preCard = NULL;
        sCard*       currentCard = player[numberOfPlayer].cardOnHand;

        while (currentCard != NULL)
        {
            if(currentCard == card)
            {
                memcpy(&discardDeck[discardDeckIndex], currentCard, sizeof(sCard));

                if(currentCard == player[numberOfPlayer].cardOnHand) 
                    player[numberOfPlayer].cardOnHand = currentCard->linkedListNext;
                else 
                    preCard->linkedListNext = currentCard->linkedListNext;

                //discardDeck

                player[numberOfPlayer].number_cardOnHand--;
                discardDeckIndex++;
                player[0].number_cardOnTable = discardDeckIndex; //紀錄用的
                
                free(currentCard);
                return;
            }
            preCard = currentCard;
            currentCard = currentCard->linkedListNext;
        }
        
    }

    void            cardOnHands(sPlayer* player, int32_t numberOfPlayer)
    {

        printf("你的手牌：　　");
        if(player[numberOfPlayer].number_cardOnHand == 0)
        {
            printf("　（空）\n\n");
            return;
        }

        sCard* currentCard = player[numberOfPlayer].cardOnHand;
        
        while(currentCard != NULL)
        {
            printf("　　 (%02d) 　", currentCard->cardNumber);
            currentCard = currentCard->linkedListNext;
        }
        printf("\n\n");

        currentCard = player[numberOfPlayer].cardOnHand;
        printf("\t名稱：");
        while(currentCard != NULL)
        {
            printf("　%s", currentCard->cardName);
            currentCard = currentCard->linkedListNext;
        }
        printf("\n");

        currentCard = player[numberOfPlayer].cardOnHand;
        printf("\t費用：");
        while(currentCard != NULL)
        {
            printf("　　　%2d　　", currentCard->cardCost);
            currentCard = currentCard->linkedListNext;
        }
        printf("\n");

        currentCard = player[numberOfPlayer].cardOnHand;
        printf("\t得分：");
        while(currentCard != NULL)
        {
            if(currentCard->cardScore != -1) printf("　　　%2d　　", currentCard->cardScore);
            else printf("　　　%s　　", " ?");
            currentCard = currentCard->linkedListNext;
        }
        printf("\n\n");

    }

    void            cardOnHands_part(sPlayer* player, int32_t numberOfPlayer, sCard* startCard)
    {
        sCard* currentCard = startCard;

        printf("部分手牌：　　");
        
        while(currentCard != NULL)
        {
            printf("　　 (%02d) 　", currentCard -> cardNumber);
            currentCard = currentCard -> linkedListNext;
        }
        printf("\n\n");

        currentCard = startCard;
        printf("\t名稱：");
        while(currentCard != NULL)
        {
            printf("　%s", currentCard -> cardName);
            currentCard = currentCard -> linkedListNext;
        }
        printf("\n");

        currentCard = startCard;
        printf("\t費用：");
        while(currentCard != NULL)
        {
            printf("　　　%2d　　", currentCard -> cardCost);
            currentCard = currentCard -> linkedListNext;
        }
        printf("\n");

        currentCard = startCard;
        printf("\t得分：");
        while(currentCard != NULL)
        {
            if(currentCard -> cardScore != -1) printf("　　　%2d　　", currentCard -> cardScore);
            else printf("　　　%s　　", " ?");
            currentCard = currentCard -> linkedListNext;
        }
        printf("\n\n");

    }

    int32_t         chooseProfession(sPlayer* player,int32_t amountOfPlayer,int32_t numberOfPlayer)
    {
        int32_t currentProfession = 0;

        showCardsOnTable(player, amountOfPlayer);

        //Saddly 只能隨機選職業Q

        if(numberOfPlayer != HUMAN)
        {
            printf("輪到%d號玩家選擇職業中。\n", numberOfPlayer);
            sleep(2);

            currentProfession = rand() % 5 + 1;
            while(profession_table[currentProfession] == true) currentProfession = rand() % 5 + 1;
            profession_table[currentProfession] = true;

            return currentProfession;
        }
    
        printf("\n1.選擇職業 2.查看職業敘述\n");
        printf("請選擇(輸入01 or 02)：   ");

        while (1)
        {
            bool        flag = false;
            char        c = 0;
            int32_t     choice = 0;
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                
                showCardsOnTable(player, amountOfPlayer);

                printf("請選擇職業。\n目前可選職業：");

                //Todo 沒顯示 卻按了該數字
                if(!profession_table[BUILDER]) printf(" (1) 建築師");
                if(!profession_table[COUNCILLOR]) printf(" (2) 議員");
                if(!profession_table[PRODUCER]) printf(" (3) 製造商");
                if(!profession_table[PROSPECTOR]) printf(" (4) 礦工");
                if(!profession_table[TRADER]) printf(" (5) 貿易商");

                printf("\n");

                scanf("%d", &currentProfession);

                if(currentProfession >= 1 && currentProfession <= 5 && !profession_table[currentProfession])
                {
                    flag = true;
                    profession_table[currentProfession] = true;
                }
                else
                {
                    showCardsOnTable(player, amountOfPlayer);
                    printf("\e[1;38;2;255;0;64m幫個忙拜託：請輸入有效值！\n\n\e[m");
                    printf("別再惡搞了...已經寫的頭昏眼花了..\n\n");
                    printf("請選擇動作（1:選擇職業 2:查看職業敘述）。\n");
                }
            break;
            
            case 2:

                showCardsOnTable(player, amountOfPlayer);
                printf("\n\n\n\n\n\t====================================================================================================\n");
                printf("\n\t【建築師】\t行動：每個人可以建造一棟建築。 \n\t\t特權：建築師可以少支付一張牌的建造費用。\n");
                printf("\n\t【議員】\t行動：每個人抽兩張牌並選擇其中一張保留。　\n\t\t特權：議員額外抽三張牌。\n");
                printf("\n\t【製造商】\t行動：每人可以生產一份貨物。　\n\t\t特權：製造商可以額外生產一份貨物。\n");
                printf("\n\t【礦工】\t行動：無。　\n\t\t特權：礦工抽一張牌。\n");
                printf("\n\t【貿易商】\t行動：每個人可以販賣一份貨物。　\n\t\t特權：建築師可以少支付一張牌的建造費用。\n");
                printf("\n\t====================================================================================================\n");

                printf("請按Enter繼續。");
                setbuf(stdin, NULL);
                c = getchar();
                showCardsOnTable(player, amountOfPlayer);
                printf("\n1.選擇職業 2.查看職業敘述\n");
                printf("請選擇(輸入01 or 02)：   ");
            break;

            default:
                showCardsOnTable(player, amountOfPlayer);
                printf("\n1.選擇職業 2.查看職業敘述\n");
                printf("請選擇(輸入01 or 02)：   ");
                
                printf("別再惡搞了...已經寫的頭昏眼花了.....\n");
            break;
            }

            if (flag) break;
            
        }
        
        return currentProfession;
    }

    void            putCardUnder(sPlayer* player,int32_t numberOfPlayer,int32_t tableCardIndex,sCard* card)
    {
        //桌上的牌先列出來
        sCard* preCard = NULL;
        sCard* currentCard = player[numberOfPlayer].cardOnTable[tableCardIndex].linkedListNext;

        while(currentCard != NULL)
        {
            preCard = currentCard;
            currentCard = currentCard -> linkedListNext;
        }

        currentCard = (sCard*)malloc(sizeof(sCard));
        memcpy(currentCard, card, sizeof(sCard));
        player[numberOfPlayer].cardOnTable[tableCardIndex].subcard++;

        currentCard = player[numberOfPlayer].cardOnHand;

        while(currentCard != NULL)
        {
            
            if(currentCard == card)
            {

                //Redirect

                if(currentCard == player[numberOfPlayer].cardOnHand)
                    player[numberOfPlayer].cardOnHand = currentCard->linkedListNext;
                else 
                    preCard->linkedListNext = currentCard->linkedListNext;

                //handcard

                player[numberOfPlayer].number_cardOnHand--;
                
                free(currentCard);
                return;

            }

            preCard = currentCard;
            currentCard = currentCard->linkedListNext;

        }
    }
    //Todo: ★★★★★ 檢查 按Enter是否有影響
    void            chapel_MakeDecision(sPlayer* player, int32_t amountOfPlayer, int32_t numberOfPlayer, int32_t tableCardIndex)
    {
        char    c = 0;

        while(1)
        {
            int32_t cardID = 0;
            sCard* card = NULL;
            scanf("%d", &cardID);

            //不放牌 則輸入0
            if(cardID == 0) return;

            if((card = find_handcard(player, numberOfPlayer, cardID)) != NULL)
            {
                putCardUnder(player, numberOfPlayer, tableCardIndex, card);
                player[numberOfPlayer].pointsReceive++;
                break;
            }
            else
            {
                showCardsOnTable(player, amountOfPlayer);
                cardOnHands(player, numberOfPlayer);
                printf("號碼 %d 不在當前手牌中。\n", cardID);
            }

        }

        showCardsOnTable(player, amountOfPlayer);
        cardOnHands(player, numberOfPlayer);
        printf("放牌成功！\n");
        sleep(2);
        showCardsOnTable(player, amountOfPlayer);
        cardOnHands(player, numberOfPlayer);
        return;

    }

    void            discard_product(sPlayer* player, int32_t numberOfPlayer, int32_t tableCardIndex)
    {
        sCard* preCard = NULL;
        sCard* currentCard = player[numberOfPlayer].cardOnTable[tableCardIndex].linkedListNext;

        if(currentCard == NULL) return;
        while(currentCard->linkedListNext != NULL)
        {
            preCard = currentCard;
            currentCard = currentCard->linkedListNext;
        }

        memcpy(&discardDeck[discardDeckIndex], currentCard, sizeof(sCard));

        //Redirect

        if(currentCard == player[numberOfPlayer].cardOnTable[tableCardIndex].linkedListNext) 
            player[numberOfPlayer].cardOnTable[tableCardIndex].linkedListNext = currentCard->linkedListNext;
        else 
            preCard->linkedListNext = currentCard->linkedListNext;

        //discardDeck

        player[numberOfPlayer].cardOnTable[tableCardIndex].cardHasProduct = false;
        player[numberOfPlayer].cardOnTable[tableCardIndex].subcard--;
        discardDeckIndex++;
        player[0].number_cardOnTable = discardDeckIndex;    //紀錄
        
        free(currentCard);

    }

    void            produce_product(sPlayer* player, int32_t numberOfPlayer, int32_t tableCardIndex)
    {
        sCard* pre = NULL;
        sCard* now = player[numberOfPlayer].cardOnTable[tableCardIndex].linkedListNext;

        while(now != NULL)
        {
            pre = now;
            now = now->linkedListNext;
        }

        now = (sCard*)malloc(sizeof(sCard));
        memcpy(now, &deck[deckIndex], sizeof(sCard));
        memset(&deck[deckIndex], 0, sizeof(sCard));

        //Redirect

        if(player[numberOfPlayer].cardOnTable[tableCardIndex].subcard != 0)
        {
            now->linkedListNext = pre->linkedListNext;
            pre->linkedListNext = now;
        }
        else
        {
            now->linkedListNext = NULL;
            player[numberOfPlayer].cardOnTable[tableCardIndex].linkedListNext = now;
        }

        player[numberOfPlayer].cardOnTable[tableCardIndex].cardHasProduct = true;
        player[numberOfPlayer].cardOnTable[tableCardIndex].subcard++;
        deckIndex--;
        player[0].number_cardOnHand = deckIndex + 1;
    }

    bool            game_end(sPlayer* player, int32_t amountOfPlayers)
    {

        for(int32_t numberOfPlayer = 1;numberOfPlayer <= amountOfPlayers;numberOfPlayer++)
        {
            if(player[numberOfPlayer].number_cardOnTable == 12) return true;
        }

        return false;

    }


//5種基本角色

    //建築(Build) Functions
    void            pro_Builder(sPlayer* player,int32_t amountOfPlayer,int32_t professionOfPlayer,int32_t numberOfPlayer)
    {
        if(numberOfPlayer != HUMAN)
        {
            showCardsOnTable(player, amountOfPlayer);
            printf("%d 號玩家選擇了建築師，現在是建築階段。\n\n", professionOfPlayer);
            printf("%d 號玩家正在採取行動。\n", numberOfPlayer);
            sleep(1);
        }

        if (numberOfPlayer == HUMAN)
        {
            showCardsOnTable(player, amountOfPlayer);
            printf("%d 號玩家選擇了【建築師】，現在是建築階段。\n\n", professionOfPlayer);
            sleep(2);
            showCardsOnTable(player, amountOfPlayer);
            cardOnHands(player, numberOfPlayer);
            printf("請選擇動作（1:建造 2:查看手牌敘述 3:查看場上卡牌敘述）。\n");
            while(1)
            {

                int32_t     choice = 0;
                scanf("%d", &choice);

                //"請選擇動作（1:建造 2:查看手牌敘述 3:查看場上卡牌敘述）。"
                if(choice == 1) break;
                if(choice == 2) displayCardDescription(player, amountOfPlayer, numberOfPlayer);
                if(choice == 3) display_TableCardDescription(player, amountOfPlayer, numberOfPlayer);
                if(choice < 1 || choice > 3)
                {
                    showCardsOnTable(player, amountOfPlayer);
                    cardOnHands(player, numberOfPlayer);
                    printf("請選擇動作（1:建造 2:查看手牌敘述 3:查看場上卡牌敘述）。\n");
                    printf("請輸入有效值，拜託了。\n");
                }
            }
        }
        
        
        if(numberOfPlayer == HUMAN) build(player, amountOfPlayer, professionOfPlayer, numberOfPlayer);
        if(numberOfPlayer != HUMAN)
        {
            if(bot_decision(85)) build(player ,amountOfPlayer, professionOfPlayer, numberOfPlayer);
            else printf("%d號玩家沒有建造任何建築。\n", numberOfPlayer);
        }

        if(numberOfPlayer != HUMAN) sleep(3);

    }
    void                build(sPlayer* player, int32_t amountOfPlayer,int32_t  professionOfPlayer,int32_t numberOfPlayer)
        {
            sCard       *card = NULL;
            
            //媽的 應該全部都是機器人的
            if (numberOfPlayer != HUMAN)
            {
                card = player[numberOfPlayer].cardOnHand;
                int32_t     fee = 0; //建築費用

                while (card != NULL)
                {
                     fee = card -> cardCost;
                    //特權者
                    if(professionOfPlayer == numberOfPlayer)
                    {    
                        if(find(LIBRARY)) library(player, numberOfPlayer, &fee, BUILDER);
                        else fee--;
                    }
                    if(find(SMITHY)) smithy(player, numberOfPlayer, card, &fee);
                    if(find(QUARRY)) quarry(player, numberOfPlayer, card, &fee);
                    if(find(BLACK_MARKET)) black_market(player, numberOfPlayer, numberOfPlayer, &fee);

                    if(fee <= 0) fee = 1;

                    if(fee > player[numberOfPlayer].number_cardOnHand - 1)
                    {
                        card = card->linkedListNext;
                        continue;
                    }
                    else break;
                }

                if (card == NULL)
                {
                    printf("%d 號玩家沒有建造任何建築。\n", numberOfPlayer);
                    return;
                }
                
                int32_t tableCardIndex = player[numberOfPlayer].number_cardOnTable;
                player[numberOfPlayer].pointsReceive += card->cardScore;    //積分設定
                tableCardIndex = player[numberOfPlayer].number_cardOnTable;
                memcpy(&player[numberOfPlayer].cardOnTable[tableCardIndex+1], card, sizeof(sCard));
                player[numberOfPlayer].number_cardOnTable++;

                //隨便啦卡片
                sCard* pre = NULL;
                sCard* currentCard = player[numberOfPlayer].cardOnHand;

                while(currentCard != NULL)
                {

                    if(currentCard == card) break;

                    pre = currentCard;
                    currentCard = currentCard->linkedListNext;

                }

                if(currentCard == player[numberOfPlayer].cardOnHand) 
                    player[numberOfPlayer].cardOnHand  = currentCard->linkedListNext;
                else 
                    pre -> linkedListNext = currentCard -> linkedListNext;

                free(currentCard);

                //fee 是多少 就丟多少張牌

                for(int32_t i = 0;i < fee;i++)
                {
                    discard(player, numberOfPlayer, player[numberOfPlayer].cardOnHand);
                } 

                

                player[numberOfPlayer].number_cardOnHand--;
                
                printf("%d 號玩家花費 %d 張牌並蓋了 【%s】。\n", 
                        numberOfPlayer, fee, player[numberOfPlayer].cardOnTable[tableCardIndex+1].cardName);
                
                if(find(CARPENTER)) carpenter(player, amountOfPlayer, numberOfPlayer, &player[numberOfPlayer].cardOnTable[tableCardIndex+1]);
                if(find(POOR_HOUSE)) poor_house(player, amountOfPlayer, numberOfPlayer);

                return;
            }
            
            //正常人類
            int32_t         cardID = 0;
            char            c = 0;

            showCardsOnTable(player, amountOfPlayer);
            cardOnHands(player, numberOfPlayer);
            printf("請選擇一張牌來建造，若不建造則輸入0。\n");

            while (1)
            {
                scanf("%d", &cardID);
                if(cardID == 0) return;

                if( (card = find_handcard(player, numberOfPlayer, cardID)) != NULL)
                {
                    int32_t     fee = card -> cardCost;
                    int32_t     tablecardIndex = 0;

                    if(find(CRANE)) tablecardIndex = crane(player, amountOfPlayer, numberOfPlayer, card);
                    if(find(BLACK_MARKET)) black_market(player, amountOfPlayer, numberOfPlayer, &fee);
                    showCardsOnTable(player, amountOfPlayer);
                    //特權者
                    if(professionOfPlayer == numberOfPlayer)
                    {    
                        if(find(LIBRARY)) library(player, numberOfPlayer, &fee, BUILDER);
                        else
                        {
                            printf("由於你是【建築師】，因此你在建造任何建築時少付一張牌。\n");
                            fee--;
                        }
                    }
                    if(find(SMITHY)) smithy(player, numberOfPlayer, card, &fee);
                    if(find(QUARRY)) quarry(player, numberOfPlayer, card, &fee);
                    //起重機找公園
                    if(tablecardIndex != 0)
                    {  
                        //你可以改建1棟建築（費用為新建築的費用減舊建築的費用，但費用不得低於0）。
                        if(player[numberOfPlayer].cardOnTable[tablecardIndex].cardNumber == PARK) fee -= 6;
                        else fee -= player[numberOfPlayer].cardOnTable[tablecardIndex].cardCost;
                    }

                    if(player[numberOfPlayer].cardOnTable[tablecardIndex].cardNumber == PARK && tablecardIndex != 0)
                    {  //use crane to rebuild park
                        if(fee < 0) fee = 0;
                    }
                    else
                    {
                        if(fee <= 0) fee = 1;
                    }
                    //錢不夠
                    if(fee > player[numberOfPlayer].number_cardOnHand - 1)
                    {
                        showCardsOnTable(player, amountOfPlayer);
                        cardOnHands(player, numberOfPlayer);
                        printf("請選擇一張牌來建造，若不建造則輸入0。\n");
                        printf("Error囉：你沒有足夠的錢！\n");
                        continue;
                    }

                    if(!find(SMITHY) && !find(QUARRY) && !find(BLACK_MARKET) && numberOfPlayer != professionOfPlayer)
                        printf("你沒有其他可減少建築費用的卡牌。\n");
                    printf("\n請按Enter繼續。\n");
                    setbuf(stdin , NULL);
                    c = getchar();

                    //backup

                    sCard tmpcard = *(card);

                    //find the card's prev

                    sCard* preCard = NULL;
                    sCard* currentCard = player[numberOfPlayer].cardOnHand;

                    while(currentCard != NULL)
                    {

                        if(currentCard == card) break;

                        preCard = currentCard;
                        currentCard = currentCard->linkedListNext;

                    }

                    //Redirect

                    if(currentCard == player[numberOfPlayer].cardOnHand) 
                        player[numberOfPlayer].cardOnHand = currentCard->linkedListNext;
                    else 
                        preCard->linkedListNext = currentCard->linkedListNext;
                    free(currentCard);

                    while(1)
                    {
                        bool flag = false;

                        flag = discardFromHand(player, amountOfPlayer, numberOfPlayer, fee);
                        if(flag) break;
                        else
                        {
                            char c = 0;
                            printf("請按Enter繼續。\n");
                            setbuf(stdin, NULL);
                            c = getchar();
                        }

                    }

                    //Build

                    card = &tmpcard;

                    if(tablecardIndex == 0) 
                        player[numberOfPlayer].pointsReceive  += card->cardScore;    //得分
                    else
                    {
                        player[numberOfPlayer].pointsReceive -= player[numberOfPlayer].cardOnTable[tablecardIndex].cardScore;
                        player[numberOfPlayer].pointsReceive += card->cardScore;
                    }

                    if(tablecardIndex == 0)
                    {      //copy the card to the table
                        tablecardIndex = player[numberOfPlayer].number_cardOnTable;
                        memcpy(&player[numberOfPlayer].cardOnTable[tablecardIndex+1], card, sizeof(sCard));
                        player[numberOfPlayer].number_cardOnTable++;
                    }
                    else
                    {
                        player[numberOfPlayer].cardOnTable[tablecardIndex].cardNumber = card-> cardNumber;
                        player[numberOfPlayer].cardOnTable[tablecardIndex].cardName = card-> cardName;
                        player[numberOfPlayer].cardOnTable[tablecardIndex].cardDescription = card-> cardDescription;
                        player[numberOfPlayer].cardOnTable[tablecardIndex].cardCost = card-> cardCost;
                        player[numberOfPlayer].cardOnTable[tablecardIndex].cardScore = card-> cardScore;
                        player[numberOfPlayer].cardOnTable[tablecardIndex].subcard = card-> subcard;

                        if(player[numberOfPlayer].cardOnTable[tablecardIndex].cardHasProduct) 
                            discard_product(player, numberOfPlayer, tablecardIndex);

                        player[numberOfPlayer].cardOnTable[tablecardIndex].cardHasProduct = false;

                    }
                

                    //others

                    player[numberOfPlayer].number_cardOnHand--;
                    
                    showCardsOnTable(player, amountOfPlayer);
                    cardOnHands(player, numberOfPlayer);
                    printf("建造成功！請按Enter繼續。\n");
                    setbuf(stdin, NULL);
                    c = getchar();

                    //after build

                    if(find(CARPENTER)) carpenter(player, amountOfPlayer,numberOfPlayer, card);
                    if(find(POOR_HOUSE)) poor_house(player, amountOfPlayer, numberOfPlayer);

                    break;

//============================================
                }
                else
                {
                    showCardsOnTable(player, amountOfPlayer);
                    cardOnHands(player, numberOfPlayer);
                    printf("請選擇一張牌來建造，若不建造則輸入0...\n");
                    printf("\e[1;38;2;255;0;64m \n\n\tError囉：請輸入有效值！\n\n\e[m");
                }
            }
            

        }
    
    //議員(Councillor) Functions
    void            pro_Councillor(sPlayer* player,int32_t amountOfPlayer,int32_t professionOfPlayer,int32_t numberOfPlayer)
    {
        //機器人
        if(numberOfPlayer != HUMAN)
        {
            showCardsOnTable(player, amountOfPlayer);
            printf("%d 號玩家選擇了議員，現在是【議員】階段。\n\n", professionOfPlayer);
            printf("%d 號玩家正在採取行動。\n\n", numberOfPlayer);
            sleep(2);
        }

        //玩家

        if(numberOfPlayer == HUMAN)
        {
            showCardsOnTable(player, amountOfPlayer);
            printf("%d 號玩家選擇了【議員】，現在是議員階段。\n\n", professionOfPlayer);
            sleep(2);
            showCardsOnTable(player, amountOfPlayer);
            cardOnHands(player, numberOfPlayer);
            printf("請選擇動作（1:抽牌 2:查看手牌敘述 3:查看場上卡牌敘述）...\n");

            while(1)
            {
                int32_t choice = 0;
                scanf("%d", &choice);

                if(choice == 1) break;
                if(choice == 2) displayCardDescription(player, amountOfPlayer, numberOfPlayer);
                if(choice == 3) display_TableCardDescription(player, amountOfPlayer, numberOfPlayer);
                if(choice < 1 || choice > 3)
                {
                    showCardsOnTable(player, amountOfPlayer);
                    cardOnHands(player, numberOfPlayer);
                    printf("請選擇動作（1:抽牌 2:查看手牌敘述 3:查看場上卡牌敘述）...\n");
                    printf("\e[1;38;2;255;0;64m輸入值有誤。\n\e[m");
                }
            }

        }

        councillor(player, amountOfPlayer, professionOfPlayer, numberOfPlayer);
        if(numberOfPlayer != HUMAN) sleep(3);
    }
    void                councillor(sPlayer* player, int32_t amountOfPlayer, int32_t professionOfPlayer, int32_t numberOfPlayer)
        {
             //機器人
            if(numberOfPlayer != HUMAN)
            {
                int32_t amountOfCard = 0;

                if(numberOfPlayer == professionOfPlayer)
                {
                    if(find(LIBRARY))
                    {
                        library(player, numberOfPlayer, NULL, COUNCILLOR);
                        amountOfCard = 8;
                    }
                    else
                    {
                        printf("%d 號玩家是【議員】，可以額外再抽三張牌，總計五張牌。\n", numberOfPlayer);
                        amountOfCard = 5;
                    }
                }
                else amountOfCard = 2;

                int32_t original_NumberOfHandcard = player[numberOfPlayer].number_cardOnHand; 
                int32_t amountOfDiscard = amountOfCard - 1;

                if(find(ARCHIVE)) archive(numberOfPlayer, &original_NumberOfHandcard);
                if(find(PREFECTURE)) prefecture(numberOfPlayer, amountOfCard, &amountOfDiscard);

                //Draw

                draw(player, numberOfPlayer, amountOfCard);

                //find the start of cards that can be discarded

                sCard* currentCard = player[numberOfPlayer].cardOnHand;
                sCard* start = NULL;
                int32_t nowNum = 1;

                while(currentCard != NULL)
                {     //set start of display
                    if(nowNum == original_NumberOfHandcard + 1) break;
                    currentCard = currentCard->linkedListNext;
                    nowNum++;
                }
                start = currentCard;

                //discard

                for(int32_t i = 0;i < amountOfDiscard;i++)
                {
                    sCard* card = start;
                    start = start->linkedListNext;
                    discard(player, numberOfPlayer, card);
                }

                printf("%d 號玩家抽了 %d 張牌，並保留 %d 張牌\n", numberOfPlayer, amountOfCard, amountOfCard - amountOfDiscard);

                int32_t tablecardIdx = 0;

                if(tablecardIdx = find(CUSTOMS_OFFICE)) 
                    customs_office(player, amountOfPlayer, numberOfPlayer, tablecardIdx);

                return;
            }

            //玩家

            int32_t amountOfCard = 0;

            showCardsOnTable(player, amountOfPlayer);

            if(numberOfPlayer == professionOfPlayer)
            {
                if(find(LIBRARY))
                {
                    library(player, numberOfPlayer, NULL, COUNCILLOR);
                    amountOfCard = 8;
                }
                else
                {
                    printf("由於你是【議員】，因此你可以額外再抽三張牌，總計五張\n");
                    amountOfCard = 5;
                }
            }
            else
            {
                printf("你沒有任何增加抽牌數量之特權。\n");
                amountOfCard = 2;
            }

            int32_t original_NumberOfHandcard = player[numberOfPlayer].number_cardOnHand; //Backup
            int32_t amountOfDiscard = amountOfCard - 1;

            if(find(ARCHIVE)) archive(numberOfPlayer, &original_NumberOfHandcard);
            if(find(PREFECTURE)) prefecture(numberOfPlayer, amountOfCard, &amountOfDiscard);
            
            char c = 0;

            printf("\n請按Enter繼續。\n");
            setbuf(stdin,NULL);
            c = getchar();

            //Draw

            showCardsOnTable(player, amountOfPlayer);
            printf("抽牌中。\n");
            sleep(2);
            draw(player, numberOfPlayer, amountOfCard);

            //find the start of cards that can be discarded

            sCard* currentCard = player[numberOfPlayer].cardOnHand;
            sCard* start = NULL;
            int32_t nowNum = 1;

            while(currentCard != NULL)
            {     //set start of display
                if(nowNum == original_NumberOfHandcard + 1) break;
                currentCard = currentCard->linkedListNext;
                nowNum++;
            }
            start = currentCard;

            //print cards that can be discarded

            showCardsOnTable(player, amountOfPlayer);
            cardOnHands_part(player, numberOfPlayer, start);

            if(amountOfDiscard == 0)
            {
                printf("你不需要棄牌。\n");
                sleep(2);
            }
            else printf("你需要棄掉 %d 張牌，請以空格為分隔符，輸入要棄掉的卡片編號（重複的牌亦須重複輸入）。\n", amountOfDiscard);

            while(1)
            {

                bool continueFlag = false;
            
                //check

                int32_t* discard_list = NULL;
                discard_list = (int32_t*)malloc(sizeof(int32_t) * amountOfDiscard);
                for(int32_t i = 0;i < amountOfDiscard;i++) scanf("%d", &discard_list[i]);

                for(int32_t i = 0;i < amountOfDiscard;i++)
                {
                    if(find_handcard(player, numberOfPlayer, discard_list[i]) == NULL)
                    {
                        continueFlag = true;
                        showCardsOnTable(player, amountOfPlayer);
                        cardOnHands_part(player, numberOfPlayer, start);
                        printf("你需要棄掉 %d 張牌，請以空格為分隔符，輸入要棄掉的卡片編號（重複的牌亦須重複輸入）。\n", amountOfDiscard);
                        printf("\e[1;38;2;255;0;64m \n\n\tError囉：請輸入有效值！\n\n\e[m");
                        break;
                    }
                }

                if(continueFlag) continue;

                //discard

                for(int32_t i = 0;i < amountOfDiscard;i++)
                {

                    sCard* card = NULL;
                    int32_t card_id = discard_list[i];

                    if((card = find_handcard(player, numberOfPlayer, card_id)) != NULL) discard(player, numberOfPlayer, card);

                }

                free(discard_list);
                break;

            }

            showCardsOnTable(player, amountOfPlayer);
            cardOnHands(player, numberOfPlayer);

            if(amountOfDiscard != 0) printf("棄牌成功！");
            printf("請按Enter繼續。\n");
            setbuf(stdin, NULL);
            c = getchar();

            int32_t tablecardIdx = 0;

            if(tablecardIdx = find(CUSTOMS_OFFICE)) customs_office(player, amountOfPlayer, numberOfPlayer, tablecardIdx);
        }
    
    //製造商(Producer) Functions
    void            pro_Producer(sPlayer* player,int32_t amountOfPlayer,int32_t professionOfPlayer,int32_t numberOfPlayer)
    {
        //機器人
        if(numberOfPlayer != HUMAN)
        {

            int32_t most_num_of_product = 0;

            if(numberOfPlayer == professionOfPlayer)
            {
                if(find(LIBRARY))
                {
                    library(player, numberOfPlayer, NULL, PRODUCER);
                    most_num_of_product = 3;
                }
                else
                {
                    printf("%d 號玩家是【製造商】。\t特權：因此可以多生產一份貨\n", numberOfPlayer);
                    most_num_of_product = 2;
                }
            }
            else most_num_of_product = 1;
            if(find(AQUEDUCT)) aquaduct(numberOfPlayer, &most_num_of_product);
            //賣最多
            int32_t num_of_producible = 0;

            for(int32_t tablecardIdx = 1;tablecardIdx <= player[numberOfPlayer].number_cardOnTable;tablecardIdx++)
            {
                if(!player[numberOfPlayer].cardOnTable[tablecardIdx].cardHasProduct && player[numberOfPlayer].cardOnTable[tablecardIdx].cardNumber <= 5)
                {
                    num_of_producible++;
                }
            }

            if(num_of_producible < most_num_of_product) most_num_of_product = num_of_producible;

            //隨便賣

            int32_t num_of_product = 0;

            if(bot_decision(10)) num_of_product = 0;
            else if(most_num_of_product == 0) num_of_product = 0;
            else
            {
                if(bot_decision(60)) num_of_product = most_num_of_product;
                else num_of_product = rand() % most_num_of_product + 1;
            }

            //produce

            for(int32_t i = 0;i < num_of_product;i++)
            {
                int32_t tablecardIdx = rand() % player[numberOfPlayer].number_cardOnTable + 1;
                while(player[numberOfPlayer].cardOnTable[tablecardIdx].cardNumber > 5 || player[numberOfPlayer].cardOnTable[tablecardIdx].cardHasProduct)
                {
                    tablecardIdx = rand() % player[numberOfPlayer].number_cardOnTable + 1;
                }
                produce_product(player, numberOfPlayer, tablecardIdx);
            }

            if(num_of_product == 0) printf("%d 號玩家沒有生產貨物。\n", numberOfPlayer);
            else printf("%d 號玩家生產了 %d 份貨物。\n", numberOfPlayer, num_of_product);

            //檢查well有沒有在

            if(find(WELL)) well(player, amountOfPlayer, numberOfPlayer, num_of_product);

            return;
        }

        //玩家

        int32_t most_num_of_product = 0;

        showCardsOnTable(player, amountOfPlayer);

        if(numberOfPlayer == professionOfPlayer)
        {
            if(find(LIBRARY))
            {
                library(player, numberOfPlayer, NULL, PRODUCER);
                most_num_of_product = 3;
            }
            else
            {
                printf("由於你是【製造商】，你的特權：因此你可以多生產一份貨。\n");
                most_num_of_product = 2;
            }
        }
        else most_num_of_product = 1;
        if(find(AQUEDUCT)) aquaduct(numberOfPlayer, &most_num_of_product);

        char c = 0;

        if(!find(AQUEDUCT) && numberOfPlayer != professionOfPlayer) printf("你沒有其他可增加產量的卡牌。\n");
        printf("\n請按Enter繼續。\n");
        setbuf(stdin, NULL);
        c = getchar();

        //adjust most_num_of_product

        int32_t num_of_producible = 0;

        for(int32_t tablecardIdx = 1;tablecardIdx <= player[numberOfPlayer].number_cardOnTable;tablecardIdx++)
        {
            if(!player[numberOfPlayer].cardOnTable[tablecardIdx].cardHasProduct && player[numberOfPlayer].cardOnTable[tablecardIdx].cardNumber <= 5)
            {
                num_of_producible++;
            }
        }

        if(num_of_producible < most_num_of_product) most_num_of_product = num_of_producible;

        showCardsOnTable(player, amountOfPlayer);
        cardOnHands(player, numberOfPlayer);
        printf("你最多可以生產% d 份貨。請輸入生產數量，若不生產則輸入0:\n", most_num_of_product);
        
        while(1){

            bool continueFlag = false;
            int32_t num_of_product = 0;

            scanf("%d", &num_of_product);

            if(num_of_product == 0) return;

            if(num_of_product > 0 && num_of_product <= most_num_of_product)
            {

                showCardsOnTable(player, amountOfPlayer);
                cardOnHands(player, numberOfPlayer);
                printf("請輸入要生產的卡片編號，你要生產 %d 份貨。\n", num_of_product);

                //check

                int32_t* product_list = NULL;
                product_list = (int32_t*)malloc(sizeof(int32_t) * num_of_product);
                for(int32_t i = 0;i < num_of_product;i++) scanf("%d", &product_list[i]);

                for(int32_t i = 0;i < num_of_product;i++)
                {

                    int32_t tablecardIdx = product_list[i];

                    if(player[numberOfPlayer].cardOnTable[tablecardIdx].cardHasProduct || player[numberOfPlayer].cardOnTable[tablecardIdx].cardNumber > 5 || tablecardIdx < 1 || tablecardIdx > player[numberOfPlayer].number_cardOnTable)
                    {
                        continueFlag = true;
                        showCardsOnTable(player, amountOfPlayer);
                        cardOnHands(player , numberOfPlayer);
                        printf("你最多可以生產% d 份貨。請輸入生產數量，若不生產則輸入0:\n", most_num_of_product);
                        printf("\e[1;38;2;255;0;64m輸入值有誤。\n\e[m");
                        break;
                    }
                }

                if(continueFlag) continue;

                //produce

                for(int32_t i = 0;i < num_of_product;i++)
                {
                    int32_t tablecardIdx = product_list[i];
                    produce_product(player, numberOfPlayer, tablecardIdx);
                }

                free(product_list);

                showCardsOnTable(player, amountOfPlayer);
                cardOnHands(player, numberOfPlayer);
                printf("生產完成。請按Enter繼續。\n");
                setbuf(stdin, NULL);
                c = getchar();

                //檢查

                if(find(WELL)) well(player, amountOfPlayer, numberOfPlayer, num_of_product);

                break;

            }
            else
            {

                showCardsOnTable(player, amountOfPlayer);
                cardOnHands(player , numberOfPlayer);
                printf("你最多可以生產% d 份貨。請輸入生產數量，若不生產則輸入0:\n", most_num_of_product);
                printf("\e[1;38;2;255;0;64m輸入值有誤。\n\e[m");         

            }

        }

    }
    
    
    //礦工(Prospector) Functions
    void            pro_Prospector(sPlayer* player,int32_t amountOfPlayer,int32_t professionOfPlayer,int32_t numberOfPlayer)
    {
        int32_t amountOfCard = 0;
        char c = 0;
        
        //Bot

        if(numberOfPlayer != HUMAN)
        {

            if(numberOfPlayer == professionOfPlayer)
            {
                if(find(LIBRARY))
                {
                    library(player, numberOfPlayer, NULL, PROSPECTOR);
                    amountOfCard = 2;
                }
                else
                {
                    printf("%d 號玩家是【礦工】，特權為：可以抽一張牌。\n", numberOfPlayer);
                    amountOfCard = 1;
                }
            }
            else
            {
                printf("%d 號為非【礦工】玩家，沒有抽牌的特權。\n", numberOfPlayer);
                amountOfCard = 0;
            }

            if(amountOfCard != 0) draw(player, numberOfPlayer, amountOfCard);

            if(find(GOLDMINE)) goldmine(player, amountOfPlayer, numberOfPlayer);
            if(find(GOLDSMITH)) goldsmith(player, amountOfPlayer, numberOfPlayer);

            return;
        }

        //Human

        showCardsOnTable(player, amountOfPlayer);
        cardOnHands(player, numberOfPlayer);
        printf("請選擇動作（1:抽牌 2:查看手牌敘述 3:查看場上卡牌敘述）。\n");

        while(1){

            int32_t choice = 0;
            scanf("%d", &choice);

            if(choice == 1) break;
            if(choice == 2) displayCardDescription(player, amountOfPlayer, numberOfPlayer);
            if(choice == 3) display_TableCardDescription(player, amountOfPlayer, numberOfPlayer);
            if(choice < 1 || choice > 3)
            {
                showCardsOnTable(player, amountOfPlayer);
                cardOnHands(player, numberOfPlayer);
                printf("請選擇動作（1:抽牌 2:查看手牌敘述 3:查看場上卡牌敘述）。\n");
                printf("\e[1;38;2;255;0;64m輸入值有誤。\n\e[m");
            }
        }

        showCardsOnTable(player, amountOfPlayer);

        if(numberOfPlayer == professionOfPlayer)
        {
            if(find(LIBRARY))
            {
                library(player, numberOfPlayer, NULL, PROSPECTOR);
                amountOfCard = 2;
            }
            else
            {
                printf("你是【礦工】，因此你可以抽一張牌。\n");
                amountOfCard = 1;
            }
        }
        else
        {
            printf("非【礦工】玩家，沒有抽牌的特權。\n");
            amountOfCard = 0;
        }
        printf("\n請按Enter繼續。\n");
        setbuf(stdin, NULL);
        c = getchar();

        if(amountOfCard != 0)
        {

            showCardsOnTable(player, amountOfPlayer);
            printf("抽牌中。\n");
            sleep(2);
            draw(player, numberOfPlayer, amountOfCard);

            showCardsOnTable(player, amountOfPlayer);
            cardOnHands(player, numberOfPlayer);
            printf("請按Enter繼續。\n");
            c = getchar();

        }

        if(find(GOLDMINE)) goldmine(player, amountOfPlayer, numberOfPlayer);
        if(find(GOLDSMITH)) goldsmith(player, amountOfPlayer, numberOfPlayer);

    }


    //貿易商(Trader) Functions
    void            pro_Trader(sPlayer* player,int32_t amountOfPlayer,int32_t professionOfPlayer,int32_t numberOfPlayer)
    {
         //機器人

        if(numberOfPlayer != HUMAN)
        {

        int32_t most_num_of_product = 0;

            if(numberOfPlayer == professionOfPlayer)
            {
                if(find(LIBRARY))
                {
                    library(player, numberOfPlayer, NULL, PRODUCER);
                    most_num_of_product = 3;
                }
                else
                {
                    printf(" %d 號玩家是【貿易商】； 特權：因此可以多賣一份貨。\n", numberOfPlayer);
                    most_num_of_product = 2;
                }
            }
            else most_num_of_product = 1;
            if(find(TRADING_POST)) trading_post(numberOfPlayer, &most_num_of_product);

            //設定能賣數量

            int32_t able_to_sell = 0;

            for(int32_t tablecardIdx = 1;tablecardIdx <= player[numberOfPlayer].number_cardOnTable; tablecardIdx++)
            {
                if(player[numberOfPlayer].cardOnTable[tablecardIdx].cardHasProduct 
                && (player[numberOfPlayer].cardOnTable[tablecardIdx].cardNumber <= 5 || player[numberOfPlayer].cardOnTable[tablecardIdx].cardNumber == CUSTOMS_OFFICE))
                {
                    able_to_sell++;
                }
            }

            if(able_to_sell < most_num_of_product) most_num_of_product = able_to_sell;

            //機器人亂選就可以了...

            int32_t num_of_product = 0;

            if(bot_decision(10)) num_of_product = 0;
            else if(most_num_of_product == 0) num_of_product = 0;
            else
            {
                if(bot_decision(75)) num_of_product = most_num_of_product;
                else num_of_product = rand() % most_num_of_product + 1;
            }

            //賺

            int32_t earn = 0;

            for(int32_t i = 0;i < num_of_product;i++)
            {

                int32_t tablecardIdx = rand() % player[numberOfPlayer].number_cardOnTable + 1;
                int32_t amountOfCard = 0;
                
                while(!player[numberOfPlayer].cardOnTable[tablecardIdx].cardHasProduct
                    || (player[numberOfPlayer].cardOnTable[tablecardIdx].cardNumber > 5 && player[numberOfPlayer].cardOnTable[tablecardIdx].cardNumber != CUSTOMS_OFFICE))
                {
                tablecardIdx = rand() % player[numberOfPlayer].number_cardOnTable + 1;
                }

                if(player[numberOfPlayer].cardOnTable[tablecardIdx].cardNumber == CUSTOMS_OFFICE) amountOfCard = 2;
                else amountOfCard = price[player[numberOfPlayer].cardOnTable[tablecardIdx].cardNumber];

                discard_product(player, numberOfPlayer, tablecardIdx);
                draw(player, numberOfPlayer, amountOfCard);

                earn += amountOfCard;
            }

            if(num_of_product == 0) printf("%d 號玩家沒有賣出任何貨物。\n", numberOfPlayer);
            else printf("%d 號玩家賣掉了 %d 份貨物，並獲得 %d 張牌。\n", numberOfPlayer, num_of_product, earn);
            //Last
            int32_t tablecardIdx = 0;

            if(find(MARKET_STAND)) market_stand(player, amountOfPlayer, numberOfPlayer, num_of_product);
            if(find(MARKET_HALL)) market_hall(player, amountOfPlayer, numberOfPlayer, num_of_product);
            if(num_of_product != 0)
            {
                if(tablecardIdx = find(HARBOR)) harbor(player, amountOfPlayer, numberOfPlayer, tablecardIdx);
            }

            return;
        }

        //Human

        int32_t most_num_of_product = 0;

        showCardsOnTable(player, amountOfPlayer);

        if(numberOfPlayer == professionOfPlayer)
        {
            if(find(LIBRARY))
            {
                library(player, numberOfPlayer, NULL, TRADER);
                most_num_of_product = 3;
            }
            else
            {
                printf("你是【貿易商】，你的特權：因此你可以多賣一份貨。\n");
                most_num_of_product = 2;
            }
        }
        else most_num_of_product = 1;
        if(find(TRADING_POST)) trading_post(numberOfPlayer, &most_num_of_product);

        char c = 0;

        if(!find(TRADING_POST) && numberOfPlayer != professionOfPlayer) printf("你沒有其他可增加銷量的卡牌。\n");
        printf("\n請按Enter繼續。\n");
        setbuf(stdin, NULL);
        c = getchar();

        //adjust most_num_of_product

        int32_t able_to_sell = 0;

        for(int32_t tablecardIdx = 1; tablecardIdx <= player[numberOfPlayer].number_cardOnTable; tablecardIdx++)
        {
            if(player[numberOfPlayer].cardOnTable[tablecardIdx].cardHasProduct 
            && (player[numberOfPlayer].cardOnTable[tablecardIdx].cardNumber <= 5 || player[numberOfPlayer].cardOnTable[tablecardIdx].cardNumber == CUSTOMS_OFFICE))
            {
                able_to_sell++;
            }
        }

        if(able_to_sell < most_num_of_product) most_num_of_product = able_to_sell;

        showCardsOnTable(player, amountOfPlayer);
        cardOnHands(player, numberOfPlayer);
        printf("請輸入銷售數量，若不銷售則輸入0（你最多可以賣%d份貨）：\n", most_num_of_product);

        while(1)
        {

            bool continueFlag = false;
            int32_t num_of_product = 0;

            scanf("%d", &num_of_product);

            if(num_of_product == 0) return;

            if(num_of_product > 0 && num_of_product <= most_num_of_product){

                showCardsOnTable(player, amountOfPlayer);
                cardOnHands(player, numberOfPlayer);
                printf("請輸入要銷售的卡片編號，你要賣 %d 份貨（編號由左至右，由上至下）。\n", num_of_product);

                //check

                int32_t* list_Product = NULL;
                list_Product = (int32_t*)malloc(sizeof(int32_t) * num_of_product);
                for(int32_t i = 0;i < num_of_product;i++) scanf("%d", &list_Product[i]);

                for(int32_t i = 0;i < num_of_product;i++)
                {

                    int32_t tablecardIdx = list_Product[i];

                    if(!player[numberOfPlayer].cardOnTable[tablecardIdx].cardHasProduct 
                        || (player[numberOfPlayer].cardOnTable[tablecardIdx].cardNumber > 5 && player[numberOfPlayer].cardOnTable[tablecardIdx].cardNumber != CUSTOMS_OFFICE) 
                        || tablecardIdx < 1 || tablecardIdx > player[numberOfPlayer].number_cardOnTable)
                    {
                        continueFlag = true;
                        showCardsOnTable(player, amountOfPlayer);
                        cardOnHands(player , numberOfPlayer);
                        printf("請輸入銷售數量，若不銷售則輸入0（你最多可以賣%d份貨）。\n", most_num_of_product);
                        printf("\e[1;38;2;255;0;64m輸入值有誤。\n\e[m");
                        break;
                    }
                }

                if(continueFlag) continue;

                //計賺
                int32_t earn = 0;

                for(int32_t i = 0;i < num_of_product;i++)
                {

                    int32_t tablecardIdx = list_Product[i];
                    int32_t amountOfCard = 0;

                    if(player[numberOfPlayer].cardOnTable[tablecardIdx].cardNumber == CUSTOMS_OFFICE) amountOfCard = 2;
                    else amountOfCard = price[player[numberOfPlayer].cardOnTable[tablecardIdx].cardNumber];

                    discard_product(player, numberOfPlayer, tablecardIdx);
                    draw(player, numberOfPlayer, amountOfCard);

                    earn += amountOfCard;

                }

                free(list_Product);

                showCardsOnTable(player, amountOfPlayer);
                cardOnHands(player, numberOfPlayer);
                printf("販賣完成。你賣掉了%d份貨物，並獲得 %d張牌。\n", num_of_product, earn);
                printf("請按Enter繼續。\n");
                setbuf(stdin, NULL);
                c = getchar();

                //總結

                int32_t tablecardIdx = 0;

                if(find(MARKET_STAND)) market_stand(player, amountOfPlayer, numberOfPlayer, num_of_product);
                if(find(MARKET_HALL)) market_hall(player, amountOfPlayer, numberOfPlayer, num_of_product);
                if(num_of_product != 0)
                {
                    if(tablecardIdx = find(HARBOR)) harbor(player, amountOfPlayer, numberOfPlayer, tablecardIdx);
                }

                break;

            }
            else
            {

                showCardsOnTable(player, amountOfPlayer);
                cardOnHands(player , numberOfPlayer);
                printf("請輸入生產數量，若不生產則輸入0（你最多可以賣%d份貨）...\n", most_num_of_product);
                printf("\e[1;38;2;255;0;64m輸入值有誤。\n\e[m");         

            }

        }
    }





//card.c
    bool            bot_decision(int32_t chance) //決定出牌機率
    {
        int32_t choice = rand() % 100 + 1;
        if(choice <= chance) return true;
        else 
        return false;
    }

    sCard*          find_handcard(sPlayer* player, int32_t numberOfPlayer, int32_t cardID)
    {

        sCard* currentCard = player[numberOfPlayer].cardOnHand;

        while(currentCard != NULL)
        {
            if(currentCard-> cardNumber == cardID) return currentCard;
            else currentCard = currentCard->linkedListNext;
        }

        return NULL;
    }

    int32_t         findCard(sPlayer* player, int32_t numberOfPlayer, int32_t cardID)
    {
        /*如果找的到號碼 則桌面上有該牌*/
        for(int32_t i = 1;i <= 12;i++)
        {
            if(player[numberOfPlayer].cardOnTable[i].cardNumber == cardID) return i;
        }
        return 0;
    }
    //教堂 辦公大樓 銀行
    void            chapel(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer, int32_t tableCardIndex)
    {

        if(numberOfPlayer != HUMAN)
        {
            if(bot_decision(75)) 
            {
                putCardUnder(player, numberOfPlayer, tableCardIndex, player[numberOfPlayer].cardOnHand);
                printf("%d 號玩家使用【教堂】的功能，將一張牌放至【教堂】下\n", numberOfPlayer);
                player[numberOfPlayer].pointsReceive++;
                sleep(2);
            }

        return;
        }

        showCardsOnTable(player, amountOfPlayers);
        cardOnHands(player, numberOfPlayer);
        printf("由於你建造了【教堂】，因此你可以從手牌放一張牌至【教堂】下（每張牌值1分，遊戲結束時結算）\n");
        printf("請選擇一張牌放至【教堂】下，若不放牌則輸入0。\n");

        chapel_MakeDecision(player, amountOfPlayers, numberOfPlayer, tableCardIndex);
    }

    void            office(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer, int32_t tableCardIndex)
    {
        //回合開始 → 你可以棄掉1或2張牌，然後抽等量的新牌。

        if(numberOfPlayer != HUMAN)
        {

            int32_t card_ToDiscard = rand() % 3;
            
            if(card_ToDiscard != 0)
            {
                for(int32_t i = 0;i < card_ToDiscard;i++) 
                {
                    discard(player, numberOfPlayer, player[numberOfPlayer].cardOnHand);
                }
                draw(player, numberOfPlayer, card_ToDiscard);
                printf("%d 號玩家使用【辦公大樓】的功能，棄掉 %d 張牌並抽等量的新牌。\n", numberOfPlayer, card_ToDiscard);
                sleep(2);
            }

            return;
        } 

        showCardsOnTable(player, amountOfPlayers);
        cardOnHands(player, numberOfPlayer);
        printf("你建造了【辦公大樓】，因此你可以棄掉一或兩張牌，然後抽等量的新牌。\n");
        printf("請輸入棄牌數量（0-2)。\n");

        int32_t         card_ToDiscard = 0;
        char            c = 0;

        while(1)
        {
            
            bool flag = false;
            scanf("%d", &card_ToDiscard);

            if(card_ToDiscard == 0) return;
            if(card_ToDiscard < 0 || card_ToDiscard > 2)
            {

                showCardsOnTable(player, amountOfPlayers);
                cardOnHands(player, numberOfPlayer);
                printf("由於你建造了【辦公大樓】，因此你可以棄掉一或兩張牌，然後抽等量的新牌。\n");
                printf("請輸入棄牌數量（0/1/2 張)。\n");
                continue;

            }

            flag = discardFromHand(player, amountOfPlayers, numberOfPlayer, card_ToDiscard);

            if(flag) break;

        }

        printf("棄牌完成！抽牌中。\n");
        draw(player, numberOfPlayer, card_ToDiscard);
        sleep(1);

        showCardsOnTable(player, amountOfPlayers);
        cardOnHands(player, numberOfPlayer);
        printf("請按Enter繼續。\n");
        setbuf(stdin, NULL);
        c = getchar();

    }

    void            bank(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer, int32_t tableCardIndex)
    {
        //一場遊戲中有一次機會將任意張數的手牌放置銀行下（在遊戲結束時每張值1分）。

        if(numberOfPlayer != HUMAN)
        {

            if(bot_decision(15))
            {
                    
                int32_t amountOfCard = rand() % player[numberOfPlayer].number_cardOnHand + 1;

                for(int32_t i = 0;i < amountOfCard;i++) 
                {
                    putCardUnder(player, numberOfPlayer, tableCardIndex, player[numberOfPlayer].cardOnHand);
                }
                printf("%d 號玩家使用【銀行】的功能，將 %d 張牌放至【銀行】下\n", numberOfPlayer, amountOfCard);
                sleep(2);
            }
            return;
        }

        //有選擇權的人類～

        showCardsOnTable(player, amountOfPlayers);
        cardOnHands(player, numberOfPlayer);
        printf("由於你建造了【銀行】，因此你在一場遊戲中有一次機會將任意張數的手牌放至【銀行】下（在遊戲結束時每張值一分）\n");
        printf("請輸入放牌數量，若不放牌則輸入0。\n");

        int32_t amountOfCard = 0;
        char c = 0;

        while(1)
        {

            bool flag = false;

            scanf("%d", &amountOfCard);

            if(amountOfCard == 0) return;

            if(amountOfCard > player[numberOfPlayer].number_cardOnHand || amountOfCard < 0 )
            {
                showCardsOnTable(player, amountOfPlayers);
                cardOnHands(player, numberOfPlayer);
                printf("由於你建造了【銀行】，因此你在一場遊戲中有一次機會將任意張數的手牌放至【銀行】下（在遊戲結束時每張值一分）\n");
                printf("請輸入放牌數量，若不放牌則輸入0。\n");
                printf("別再搞事了拜託。\n");
                continue;
            }

            showCardsOnTable(player, amountOfPlayers);
            cardOnHands(player, numberOfPlayer);

            printf("請以空格為分隔符，輸入要放入的卡片編號（重複的牌亦須重複輸入）。\n");
            for(int32_t i = 0;i < amountOfCard;i++)
            {

                int32_t     cardID = 0;
                sCard*      card = NULL;
                scanf("%d", &cardID);

                if((card = find_handcard(player, numberOfPlayer, cardID)) != NULL)
                {
                    flag = true;
                    putCardUnder(player, numberOfPlayer, tableCardIndex, card);
                    player[numberOfPlayer].pointsReceive ++;
                }
                else{
                    flag = false;
                    showCardsOnTable(player, amountOfPlayers);
                    cardOnHands(player, numberOfPlayer);
                    printf("請輸入放牌數量，若不放牌則輸入0。\n");
                    printf("別再搞事了拜託。\n");
                    break;
                }

            }

            if(flag) break;

        }

        showCardsOnTable(player, amountOfPlayers);
        cardOnHands(player, numberOfPlayer);
        printf("放牌成功！\n");
        printf("請按Enter繼續。\n");
        setbuf(stdin, NULL);
        c = getchar();
    }
    //鐵匠鋪 採石場 黑市
    void            smithy(sPlayer* player, int32_t numberOfPlayer,sCard* card, int32_t* fee)
    {   //鐵匠鋪 
        //你建築工廠建築時少付一張牌。
        if(card->cardNumber  <= 5)
        { 
            (*fee)--;
            if(numberOfPlayer == HUMAN) printf("由於你建造了【鐵匠舖】，因此你在建造工廠建築時少付一張牌。\n");
        }

    }
    
    void            quarry(sPlayer* player, int32_t numberOfPlayer,sCard* card, int32_t* fee)
    {   //採石場
        //你在建造城市建築時少付1張牌。
        if(card->cardNumber  >  5)
        {
            (*fee)--;
            if(numberOfPlayer == HUMAN) 
                printf("由於你建造了【採石場】，因此你在建造城市建築時少付一張牌。\n");
        }   
    }
    
    void            black_market(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer,int32_t* fee)
    {
        //你可以棄掉任何一份貨物降低建築費用1張牌，或棄掉任何兩份貨物降低建築費用2張手牌。

        int32_t mostDiscard = 0;
        int32_t amountToDiscard = 0;

        for(int32_t i = 1;i <= player[numberOfPlayer].number_cardOnTable;i++)
        {
            if(player[numberOfPlayer].cardOnTable[i].cardHasProduct) mostDiscard++;
        }
        if(mostDiscard > 2) mostDiscard = 2;

        if(numberOfPlayer != HUMAN)
        {

            amountToDiscard = rand() % (mostDiscard + 1);

            if(amountToDiscard == 0) return;

            if((*fee) - amountToDiscard <= player[numberOfPlayer].number_cardOnHand - 1 && player[numberOfPlayer].number_cardOnHand > 1)
            {
                int32_t now_amountToDiscard = 0;
                for(int32_t tablecardIdx = 1;tablecardIdx <= player[numberOfPlayer].number_cardOnTable;tablecardIdx++){
                    if(player[numberOfPlayer].cardOnTable[tablecardIdx].cardHasProduct)
                    {
                        discard_product(player, numberOfPlayer, tablecardIdx);
                        (*fee)--;
                        now_amountToDiscard++;
                        if(now_amountToDiscard == amountToDiscard) break;
                    }
                }
            }

            return;

        }

        showCardsOnTable(player, amountOfPlayers);
        cardOnHands(player, numberOfPlayer);
        printf("你建造了【黑市】，因此你可以棄掉任何一份或兩份貨物，各別降低建築費用一張牌或兩張牌。\n");
        printf("你最多可以棄%d份貨請輸入棄貨數量(若不棄貨則輸入0) : \n", mostDiscard);
        
        while(1)
        {

            bool continueFlag = false;

            scanf("%d", &amountToDiscard);

            if(amountToDiscard == 0) return;

            if(amountToDiscard > 0 && amountToDiscard <= mostDiscard)
            {

                showCardsOnTable(player, amountOfPlayers);
                cardOnHands(player, numberOfPlayer);
                printf("請輸入要棄貨的卡片編號，你要棄掉 %d 份貨（重複的牌亦須重複輸入）。\n", amountToDiscard);

                //check

                int32_t* discard_list = NULL;
                discard_list = (int32_t*)malloc(sizeof(int32_t) * amountToDiscard);
                for(int32_t i = 0;i < amountToDiscard;i++) scanf("%d", &discard_list[i]);

                for(int32_t i = 0;i < amountToDiscard;i++)
                {

                    int32_t tablecardIdx = discard_list[i];

                    if(!player[numberOfPlayer].cardOnTable[tablecardIdx].cardHasProduct || tablecardIdx < 1 || tablecardIdx > player[numberOfPlayer].number_cardOnTable)
                    {
                        continueFlag = true;
                        showCardsOnTable(player, amountOfPlayers);
                        cardOnHands(player , numberOfPlayer);
                        printf("由於你建造了【黑市】，因此你可以棄掉任何一份或兩份貨物，各別降低建築費用一張牌或兩張牌。\n");
                        printf("你最多可以棄%d份貨請輸入棄貨數量(若不棄貨則輸入0) : \n", mostDiscard);
                        printf("\e[1;38;2;255;0;64m輸入值有誤。\n\e[m");
                        break;
                    }
                }

                if(continueFlag) continue;

                for(int32_t i = 0;i < amountToDiscard;i++)
                {
                    int32_t tablecardIdx = discard_list[i];
                    discard_product(player, numberOfPlayer, tablecardIdx);
                    (*fee)--;
                }

                free(discard_list);
                break;

            }
            else
            {
                showCardsOnTable(player, amountOfPlayers);
                cardOnHands(player , numberOfPlayer);
                printf("由於你建造了【黑市】，因此你可以棄掉任何一份或兩份貨物，各別降低建築費用一張牌或兩張牌。\n");
                printf("請輸入棄貨數量，若不棄貨則輸入0（你最多可以棄%d份貨）。\n", mostDiscard);
                printf("\e[1;38;2;255;0;64m輸入值有誤。\n\e[m");

            }

        }

        char c = 0;

        showCardsOnTable(player, amountOfPlayers);
        cardOnHands(player, numberOfPlayer);
        printf("請按Enter繼續。\n");
        setbuf(stdin, NULL);
        c = getchar();


    }
    //木工坊 濟貧院 圖書館  //【】
    void            carpenter(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer, sCard* card)
    {
        //你建造城市建築後抽一張牌。
        if(card->cardNumber > 5)
        {

            if(numberOfPlayer != HUMAN)
            {
                draw(player, numberOfPlayer, 1);
                printf("%d 號玩家使用【木工坊】的功能，建造城市建築抽一張牌。\n", numberOfPlayer);
                return;
            }


            char c = 0;

            showCardsOnTable(player, amountOfPlayers);
            cardOnHands(player, numberOfPlayer);
            printf("由於你建造了【木工坊】，因此你建造城市建築抽一張牌。\n");

            printf("抽牌中。\n");
            sleep(2);
            draw(player, numberOfPlayer, 1);

            showCardsOnTable(player, amountOfPlayers);
            cardOnHands(player, numberOfPlayer);
            printf("請按Enter繼續。\n");
            setbuf(stdin, NULL);
            c = getchar();

        }
    }
    
    void            poor_house(sPlayer* player,int32_t amountOfPlayer, int32_t numberOfPlayer)
    {
        //你在建造完後如果只剩0或1張手牌，則抽1張牌。
        if(player[numberOfPlayer].number_cardOnHand <= 1)
        {

            if(numberOfPlayer != HUMAN)
            {
                draw(player, numberOfPlayer, 1);
                printf("%d 號玩家使用【濟貧院】的功能，在建造完後如果只剩 0 或 1 張手牌，則抽 1 張牌。\n", numberOfPlayer);
                return;
            }        
            
            char c = 0;

            showCardsOnTable(player, amountOfPlayer);
            cardOnHands(player, numberOfPlayer);
            printf("你建造了【濟貧院】， 該卡片功能：你在建造完後如果只剩 0 或 1 張手牌，則抽 1 張牌。\n");

            printf("抽牌中...\n");
            sleep(3);
            draw(player, numberOfPlayer, 1);

            showCardsOnTable(player, amountOfPlayer);
            cardOnHands(player, numberOfPlayer);
            printf("請按Enter繼續...\n");
            setbuf(stdin, NULL);
            c = getchar();

        }

    }
        
    void            library(sPlayer* player, int32_t numberOfPlayer, int32_t* fee, int32_t profession)
    {
        //特權 * 2
        switch (profession)
        {
        case BUILDER:
                (*fee) -= 2;
                if(numberOfPlayer == HUMAN) 
                    printf("由於你建造了【圖書館】，因此你在建造任何建築時少付兩張牌。\n");
            break;
        case COUNCILLOR:
                if(numberOfPlayer == HUMAN)
                    printf("由於你建造了【圖書館】，因此你在議員階段可額外再抽六張牌，總計八張。\n");
                else 
                    printf("%d 號玩家使用【圖書館】的功能，額外再抽六張牌，總計八張。\n", numberOfPlayer);
            break;

        case PROSPECTOR:
                if(numberOfPlayer == HUMAN) 
                    printf("由於你建造了【圖書館】，因此你可以抽兩張牌\n");
                else 
                    printf("%d 號玩家使用【圖書館】的功能，可以抽兩張牌\n", numberOfPlayer);
            break;

        case TRADER:
                if(numberOfPlayer == HUMAN) 
                    printf("由於你建造了【圖書館】，因此你可以多賣兩份貨\n");
                else 
                    printf("%d號玩家使用【圖書館】的功能，可以多賣兩份貨\n", numberOfPlayer);
            break;

        case PRODUCER:
                if(numberOfPlayer == HUMAN) 
                    printf("由於你建造了【圖書館】，因此你可以多生產兩份貨物\n");
                else 
                    printf("%d 號玩家使用【圖書館】的功能，可以多生產兩份貨物\n", numberOfPlayer);
            break;
        }
    }
    // 起重機 【檔案室】 【總督府】 【海關】 
    int32_t         crane(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer, sCard* card)
    {
        //【起重機】
        showCardsOnTable(player, amountOfPlayers);
        cardOnHands(player, numberOfPlayer);
        printf("由於你建造了【起重機】，因此你可以用新建築蓋掉先前的建築，並支付差額\n");
        printf("請輸入欲改建的建築編號(若不改建則輸入0): \n");

        while(1)
        {

            int32_t tablecardIdx = 0;
            scanf("%d", &tablecardIdx);

            if(tablecardIdx >= 0 && tablecardIdx <= player[numberOfPlayer].number_cardOnTable) 
                return tablecardIdx;
            else
            {

                showCardsOnTable(player, amountOfPlayers);
                cardOnHands(player, numberOfPlayer);
                printf("由於你建造了【起重機】，因此你可以用新建築蓋掉先前的建築，並支付差額\n");
                printf("請輸入欲改建的建築編號(若不改建則輸入0):\n");
                printf("\e[1;38;2;255;0;64m請輸入有效值！\n\n\e[m");

            }

        }
    }

    void            archive(int32_t numberOfPlayer, int32_t* original_NumberOfHandcard)
    {
        (*original_NumberOfHandcard) = 0;

        if(numberOfPlayer == HUMAN) 
            printf("由於你建造了【檔案室】，因此你可以從抽取的牌或從手牌中棄牌\n");
        else 
            printf("%d 號玩家使用【檔案室】的功能，從抽取的牌或從手牌中棄牌\n", numberOfPlayer);
    }

    void            prefecture(int32_t numberOfPlayer, int32_t amountOfCard, int32_t* amountOfDiscard)
    {
        // 【總督府】
        (*amountOfDiscard) = amountOfCard - 2;

        if(numberOfPlayer == HUMAN) 
            printf("由於你建造了【總督府】，因此你可以在抽牌時多保留一張牌\n");
        else 
            printf("%d 號玩家使用【總督府】的功能，抽牌後多保留一張牌\n", numberOfPlayer);
    }
    
    void            customs_office(sPlayer* player ,int32_t amountOfPlayers, int32_t numberOfPlayer, int32_t tablecardIdx)
    {
        //【海關】 放一份貨物至海關。 交易階段 →賣此貨物得2張牌。

        if(numberOfPlayer != HUMAN)
        {
            if(bot_decision(90))
            {
                printf("%d 號玩家使用【海關】的功能，放一份貨物至海關\n", numberOfPlayer);
                produce_product(player, numberOfPlayer, tablecardIdx);
            }
        return;
        }

        //玩家
        char choice = 0;
        char c = 0;

        showCardsOnTable(player, amountOfPlayers);
        cardOnHands(player, numberOfPlayer);
        printf("你建造了【海關】，因此你可以放一份貨物至海關。\n");
        printf("是否在海關生產貨物？(y/n)\n");

        while(1)
        {
            
            choice = fgetc(stdin);

            if(choice == 'y')
            {
                produce_product(player, numberOfPlayer, tablecardIdx);
                showCardsOnTable(player, amountOfPlayers);
                cardOnHands(player, numberOfPlayer);
                printf("生產完成。請按Enter繼續。\n");
                setbuf(stdin, NULL);
                c = getchar();
                return;
            }
            else if(choice == 'n') return;
            else
            {
                showCardsOnTable(player, amountOfPlayers);
                cardOnHands(player, numberOfPlayer);
                printf("由於你建造了【海關】，因此你可以放一份貨物至海關。\n");
                printf("是否在海關生產貨物？(y/n)\n");
                printf("\e[1;38;2;255;0;64m請輸入有效值！\n\n\e[m");
            }

        }
    }
    //【上水道】 【水井】 【金工坊】  【金礦】
    void            aquaduct(int32_t numberOfPlayer,int32_t* mostProduct)
    {
        // 生產階段 → 你多生產1份貨物。
        (*mostProduct)++;
        if(numberOfPlayer == HUMAN) printf("你建造了【下水道】，你可以多生產一份貨物。\n");
        else printf("%d 號玩家使用【下水道】。能力：可以多生產一份貨物。\n", numberOfPlayer);
    }
    
    void            well(sPlayer* player,int32_t amountOfPlayers,int32_t numberOfPlayer,int32_t amountProduct)
    {
        // 生產階段 → 你生產至少2份貨物時，抽1張牌。
        if(amountProduct >= 2)
        {

            if(numberOfPlayer != HUMAN)
            {
                draw(player, numberOfPlayer, 1);
                printf("%d 號玩家使用【水井】。卡牌效果：生產至少兩份貨物時抽一張牌。\n", numberOfPlayer);
                return;
            }

            char c = 0;

            showCardsOnTable(player, amountOfPlayers);
            cardOnHands(player, numberOfPlayer);
            printf("由於你建造了【水井】。卡牌效果：因此你生產至少兩份貨物時，抽一張牌。\n");

            printf("抽牌中。\n");
            sleep(2);
            draw(player, numberOfPlayer, 1);

            showCardsOnTable(player, amountOfPlayers);
            cardOnHands(player, numberOfPlayer);
            printf("請按Enter繼續。n");
            c = getchar();

        }
    }

    void            goldsmith(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer)
    {
        //你抽1張牌，若尚未有任何玩家建造此建築，即可保留它，否則丟入棄牌堆。
        char c = 0;

        if(numberOfPlayer != HUMAN)
        {

            printf("%d 號玩家使用【金工坊】。功能：抽一張牌，若尚未有任何玩家建造此建築，即可保留它，否則丟入棄牌堆。\n", numberOfPlayer);

            draw(player, numberOfPlayer, 1);

            sCard* card = player[numberOfPlayer].cardOnHand;
            while(card-> linkedListNext != NULL) card = card -> linkedListNext;
            char* nameOfCard = card -> cardName;   //backup

            //find if there exists a same building

            bool success = true;

            for(int32_t i = 1;i <= amountOfPlayers;i++)
            {
                for(int32_t tablecardIdx = 1; tablecardIdx < player[i].number_cardOnTable;tablecardIdx++)
                {
                    if(player[i].cardOnTable[tablecardIdx].cardNumber == card->cardNumber)
                    {
                        success = false;
                        discard(player, numberOfPlayer, card);
                        break;
                    }
                }
                if(!success) break;
            }

            if(success) printf("%d號玩家保留了卡牌\n", numberOfPlayer);
            else printf("%d號玩家抽到了%s，因此丟入棄牌堆\n", numberOfPlayer, nameOfCard);

            return;
        }

        showCardsOnTable(player, amountOfPlayers);
        cardOnHands(player, numberOfPlayer);
        printf("由於你建造了【金工坊】。\t功能：因此你抽一張牌，若尚未有任何玩家建造此建築，即可保留它，否則丟入棄牌堆。\n");

        printf("抽牌中。\n");
        sleep(2);
        draw(player, numberOfPlayer, 1);

        //find the card

        sCard* card = player[numberOfPlayer].cardOnHand;
        while(card->linkedListNext != NULL) card = card->linkedListNext;
        char* nameOfCard = card->cardName;   //backup

        //find if there exists a same building

        bool success = true;

        for(int32_t i = 1;i <= amountOfPlayers;i++)
        {
            for(int32_t tablecardIdx = 1;tablecardIdx < player[i].number_cardOnTable;tablecardIdx++)
            {

                if(player[i].cardOnTable[tablecardIdx].cardNumber == card->cardNumber)
                {
                    success = false;
                    discard(player, numberOfPlayer, card);
                    break;
                }
            }
            if(!success) break;
        }

        showCardsOnTable(player, amountOfPlayers);
        cardOnHands(player, numberOfPlayer);
        printf("你抽到%s。\n", nameOfCard);

        if(success) printf("由於尚未有玩家建造此建築，因此保留卡牌。\n");
        else printf("已有人建造此建築，因此丟入棄牌堆。\n");

        printf("\n請按Enter繼續。\n");
        c = getchar();
    }

    void            goldmine(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer)
    {
        // 你抽4張牌，若它們的建築費用皆不同，保留其中費用最便宜的一張。
        char c = 0;

        //機器人
        if(numberOfPlayer != HUMAN)
        {
            if(bot_decision(90))
            {

                printf("%d 號玩家使用【金礦】。功能：抽四張牌，若它們的建築費用皆不同，保留其中費用最便宜的一張。\n", numberOfPlayer);
                
                int32_t num_of_handcard_origin = player[numberOfPlayer].number_cardOnHand; //backup
                draw(player, numberOfPlayer, 4);

                //Judge

                //find the start of cards that can be discarded

                sCard* currentCard = player[numberOfPlayer].cardOnHand;
                sCard* pre = NULL;
                sCard* start = NULL;
                sCard* search = NULL;
                int32_t currentCardNum = 1;

                while(currentCard != NULL)
                {     //set start of display
                    if(currentCardNum == num_of_handcard_origin + 1) break;
                    currentCard = currentCard->linkedListNext;
                    currentCardNum++;
                }
                start = currentCard;

                //find if there is a duplicate number

                bool success = true;

                while(currentCard != NULL)
                {
                    search = currentCard->linkedListNext;
                    while(search != NULL)
                    {
                        if(currentCard->cardCost == search->cardCost)
                        {
                            success = false;
                            break;
                        }
                        search = search->linkedListNext;
                    }
                    currentCard = currentCard->linkedListNext;
                    if(!success) break;
                }

                if(success) printf("成功。%d 號玩家可以保留費用最便宜的一張。\n", numberOfPlayer);
                else printf("%d 號玩家失敗，沒挖到東西。\n", numberOfPlayer);

                //discard

                if(success)
                {

                    int32_t min = INT32_MAX;
                    sCard* minCard = NULL;

                    //find the minimum cost

                    currentCard = start;
                    while(currentCard != NULL)
                    {
                        if(min > currentCard->cardCost)
                        {
                            min = currentCard->cardCost;
                            minCard = currentCard;
                        }
                        currentCard = currentCard->linkedListNext;
                    }

                    //discard

                    currentCard = start;
                    while(currentCard != NULL)
                    {
                        pre = currentCard;
                        currentCard = currentCard->linkedListNext;
                        if(pre != minCard) discard(player, numberOfPlayer, pre);
                    }

                }
                else
                {
                    //discard

                    currentCard = start;
                    while(currentCard != NULL)
                    {
                        pre = currentCard;
                        currentCard = currentCard->linkedListNext;
                        discard(player, numberOfPlayer, pre);
                    }

                }
            }
            return;
        }

        //玩家
        showCardsOnTable(player, amountOfPlayers);
        cardOnHands(player, numberOfPlayer);
        printf("由於你建造了【金礦】。能：抽四張牌，若它們的建築費用皆不同，保留其中費用最便宜的一張。\n");
        printf("請選擇動作（1:使用金礦功能 2:離開）。\n");

        while(1){

            int32_t choice = 0;
            scanf("%d", &choice);

            if(choice == 1) break;
            
            if(choice == 2) return;
            if(choice != 1 || choice != 4)
            {
                showCardsOnTable(player, amountOfPlayers);
                cardOnHands(player, numberOfPlayer);
                printf("請選擇動作（1:使用金礦功能 2:離開）。\n");
                printf("\e[1;38;2;255;0;64m請輸入有效值！\n\n\e[m");
            }
        }
        
        int32_t num_of_handcard_origin = player[numberOfPlayer].number_cardOnHand; //backup

        showCardsOnTable(player, amountOfPlayers);
        printf("「挖寶」中。\n");
        sleep(2);
        draw(player, numberOfPlayer, 4);

        //Judge

        //find the start of cards that can be discarded

        sCard* currentCard = player[numberOfPlayer].cardOnHand;
        sCard* pre = NULL;
        sCard* start = NULL;
        sCard* search = NULL;
        int32_t currentCardNum = 1;

        while(currentCard != NULL)
        {     //set start of display
            if(currentCardNum == num_of_handcard_origin + 1) break;
            currentCard = currentCard -> linkedListNext;
            currentCardNum++;
        }
        start = currentCard;

        //find if there is a duplicate number

        bool success = true;

        while(currentCard != NULL)
        {
            search = currentCard->linkedListNext;
            while(search != NULL)
            {
                if(currentCard->cardCost == search->cardCost)
                {
                    success = false;
                    break;
                }
                search = search->linkedListNext;
            }
            currentCard = currentCard-> linkedListNext;
            if(!success) break;
        }

        showCardsOnTable(player, amountOfPlayers);
        cardOnHands_part(player, numberOfPlayer, start);
        if(success) printf("成功。你可以保留費用最便宜的一張。\n");
        else printf("你沒挖到「寶」。\n");
        printf("\n請按Enter繼續。\n");
        setbuf(stdin, NULL);
        c = getchar();

        //discard

        if(success)
        {

            int32_t min = INT32_MAX;
            sCard* minCard = NULL;

            //find the minimum cost

            currentCard = start;
            while(currentCard != NULL)
            {
                if(min > currentCard->cardCost)
                {
                    min = currentCard->cardCost;
                    minCard = currentCard;
                }
                currentCard = currentCard->linkedListNext;
            }

            //discard

            currentCard = start;
            while(currentCard != NULL)
            {
                pre = currentCard;
                currentCard = currentCard->linkedListNext;
                if(pre != minCard) discard(player, numberOfPlayer, pre);
            }

        }
        else
        {
            //discard

            currentCard = start;
            while(currentCard != NULL)
            {
                pre = currentCard;
                currentCard = currentCard->linkedListNext;
                discard(player, numberOfPlayer, pre);
            }

        }

        showCardsOnTable(player, amountOfPlayers);
        cardOnHands(player, numberOfPlayer);
        printf("請按Enter繼續。\n");
        c = getchar();



    }
    //【貿易站】【攤販】【市場】【港口】
    void            trading_post(int32_t numberOfPlayer, int32_t* mostProduct)
    {
        //交易階段 → 你可以額外賣1份貨物。
        (*mostProduct)++;
        if(numberOfPlayer == HUMAN) 
            printf("你建造了【貿易站】。功能：因此你可以多賣一份貨物。\n");
        else 
            printf("%d 號玩家使用【貿易站】。功能：可以多賣一份貨物。\n", numberOfPlayer);
    }

    void            market_stand(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer, int32_t amountProduct)
    {

        // 交易階段 → 你賣至少2份貨物時，抽1張牌。
          if(amountProduct >= 2)
          {

            if(numberOfPlayer != HUMAN)
            {
                printf("%d 號玩家使用【貿易站】。功能：賣至少兩份貨物時抽一張牌。\n", numberOfPlayer);
                draw(player, numberOfPlayer, 1);
                return;
            }

            char c = 0;

            showCardsOnTable(player, amountOfPlayers);
            cardOnHands(player, numberOfPlayer);
            printf("你建造了【貿易站】。功能：因此你賣至少兩份貨物時，抽一張牌。\n");

            printf("抽牌中。\n");
            sleep(2);
            draw(player, numberOfPlayer, 1);

            showCardsOnTable(player, amountOfPlayers);
            cardOnHands(player, numberOfPlayer);
            printf("請按Enter繼續。\n");
            c = getchar();

        }
    }

    void            market_hall(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer, int32_t amountProduct)
    {
        // 交易階段 → 你賣至少1份貨物時，抽1張牌。
         if(amountProduct >= 1)
         {

            if(numberOfPlayer != HUMAN)
            {
                printf("%d號玩家使用【市場】。功能：賣至少一份貨物時抽一張牌。\n", numberOfPlayer);
                draw(player, numberOfPlayer, 1);
                return;
            }

            char c = 0;

            showCardsOnTable(player, amountOfPlayers);
            cardOnHands(player, numberOfPlayer);
            printf("你建造了【市場】。功能：因此你賣至少一份貨物時，抽一張牌。\n");

            printf("抽牌中。\n");
            sleep(3);
            draw(player, numberOfPlayer, 1);

            showCardsOnTable(player, amountOfPlayers);
            cardOnHands(player, numberOfPlayer);
            printf("請按Enter繼續。\n");
            c = getchar();

        }

    }

    void            harbor(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer, int32_t tableCardIndex)
    {
        //交易階段 → 你將1份剛賣掉的貨放在港口下（遊戲結束時每張值1分）。

        if(numberOfPlayer != HUMAN)
        {
            if(bot_decision(90)){
                printf("%d 號玩家使用【港口】。功能:將一份剛賣掉的貨放在港口下。\n", numberOfPlayer);
                
                //produce from discard deck

                sCard* pre = NULL;
                sCard* now = player[numberOfPlayer].cardOnTable[tableCardIndex].linkedListNext;

                while(now != NULL)
                {
                    pre = now;
                    now = now->linkedListNext;
                }

                now = (sCard*)malloc(sizeof(sCard));
                memcpy(now, &discardDeck[discardDeckIndex-1], sizeof(sCard));
                memset(&discardDeck[discardDeckIndex-1], 0, sizeof(sCard));

                //Redirect

                if(player[numberOfPlayer].cardOnTable[tableCardIndex].subcard != 0)
                {
                    now->linkedListNext = pre->linkedListNext;
                    pre->linkedListNext = now;
                }
                else{
                    now->linkedListNext = NULL;
                    player[numberOfPlayer].cardOnTable[tableCardIndex].linkedListNext = now;
                }

                //others

                player[numberOfPlayer].cardOnTable[tableCardIndex].cardHasProduct = true;
                player[numberOfPlayer].cardOnTable[tableCardIndex].subcard++;
                player[numberOfPlayer].pointsReceive++;
                discardDeckIndex--;
                player[0].number_cardOnTable = discardDeckIndex;

            }
            return;
        }

        char choice = 0;
        char c = 0;

        showCardsOnTable(player, amountOfPlayers);
        cardOnHands(player, numberOfPlayer);
        printf("你建造了【港口】。功能：因此你可以將一份剛賣掉的貨放在港口下（遊戲結束時值一分）。\n");
        printf("是否放牌？(y/n)\n");
        
        while(1)
        {
            
            choice = fgetc(stdin);

            if(choice == 'y')
            {
                
                //produce from discard deck

                sCard* pre = NULL;
                sCard* now = player[numberOfPlayer].cardOnTable[tableCardIndex].linkedListNext;

                while(now != NULL)
                {
                    pre = now;
                    now = now->linkedListNext;
                }

                now = (sCard*)malloc(sizeof(sCard));
                memcpy(now, &discardDeck[discardDeckIndex-1], sizeof(sCard));
                memset(&discardDeck[discardDeckIndex-1], 0, sizeof(sCard));

                //Redirect

                if(player[numberOfPlayer].cardOnTable[tableCardIndex].subcard != 0)
                {
                    now->linkedListNext = pre->linkedListNext;
                    pre->linkedListNext = now;
                }
                else
                {
                    now->linkedListNext = NULL;
                    player[numberOfPlayer].cardOnTable[tableCardIndex].linkedListNext = now;
                }

                //others

                player[numberOfPlayer].cardOnTable[tableCardIndex].cardHasProduct = true;
                player[numberOfPlayer].cardOnTable[tableCardIndex].subcard++;
                player[numberOfPlayer].pointsReceive++;
                discardDeckIndex--;
                player[0].number_cardOnTable = discardDeckIndex;

                showCardsOnTable(player, amountOfPlayers);
                cardOnHands(player, numberOfPlayer);
                printf("放牌完成。請按Enter繼續。\n");
                setbuf(stdin, NULL);
                c = getchar();
                return;
            }
            else if(choice == 'n') return;
            else
            {
                showCardsOnTable(player, amountOfPlayers);
                cardOnHands(player, numberOfPlayer);
                printf("你建造了【港口】。功能：因此你可以將一份剛賣掉的貨放在港口下（遊戲結束時值一分）。\n");
                printf("是否放牌？(y/n)\n");
                printf("\e[1;38;2;255;0;64m請輸入有效值！\n\n\e[m");
            }

        }

    }
    //【酒館】 【茅屋】 【公會】 【市政廳】 
    void            tavern(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer)
    {
        //建築階段 → 在建築階段結束時，若你的建築物數量最少，則抽1張牌。
        int32_t min = 0;
        int32_t minNum = 0;

        for(int32_t i = 1;i <= amountOfPlayers;i++)
        {

            if(min > player[i].number_cardOnTable)
            {
                min = player[i].number_cardOnTable;
                minNum = i;
            }

        }

        for(int32_t i = 1;i <= amountOfPlayers;i++)
        {
            if(min == player[i].number_cardOnTable && i != minNum) 
                return;
        }

        if(minNum == numberOfPlayer)
        {

            if(numberOfPlayer != HUMAN)
            {
                showCardsOnTable(player, amountOfPlayers);
                printf("%d 號玩家使用【酒館】。功能：因建築物最少而抽一張牌。\n", numberOfPlayer);
                sleep(3);
                draw(player, numberOfPlayer, 1);
                return;
            }        
            
            char c = 0;

            showCardsOnTable(player, amountOfPlayers);
            cardOnHands(player, numberOfPlayer);
            printf("你建造了【酒館】。功能：若你的建築物數量最少，則抽一張牌。\n");

            printf("抽牌中。\n");
            sleep(2);
            draw(player, numberOfPlayer, 1);

            showCardsOnTable(player, amountOfPlayers);
            cardOnHands(player, numberOfPlayer);
            printf("請按Enter繼續。\n");
            setbuf(stdin, NULL);
            c = getchar();

        }

    }

    void            cottage(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer)
    {
        //交易階段 → 如果沒有任何玩家賣貨物，則你抽一張牌。
        if(numberOfPlayer != HUMAN)
        {
            showCardsOnTable(player, amountOfPlayers);
            printf("%d 號玩家使用【茅屋】。功能：當沒有任何玩家賣貨物時而抽一張牌。\n", numberOfPlayer);
            sleep(2);
            draw(player, numberOfPlayer, 1);
            return;
        }        
        
        char c = 0;

        showCardsOnTable(player, amountOfPlayers);
        cardOnHands(player, numberOfPlayer);
        printf("你建造了【茅屋】，當沒有任何玩家賣貨物時抽一張牌。\n");

        printf("抽牌中。\n");
        sleep(2);
        draw(player, numberOfPlayer, 1);

        showCardsOnTable(player, amountOfPlayers);
        cardOnHands(player, numberOfPlayer);
        printf("請按Enter繼續。\n");
        setbuf(stdin, NULL);
        c = getchar();
    }

    void            guild_hall(sPlayer* player, int32_t numberOfPlayer)
    {

        int32_t sum = 0;

        for(int32_t tablecardIdx = 1;tablecardIdx <= player[numberOfPlayer].number_cardOnTable;tablecardIdx++)
        {
            if(player[numberOfPlayer].cardOnTable[tablecardIdx].cardNumber <= 5)
            {
                player[numberOfPlayer].pointsReceive++;
                sum++;
            }
        }

        bool record[6] = {0};

        for(int32_t tablecardIdx = 1;tablecardIdx <= player[numberOfPlayer].number_cardOnTable;tablecardIdx++)
        {
            if(player[numberOfPlayer].cardOnTable[tablecardIdx].cardNumber <= 5)
            {
                int32_t id = player[numberOfPlayer].cardOnTable[tablecardIdx].cardNumber;
                if(!record[id])
                {
                    player[numberOfPlayer].pointsReceive++;
                    sum++;
                    record[id] = true;
                }
            }
        }

        printf("%d 號玩家使用【公會】。功能：額外得了%d分。\n", numberOfPlayer, sum);

    }   

    void            city_hall(sPlayer* player, int32_t numberOfPlayer)
    {
        int32_t sum = 0;

        for(int32_t tablecardIdx = 1;tablecardIdx <= player[numberOfPlayer].number_cardOnTable;tablecardIdx++)
        {
            if(player[numberOfPlayer].cardOnTable[tablecardIdx].cardNumber > 5) 
                player[numberOfPlayer].pointsReceive++;
            sum++;
        }

        printf("%d 號玩家使用【市政廳】。 功能：額外得了 %d 分。\n", numberOfPlayer, sum);
    }
    //【凱旋門】 【皇宮】 【官邸】 【】
    void            triumphal_arch(sPlayer* player, int32_t numberOfPlayer)
    {
        //透過紀念碑獲取額外分數
        int32_t count = 0;
        int32_t sum = 0;

        for(int32_t tablecardIdx = 1;tablecardIdx <= player[numberOfPlayer].number_cardOnTable;tablecardIdx++)
        {
            if (player[numberOfPlayer].cardOnTable[tablecardIdx].cardNumber >= 22 
                && 
                player[numberOfPlayer].cardOnTable[tablecardIdx].cardNumber <= 24)
            {
                count++;
            }
        }

        if(count == 1) sum = 4;
        if(count == 2) sum = 6;
        if(count >= 3) sum = 8;
        player[numberOfPlayer].pointsReceive += sum;
        
        printf("%d 號玩家使用【凱旋門】。功能：額外得了%d分。\n", numberOfPlayer, sum);
    }

    void            palace(sPlayer* player, int32_t numberOfPlayer)
    {
        int32_t sum = 0;
        sum = player[numberOfPlayer].pointsReceive / 4;
        player[numberOfPlayer].pointsReceive += sum;

        printf("%d 號玩家使用【皇宮】。功能：額外得了%d分。\n", numberOfPlayer, sum);
    }

    void            residence(sPlayer* player, int32_t numberOfPlayer)
    {
       
        int32_t     sum = 0;
        int32_t     groupCnt = rand()% 2 +1;
        if(groupCnt == 1) sum = 4;
        if(groupCnt == 2) sum = 7;
        if(groupCnt == 3) sum = 9;
        if(groupCnt >= 4) sum = 10;
        player[numberOfPlayer].pointsReceive += sum;

        printf("% d號玩家使用【官邸】。功能：額外得了%d分。\n", numberOfPlayer, sum);

    }

// printf("\e[1;38;2;255;0;64m請輸入有效值！\n\n\e[m");