#pragma once

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <iso646.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <signal.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <uchar.h>
#include <wchar.h>
#include <wctype.h>
#include <getopt.h>
#include <fcntl.h>
#include <unistd.h>


#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/poll.h>
#include <sys/time.h>
#include <sys/mman.h>


#define WRONG_PLAYER_NUMBER     999
#define INCONCLUSIVE            -1
#define HUMAN                   1


//profession

#define BUILDER 1
#define COUNCILLOR 2
#define PRODUCER 3
#define PROSPECTOR 4
#define TRADER 5

//card

#define INDIGO 1
#define SUGAR 2
#define TOBACCO 3
#define COFFEE 4
#define SILVER 5
#define SMITHY 6 //
#define GOLDMINE 7 //
#define ARCHIVE 8 //
#define POOR_HOUSE 9 //
#define MARKET_STAND 10 //
#define BLACK_MARKET 11 //
#define TRADING_POST 12 //
#define WELL 13 //
#define CRANE 14 //
#define CHAPEL 15 //
#define TOWER 16
#define AQUEDUCT 17 //
#define CARPENTER 18 //
#define PREFECTURE 19 //
#define MARKET_HALL 20 //
#define QUARRY 21 //
#define LIBRARY 22 //
#define STATUE 23
#define VICTORY_COLUMN 24
#define HERO 25
#define GUILD_HALL 26 //
#define CITY_HALL 27 //
#define TRIUMPHAL_ARCH 28 //
#define PALACE 29 //
#define GUARD_ROOM 30 //
#define OFFICE_BUILDING 31 //
#define COTTAGE 32 //
#define TAVERN 33 //
#define PARK 34
#define BANK 35 //
#define CUSTOMS_OFFICE 36  //
#define HARBOR 37 //
#define GOLDSMITH 38 //
#define RESIDENCE 39 //




//Structure
    typedef struct structureOfCard
    {
        int32_t                      cardNumber;
        char*                        cardName;
        char*                        cardDescription;
        int32_t                      cardCost;
        bool                         cardHasProduct;
        int32_t                      cardScore;
        struct structureOfCard*      linkedListNext;    
        int32_t                      subcard; //紀錄分數用的   
    } __attribute__((packed)) sCard;

    typedef struct
    {
        sCard*      cardOnHand;
        sCard       cardOnTable[13];
        int32_t     number_cardOnHand;
        int32_t     number_cardOnTable; 
        int32_t     pointsReceive;

    }__attribute__((packed)) sPlayer;


//functions to prepare
    void            printIntroduction();
    //版面
    int32_t         showSelectionList();
    //選擇開始or離開
    int32_t         getPlayerNumber();
    //選擇玩家數量
    void            printErrorMessage(int32_t messageNumber);
    //print出錯誤訊息
    void            initialize_Player(sPlayer *a, int32_t  amountOfPlayers);
    //玩家初始化
    void            initialize_Deck();
    //卡牌初始化設定
    void            initialize_Card(int32_t cardAmount, int32_t cardNumber, char* cardName, char* cardDescription, int32_t cardCost, int32_t cardPoint);
    //卡牌初始化
    void            shuffle(int32_t amount_InitializedCard);
    //洗牌
    void            cardDistribute(sPlayer *player, int32_t numberOfPlayers, int32_t governor);
    //發牌
    void            draw(sPlayer* player, int32_t governor, int32_t amountOfCard);
    //抽牌
    
