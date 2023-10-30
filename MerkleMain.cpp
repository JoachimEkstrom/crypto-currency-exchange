#include "MerkleMain.h"   
#include <iostream>
#include <string>
#include <ios> 
#include <limits>
#include <vector>
#include "CSVReader.h"

MerkleMain::MerkleMain(){}; 
void MerkleMain::init()
{
    int input;
    currentTime = orderBook.getEarliestTime();
    previousTime = orderBook.getPreviousTime(currentTime);

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
    std::cout << "	6: Continue" << std::endl;
    std::cout << "  \tThe current time is: " << currentTime << std::endl;
    std::cout << "  \tThe previous time was: " << previousTime << std::endl;
    
    return;
};


void MerkleMain::printHelp(){
    std::cout << "This is the Help menu" << std::endl;
    std::cout << "Returning to Main menu \n" << std::endl;
    return;
};

void MerkleMain::printMarketStats(){

    for ( std::string const p : orderBook.getKnownProducts())
    {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);
        std::vector<OrderBookEntry> prevEntries = orderBook.getOrders(OrderBookType::ask, p, previousTime);

        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max Ask seen: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min Ask seen: " << OrderBook::getLowPrice(entries) << std::endl;
        std::cout << "Price change since last timeframe: " << OrderBook::getPriceChange(entries, prevEntries) << "%\n" << std::endl;
    }

    // std::cout << "Displaying the Exchange stats" << std::endl;

    // std::cout << "There are currently " << orders.size() << " entries in the OrderBook" << std::endl;
    // unsigned int bids = 0;
    // unsigned int asks = 0;

    // for (OrderBookEntry& e : orders)
    // {
    //     if (e.type == OrderBookType::ask)
    //     {
    //         asks++;
    //     }
    //     if (e.type == OrderBookType::bid)
    //     {
    //         bids++;
    //     }
    // }
    // std::cout << "The numbers of asks are: " << asks << " and the numbers of bids are: " << bids << std::endl;

    // std::cout << "Returning to Main menu \n" << std::endl;
    return;
};

void MerkleMain::enterAsk(){
    std::cout << "Place an ask - enter the amount: product, price, amount e.g ETH/BTC, 10, 50" << std::endl;
    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');    // Clear the input buffer before we can get the input value. 
    std::getline(std::cin, input); 

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkleMain::enterAsk: Bad input, need exactly 3 inputs" << std::endl;

    }
    else
    {
        try{
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::ask); 

            orderBook.insertOrder(obe);
        } catch( const std::exception& e)
        {
            std::cout << "MerkleMain::enterAsk: Bad input" << std::endl;
        }   
    }



    std::cout << "You typed: " << input << std::endl;

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
    std::cout << "Going to the next timeframe" << std::endl;
    
    std::vector<OrderBookEntry> sales =  orderBook.matchAsksToBids("ETH/BTC", currentTime);
    std::cout << "Sales: " << sales.size() << std::endl; 

    for (OrderBookEntry& sale : sales)
    {
        std::cout << "Sale price: " << sale.amount << " amount: " << sale.amount << std::endl;
    }

    currentTime = orderBook.getNextTime(currentTime);
    previousTime = orderBook.getPreviousTime(currentTime);          // Keep track of the last timefram to calculate the price change. 
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

            enterAsk();
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

            std::cout << "\nPlease select an number between 1-6... \n" << std::endl;
            std::cout << "Returning to Main menu \n" << std::endl;
    }
};
