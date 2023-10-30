#include "OrderBook.h"
#include "CSVReader.h"
#include <map>
#include <iostream>
#include <algorithm>    // std::sort

/** Constructor for reading a csvfile*/
OrderBook::OrderBook(std::string filename)
{
    orders = CSVReader::readCSV(filename);                  // Reads a csvfile and adds it to the orders. 
}
/** returning all known products in a dataset*/
std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products;
    std::map<std::string, bool> prodMap;                    // init of a Map

    for (OrderBookEntry& e : orders)                        
    {
        prodMap[e.product] = true;                          // Will add a key value  pair to the map. Each product will only be added once.  
    }

    for (auto const& e :prodMap)
    {
        products.push_back(e.first);                        // The map has a first value, this is the key. The second would be the value. 
    }

    return products;

}
/** returns all orders by the selected filters*/
std::vector<OrderBookEntry> OrderBook::getOrders(
                                OrderBookType type,
                                std::string   product,
                                std::string   timestamp)
{
    std::vector<OrderBookEntry> orders_sub;

    for(OrderBookEntry& e : orders)
    {
        if (e.orderType == type &&
            e.product == product &&
            e.timestamp == timestamp)
            {
                orders_sub.push_back(e);
            }

    }

    return orders_sub;
}


double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders)
{
    double max = orders[0].price;
    for ( OrderBookEntry& e : orders)
    {
        if(e.price > max )max = e.price;
    }
    return max;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders)
{
    double min = orders[0].price;
    for ( OrderBookEntry& e : orders)
    {
        if(e.price < min )min = e.price;
    }
    return min;
}

std::string OrderBook::getEarliestTime()
{
    return orders[0].timestamp;
}

std::string  OrderBook::getNextTime(std::string timestamp)
{
    std::string next_timestamp;
    for (OrderBookEntry& e: orders)
    {
        if (e.timestamp > timestamp)
        {
            next_timestamp = e.timestamp;
            break;
        }
    }
    if ( next_timestamp == "")
    {
        next_timestamp = orders[0].timestamp; 
    }

    return next_timestamp;
}

std::string  OrderBook::getPreviousTime(std::string timestamp)                      // Testing to loop over the vector in reverse direction
{
    std::string previous_timestamp;
    //for (OrderBookEntry& e: orders)
    for(int i = orders.size()-1; i > 0; i--)                                        // Looping from the last element in the vector to the first one...
    {
        if (orders[i].timestamp < timestamp)                                        // If a timestamp if found to be of earlier date than the current one that date is saved and the loop brakes. 
        {
            previous_timestamp = orders[i].timestamp;
            break;
        }
    }
    if ( previous_timestamp == "")
    {
        previous_timestamp = orders[0].timestamp;                                   // If no timestamp is found use the first one in the dataset.  
    }

    return previous_timestamp;
}


double OrderBook::getPriceChange(std::vector<OrderBookEntry>& orders, std::vector<OrderBookEntry>& previousOrders) 
{
    double priceChange, currentMaxPrice, previousMaxPrice;

    currentMaxPrice  = getHighPrice(orders);                                                // I am using the high prices to make the calculations. Getting the values from the fuctions we already have availible to us. 
    previousMaxPrice = getHighPrice(previousOrders);


    priceChange = ((currentMaxPrice - previousMaxPrice)/abs(previousMaxPrice))*100;         // Calculation the precent change since last timeframe. 

    return priceChange;
}

void OrderBook::insertOrder(OrderBookEntry& order)
{
    orders.push_back(order); 
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}


std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp)
{
    // Get the asks and bids. 
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp); 
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp); 

    // completed sales
    std::vector<OrderBookEntry> sales;

    // sort all asks and bids on price before starting
    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);

    // Main matching engine
    for (OrderBookEntry& ask : asks)
    {
        for (OrderBookEntry& bid : bids)
        {
            if (bid.price >= ask.price)
            {
                OrderBookEntry sale{timestamp, product, OrderBookType::sale, ask.price, 0};

                // start comparing the bids and asks

                // If the bid amount and the ask amount is the same. 
                // in this case the the bid and ask will clear out. 
                if ( bid.amount == ask.amount)
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = 0;
                    break;
                }

                // If the bid amount is greater than the ask. 
                // in this case the ask will be consumed and the bid will still exist to some extent. The bid will go to the next ask and try match with that.
                // When breaking, we will exit this bid loop, and start with next ask in the outer loop, we will then hit this same bid again for processing.  
                if ( bid.amount > ask.amount)
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = bid.amount - ask.amount;
                    break;
                    
                }
                // If the bid amount is less than the ask amount. 
                // In this case the bid will be consumed and the ask will still remain. Instead of breaking we will do a continue with the next bid.
                if ( bid.amount < ask.amount)
                {
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    ask.amount = ask.amount - bid.amount;

                    bid.amount = 0;

                    continue;


                }
            }
        }
    }

    return sales;

}