#pragma once
#include <String> 


enum class OrderBookType { bid, ask, unknown, sale };

class OrderBookEntry
{
	public:
		OrderBookEntry( std::string _timestamp,
						std::string _product,
						OrderBookType _orderType,
						double _price,
						double _amount);

		static OrderBookType	stringToOrderBookType(std::string s);

		static bool compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2)
		{
			return e1.timestamp < e2.timestamp;
		}

		static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2)
		{
			return e1.price < e2.price;
		}

		static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2)
		{
			return e1.price > e2.price;
		}



		double					price;
		std::string				timestamp; 
		OrderBookType			orderType;
		double					amount;
		std::string				product;

};