//function game start
    void            round_start(sPlayer* player,int32_t numberOfPlayers,int32_t governor);
    void            showCardsOnTable(sPlayer* player,int32_t numberOfPlayers);
    void            discard(sPlayer* player, int32_t numberOfPlayer, sCard* preCard);
    void            cardOnHands(sPlayer* player, int32_t numberOfPlayer);
    void            cardOnHands_part(sPlayer* player, int32_t numberOfPlayer, sCard* startCard);
    void            displayCardDescription(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer);
    void            display_TableCardDescription(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer);
    sCard*          find_handcard(sPlayer* player, int32_t numberOfPlayer, int32_t card_id);
    bool            discardFromHand(sPlayer *player, int32_t amountOfPlayers, int32_t numberOfPlayer, int32_t amountOfDiscardCard);
    int32_t         chooseProfession(sPlayer* player,int32_t numberOfPlayers,int32_t professionOfPlayer);
    void            chapel_MakeDecision(sPlayer* player, int32_t amountOfPlayer, int32_t numberOfPlayer, int32_t tableCardIndex);
    bool            office_MakeDecision(sPlayer* player, int32_t amountOfPlayer, int32_t numberOfPlayer, int32_t tableCardIndex);
    void            produce_product(sPlayer* player, int32_t numberOfPlayer, int32_t tableCardIndex);
    bool            game_end(sPlayer* player, int32_t amountOfPlayers);

//functions of 職業設定
    void            pro_Builder(sPlayer* player,int32_t amountOfPlayer,int32_t professionOfPlayer,int32_t numberOfPlayers);  
    void                build(sPlayer* player, int32_t amountOfPlayer,int32_t  professionOfPlayer,int32_t numberOfPlayer);

    void            pro_Councillor(sPlayer* player,int32_t amountOfPlayer,int32_t professionOfPlayer,int32_t numberOfPlayers);
    void                councillor(sPlayer* player, int32_t amountOfPlayer, int32_t professionOfPlayer, int32_t numberOfPlayer);
    
    void            pro_Producer(sPlayer* player,int32_t amountOfPlayer,int32_t professionOfPlayer,int32_t numberOfPlayers);
    
    void            pro_Prospector(sPlayer* player,int32_t amountOfPlayer,int32_t professionOfPlayer,int32_t numberOfPlayers);
    
    void            pro_Trader(sPlayer* player,int32_t amountOfPlayer,int32_t professionOfPlayer,int32_t numberOfPlayers);

//functions of Cards
    bool            bot_decision(int32_t chance);
    int32_t         findCard(sPlayer* player, int32_t numberOfPlayer, int32_t cardID);
    void            office(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer, int32_t tableCardIndex);
    void            bank(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer, int32_t tableCardIndex);
    void            chapel(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer, int32_t tableCardIndex);
    void            carpenter(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer, sCard* card);
    void            smithy(sPlayer* player, int32_t numberOfPlayer,sCard* card, int32_t* fee);
    void            quarry(sPlayer* player, int32_t numberOfPlayer,sCard* card, int32_t* fee);
    void            black_market(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer,int32_t* fee);
    void            poor_house(sPlayer* player,int32_t amountOfPlayer, int32_t numberOfPlayer);
    void            library(sPlayer* player, int32_t numberOfPlayer, int32_t* fee, int32_t profession);
    int32_t         crane(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer, sCard* card);
    void            archive(int32_t numberOfPlayer, int32_t* original_NumberOfHandcard);
    void            prefecture(int32_t numberOfPlayer, int32_t amountOfCard, int32_t* amountOfDiscard);
    void            customs_office(sPlayer* player ,int32_t amountOfPlayer, int32_t numberOfPlayer, int32_t tablecardIdx);
    void            aquaduct(int32_t numberOfPlayer,int32_t* amountProduct);
    void            well(sPlayer* player,int32_t amountOfPlayers,int32_t numberOfPlayer,int32_t amountProduct);
    void            goldsmith(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer);
    void            goldmine(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer);
    void            trading_post(int32_t numberOfPlayer, int32_t* mostProduct);
    void            market_stand(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer, int32_t amountProduct);
    void            market_hall(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer, int32_t amountProduct);
    void            harbor(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer, int32_t tableCardIndex);
    void            tavern(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer);
    void            cottage(sPlayer* player, int32_t amountOfPlayers, int32_t numberOfPlayer);
    void            guild_hall(sPlayer* player, int32_t numberOfPlayer);
    void            city_hall(sPlayer* player, int32_t numberOfPlayer);
    void            triumphal_arch(sPlayer* player, int32_t numberOfPlayer);
    void            palace(sPlayer* player, int32_t numberOfPlayer);
    void            residence(sPlayer* player, int32_t numberOfPlayer);