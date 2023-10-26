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