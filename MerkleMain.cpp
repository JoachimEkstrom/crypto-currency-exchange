#include "MerkleMain.h"   
#include <iostream>
#include <string>
#include <ios> //used to get stream size
#include <limits> //used to get numeric limits

MerkleMain::MerkleMain(){}; 
void MerkleMain::init()
{
    int input;
    while(true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
};

void MerkleMain::printMenu(){

    std::cout << "\n	Main Menu \n" << std::endl;
    std::cout << "	1: Print help" << std::endl;
    std::cout << "	2: Print exchange stats" << std::endl;
    std::cout << "	3: Place an ask" << std::endl;
    std::cout << "	4: Place an bid" << std::endl;
    std::cout << "	5: Print wallet" << std::endl;
    std::cout << "	6: Continue \n" << std::endl;
    
    return;
};

void MerkleMain::printHelp(){
    std::cout << "This is the Help menu" << std::endl;
    std::cout << "Returning to Main menu \n" << std::endl;
    return;
};

void MerkleMain::printMarketStats(){

    std::cout << "Displaying the Exchange stats" << std::endl;
    std::cout << "Returning to Main menu \n" << std::endl;
    return;
};

void MerkleMain::enterOffer(){
    std::cout << "Placing an ask" << std::endl;
    std::cout << "Returning to Main menu \n" << std::endl;
    return;
};

void MerkleMain::enterBid(){
    std::cout << "Placing an bid" << std::endl;
    std::cout << "Returning to Main menu \n" << std::endl;
    return;
};

void MerkleMain::printWallet(){
    std::cout << "Displaying your lack of money in your wallet...." << std::endl;
    std::cout << "Returning to Main menu \n" << std::endl;
    return;
};

void MerkleMain::gotoNextTimeframe(){
    std::cout << "Continue" << std::endl;
    std::cout << "Returning to Main menu \n" << std::endl;
    return;
};

int  MerkleMain::getUserOption(){
    
    int userOption;
    std::cout << "	Type in 1-6 to make your choice \n" << std::endl;
    std::cin >> userOption;
    
    if (std::cin.fail()) {
        std::cout << "	Only numbers please!\n" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return 0;
    }
    return userOption; 
};

void MerkleMain::processUserOption(int userOption){
    
    switch (userOption) {
        case 1: // Help selected

            printHelp(); 
            break;

        case 2:

            printMarketStats();
            break;

        case 3:

            enterOffer();
            break;

        case 4:

            enterBid();
            break;

        case 5:

            printWallet();
            break;

        case 6:

            gotoNextTimeframe();
            break;

        default:

            std::cout << "Please select an number between 1-6... \n" << std::endl;
            std::cout << "Returning to Main menu \n" << std::endl;
    }
};
