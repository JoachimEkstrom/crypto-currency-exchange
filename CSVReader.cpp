#include "CSVReader.h"
#include <iostream>
#include <fstream>

CSVReader::CSVReader()
{

};

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFileName)
{
    std::vector<OrderBookEntry> entries;

    std::ifstream csvFile{csvFileName};                                                             // Open our file to read
    std::string line;

    if ( csvFile.is_open())                                                                         // If the file is open then we can start reading line after line. 
    {
        while(std::getline(csvFile, line))
        {
            
            try{
                OrderBookEntry obe = stringsToOBE(tokenise(line, ','));                             // Send the read line to tokenise function and then immidiatly send that result to convert it to a OBE. 
                entries.push_back(obe);                                                             // push that obe to our entries. 
            }
            catch (std::exception& e)
            {
                std::cout << "CSVReader::readCSV --- this line causes a execption" << std::endl;    // on exception print the line causing it for debugging. Then continue to read next line. 
                if (line.length() == 0)
                {
                    std::cout << "The read line is an empty line" << std::endl;                     // If the line is empty print a message 
                }
                else
                {
                    std::cout << line << std::endl;                                                 // Otherwise print the faulty line. 
                }    
            }
        }
    }

    std::cout << "\nCSVReader::readCSV read " << entries.size() << " entries.\n" << std::endl;      // print out how many entries we have read in. 
    return entries;
    
};


std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator)
{
    std::vector<std::string> tokens;
    std::string token;
    signed int start, end;

    start = csvLine.find_first_not_of(separator, 0);                                                // Look for the first char not beeing a separator and return the place. 
                            
    do{                         
        end = csvLine.find_first_of(separator, start);                                              // From the start value look for next separator and save the place. If no separator is found this function returns string::npos. Will cause the while loop to end.  
        if (start == csvLine.length() || start == end) break;                                       // If the string is of zero length, leave this line directly. 
                            
        if (end >= 0)                                                                               // If end is more than 0, we found a separator.
        {                           
            token = csvLine.substr(start, end-start);                                               // We then cut the a sub string out from start to end. Not that we care about where the start is. 
                                                                                                    // Start could be in the middle of a string if we have had a token before it thus we subrstract start from the end value. 
        }                                                                                           // Then we store this substring as a token. 
        else                            
        {                           
            token = csvLine.substr(start, csvLine.length() - start);                                // If we did not find another separator we probably found the end of the string. The substring is then from start to final position of the string - start. 
        }                           
        tokens.push_back(token);                                                                    // Add this token to our vector of tokens. 
                            
        start = end + 1;                                                                            // Set start to the end value + 1. End is the separator, thus start will be the next char after that. 
    
    } while( end > 0);                                                  

    return tokens;

};

OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens)
{
    double price, amount; 

    if (tokens.size() != 5)                                                                                             // If we don´t have 5 tokens we cant continue. 
    {
        std::cout << "Need exactly 5 tokens for processing. Incomming tokens size: " << tokens.size() << std::endl;
        throw std::exception{};                                                                                         // Throw an error for the calling fuction.  
    }
    
    try {                                                                                                               // If we have the correct amount of tokens. 
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    }
    catch ( const std::exception& e){
        std::cout << "Could not convert string to double " << tokens[3] << std::endl;
        std::cout << "Could not convert string to double " << tokens[4] << std::endl;
        throw;                                                                                                          // Throw an error for the calling fuction. 
    }


    OrderBookEntry obe( tokens[0],
                        tokens[1],
                        OrderBookEntry::stringToOrderBookType(tokens[2]),
                        price,
                        amount); 

    return obe; 

};
