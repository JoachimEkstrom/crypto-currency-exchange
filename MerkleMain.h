#pragma once
#include "OrderBook.h"
#include "Wallet.h"
class MerkleMain {
    public: 
        MerkleMain(); 
        void init();

    private:
        void printMenu();
        void printHelp();
        void printMarketStats();
        void enterAsk();
        void enterBid();
        void printWallet();
        void gotoNextTimeframe();
        int  getUserOption();
        void processUserOption(int userOption);

        std::string currentTime;
        std::string previousTime;
        OrderBook orderBook{"data.csv"};
        Wallet wallet;
};
