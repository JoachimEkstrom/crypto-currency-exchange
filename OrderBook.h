#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <vector>
#include <string>


class OrderBook
{
    public: 
       /** Constructor for reading a csvfile*/
        OrderBook(std::string filename);
        /** returning all known products in a dataset*/
        std::vector<std::string>getKnownProducts();
        /** returns all orders by the selected filters*/
        std::vector<OrderBookEntry>getOrders(
                                        OrderBookType type,
                                        std::string   product,
                                        std::string   timestamp);

    private:

        std::vector<OrderBookEntry> orders;
        
};
    