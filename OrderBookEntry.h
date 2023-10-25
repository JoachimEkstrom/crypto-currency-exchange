#include <String> 


enum class OrderBookType { bid, ask };

class OrderBookEntry
{
	public:
		OrderBookEntry( std::string _timestamp,
						std::string _product,
						OrderBookType _type,
						double _price,
						double _amount);

		double			price;
		std::string		timestamp; 
		OrderBookType	type;
		double			amount;
		std::string		product;

};