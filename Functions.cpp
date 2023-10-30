#include <iostream>
#include <string>
#include <vector>

#include "OrderBookEntry.h"
#include "MerkleMain.h"
#include "CSVReader.h"

double computeAveragePrice(std::vector<OrderBookEntry>& entries){
	double sum = 0;

	for (OrderBookEntry& e : entries)
	{
		sum = sum + e.price;
	}

	return double (sum / entries.size());
}

double computeLowPrice(std::vector<OrderBookEntry>& entries){
	double lowPrice = 0;

	for (OrderBookEntry& e : entries)
	{
		if (lowPrice == 0 || lowPrice > e.price){
			lowPrice = e.price;
		}

	}
	return lowPrice;

};
double computeHighPrice(std::vector<OrderBookEntry>& entries){
	double highPrice = 0;

	for (OrderBookEntry& e : entries)
	{
		if (highPrice < e.price){
			highPrice = e.price;
		}

	}
	return highPrice;

};
double computePriceSpread(std::vector<OrderBookEntry>& entries){
	double highPrice = computeHighPrice(entries); 
	double lowPrice = computeLowPrice(entries);

	return double (highPrice - lowPrice);
};




    // std::cout << "Average price is: " << computeAveragePrice(orders) << std::endl;
	// std::cout << "Lowest price is: " << computeLowPrice(orders) << std::endl;
	// std::cout << "Highest price is: " << computeHighPrice(orders) << std::endl;
	// std::cout << "Price spread is: " << computePriceSpread(orders) << std::endl;







	//         wallet.insertCurrency("BTC", 10);
    //     wallet.insertCurrency("BTC", 30);
    //     wallet.insertCurrency("USD", 100);
        
    // try{
    //     wallet.insertCurrency("ETC", -50);
    // }
    // catch(const std::exception& e){
    //     std::cout << e.what() << std::endl;

    // }

    // std::cout << wallet.toString() << std::endl; 



    // wallet.removeCurrency("USD", 50);
    // wallet.removeCurrency("BTC", 45);

    // std::cout << wallet.toString() << std::endl; 

    // try{
    //     wallet.removeCurrency("ETC", -50);
    // }
    // catch(const std::exception& e){
    //     std::cout << e.what() << std::endl;

    // }

    // std::cout << wallet.toString() << std::endl; 

    // std::cout << "MerkleMain::init: The wallet contains 10 BTC or more? " << wallet.containsCurrency("BTC", 10) << std::endl; 
    // std::cout << "MerkleMain::init: The wallet contains 10 USD or more? " << wallet.containsCurrency("USD", 10) << std::endl; 
    // std::cout << "MerkleMain::init: The wallet contains 60 USD or more? " << wallet.containsCurrency("USD", 60) << std::endl; 
     