#pragma once
#include <String> 


enum class OrderBookType { bid, ask, unknown };

class OrderBookEntry
{
	public:
		OrderBookEntry( std::string _timestamp,
						std::string _product,
						OrderBookType _orderType,
						double _price,
						double _amount);

		static OrderBookType	stringToOrderBookType(std::string s);
		double					price;
		std::string				timestamp; 
		OrderBookType			orderType;
		double					amount;
		std::string				product;

};