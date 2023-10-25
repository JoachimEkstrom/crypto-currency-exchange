#include <iostream>
#include <string>
#include <vector>
#include<ios> //used to get stream size
#include<limits> //used to get numeric limits

using namespace std;

enum class OrderBookType { bid, ask }; // Enum for the type.

class OrderBookEntry // this is the name of the class
{
	public: // parts of the class that can be seen from outside

		OrderBookEntry( double _price,
						std::string _timestamp,
						OrderBookType _type,
						double _amount,
						std::string _product)
		: price(_price), timestamp(_timestamp), type(_type), amount(_amount), product(_product)
		{}

		double			price;
		std::string		timestamp; 
		OrderBookType	type;
		double			amount;
		std::string		product;

};

// Functions to be added for calculations. 

double computeAveragePrice(std::vector<OrderBookEntry>& entries){
	double sum = 0;

	for (OrderBookEntry& e : entries)
	{
		sum = sum + e.price;
	}

	return double (sum / entries.size());
}

// double computeLowPrice(std::vector<OrderBookEntry>& entries){};
// double computeHighPrice(std::vector<OrderBookEntry>& entries){};
// double computePriceSpread(std::vector<OrderBookEntry>& entries){};





int main(int argc, char* argv[])
{
	std::cout << "	Welcome to the MerkleRex Crypto-exchange app!" << std::endl;
	int userOption;

	OrderBookEntry obe1{ 10000, "TIMESTAMP for obe1", OrderBookType::bid, 10000, "BTC" };
	OrderBookEntry obe2{ 30000, "2023-10-25", OrderBookType::ask, 500, "BTC/USD" };


	std::vector<OrderBookEntry> entries; // Creates the vector for Orderbook entries. 
	entries.push_back(obe1);
	entries.push_back(obe2);

	std::cout << computeAveragePrice(entries) << std::endl;




	while (1) {

		std::cout << "\n	Main Menu \n" << std::endl;

		std::cout << "	1: Print help" << std::endl;
		std::cout << "	2: Print exchange stats" << std::endl;
		std::cout << "	3: Place an ask" << std::endl;
		std::cout << "	4: Place an bid" << std::endl;
		std::cout << "	5: Print wallet" << std::endl;
		std::cout << "	6: Continue \n" << std::endl;


		std::cout << "	Type in 1-6 to make your choice \n" << std::endl;
		std::cin >> userOption;

		
		if (std::cin.fail()) {
			std::cout << "	Only numbers please!\n" << std::endl;
			std::cin.clear();
			std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		


		switch (userOption) {
			case 1: // Help selected

				std::cout << "This is the Help menu \n" << std::endl;
				std::cout << "Returning to Main menu \n" << std::endl;
				break;

			case 2:

				std::cout << "Displaying the Exchange stats \n" << std::endl;
				std::cout << "Returning to Main menu \n" << std::endl;
				break;

			case 3:

				std::cout << "Placing an ask \n" << std::endl;
				std::cout << "Returning to Main menu \n" << std::endl;
				break;

			case 4:

				std::cout << "Placing an bid \n" << std::endl;
				std::cout << "Returning to Main menu \n" << std::endl;
				break;

			case 5:

				std::cout << "Displaying your lack of money in your wallet.... \n" << std::endl;
				std::cout << "Returning to Main menu \n" << std::endl;
				break;

			case 6:

				std::cout << "Continue?? \n " << std::endl;
				std::cout << "Returning to Main menu \n" << std::endl;
				break;

			default:

				std::cout << "Please select an number between 1-6... \n" << std::endl;
				std::cout << "Returning to Main menu \n" << std::endl;
		}
	}
	return 0;
}
