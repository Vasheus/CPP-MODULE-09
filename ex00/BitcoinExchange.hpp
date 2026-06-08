#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <map>

class BitcoinExchange
{
    private:
        std::map<std::string, float> dataB;

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();

        const std::map<std::string, float>& getMap() const;
        bool makemap(const std::string &filename);

        void processInput(std::ifstream &inputFile);

        bool isValidDate(const std::string &date) const;
        bool isValidValue(const std::string &value) const;
        float convert(const std::string &value) const;

        float daterate(const std::string &date) const;
        std::string trim(const std::string &str) const;
        bool isLeapYear(int year) const;
        int daysInMonth(int year, int month) const;
};

#endif
