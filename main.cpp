#include <iostream>
#include <string>
#include <vector>

#include "OrderBookEntry.h"
#include "MerkleMain.h"

using namespace std;

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





int main(int argc, char* argv[])
{
	
	MerkleMain app{};

	std::cout << "\n	Welcome to the MerkleRex Crypto-exchange app!" << std::endl;
	app.init();

	OrderBookEntry obe1{ "2020/03/17 17:01:24.884492", "ETH/BTC", OrderBookType::bid, 10000, 0.005 };
	OrderBookEntry obe2{ "2020/03/17 17:01:30.099017", "DOGE/BTC", OrderBookType::ask, 30000, 0.0000003 };
	OrderBookEntry obe3{ "2023/03/17 17:01:30.099017", "DOGE/BTC", OrderBookType::ask, 5000, 0.00033 };

	std::vector<OrderBookEntry> entries; // Creates the vector for Orderbook entries. 
	entries.push_back(obe1);
	entries.push_back(obe2);
	entries.push_back(obe3);

	std::cout << "Average price is: " << computeAveragePrice(entries) << std::endl;
	std::cout << "Lowest price is: " << computeLowPrice(entries) << std::endl;
	std::cout << "Highest price is: " << computeHighPrice(entries) << std::endl;
	std::cout << "Price spread is: " << computePriceSpread(entries) << std::endl;



	return 0;
}
