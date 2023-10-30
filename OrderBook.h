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

        /** Returns the high price*/
        static double getHighPrice(std::vector<OrderBookEntry>& orders);
        /** Returns the low price*/
        static double getLowPrice(std::vector<OrderBookEntry>& orders);
        /** Takes the orders from this timefram and the orders from the prevoius timeframe and returns the change in precent since last timeframe for the price*/
        static double getPriceChange(std::vector<OrderBookEntry>& orders, std::vector<OrderBookEntry>& prevOrders);

        /** Returns the earliest time in the orderbook*/
        std::string getEarliestTime();
        /** Returns the next time in the orderbook, if there is no next timestamp it returns the first timestamp in orders.*/
        std::string getNextTime(std::string timestamp);
        /** Returns the previous time in the orderbook, if there is no previous timestamp it returns the last timestamp in orders.*/
        std::string getPreviousTime(std::string timestamp);

        void insertOrder(OrderBookEntry& order);

        std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);


    private:

        std::vector<OrderBookEntry> orders;

};
    