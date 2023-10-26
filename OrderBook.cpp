#include "OrderBook.h"
#include "CSVReader.h"



/** Constructor for reading a csvfile*/
OrderBook::OrderBook(std::string filename)
{
    orders = CSVReader::readCSV(filename);
}
/** returning all known products in a dataset*/
std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products;

    return products;

}
/** returns all orders by the selected filters*/
std::vector<OrderBookEntry> OrderBook::getOrders(
                                OrderBookType type,
                                std::string   product,
                                std::string   timestamp)
{
    std::vector<OrderBookEntry> orders;
    return orders;
}
