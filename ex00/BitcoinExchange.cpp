#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    this->dataB = other.dataB;
}
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
        this->dataB = other.dataB;
    return *this;
}
BitcoinExchange::~BitcoinExchange() {}


const std::map<std::string, float>& BitcoinExchange::getMap() const
{
    return dataB;
}

std::string BitcoinExchange::trim(const std::string &str) const
{
    size_t start = 0;
    size_t end = str.find_last_not_of(" \t");

    if (start == std::string::npos)
        return "";
    return str.substr(start, end - start + 1);
}

bool BitcoinExchange::isLeapYear(int year) const
{
    return ( (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) );
}

int BitcoinExchange::daysInMonth(int year, int month) const
{
    static const int days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if (month == 2)
        return isLeapYear(year) ? 29 : 28;

    return days[month - 1];
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    int y;
    int m;
    int d;

    y = std::atoi(date.substr(0, 4).c_str());
    m = std::atoi(date.substr(5, 2).c_str());
    d = std::atoi(date.substr(8, 2).c_str());

    if (y < 2009) return false;
    if (m < 1 || m > 12) return false;
    if (d < 1 || d > daysInMonth(y, m)) return false;

    return true;
}


bool BitcoinExchange::isValidValue(const std::string &value) const
{
    if (value.empty())
        return false;

    bool dot = false;

    for (size_t i = 0; i < value.length(); i++)
    {
        if (value[i] == '.')
        {
            if (dot)
            return false;
            dot = true;
        }
        else if (!isdigit(value[i]))
            return false;
    }

    float f = atof(value.c_str());
    return (f >= 0 && f <= 1000);
}

float BitcoinExchange::convert(const std::string &value) const
{
    return static_cast<float>(atof(value.c_str()));
}

bool BitcoinExchange::makemap(const std::string &filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return false;
    }

    std::string line;
    getline(file, line);

    while (getline(file, line))
    {
        size_t fas = line.find(',');

        std::string date = line.substr(0, fas);
        std::string price = line.substr(fas + 1);



        dataB[date] = convert(price);
    }
    return true;
}

float BitcoinExchange::daterate(const std::string &date) const
{
    std::map<std::string, float>::const_iterator it = dataB.lower_bound(date);

    if (it != dataB.end() && it->first == date)
        return it->second;

    if (it == dataB.begin())
        throw std::runtime_error("Error: no earlier date available.");

    --it;
    return it->second;
}

void BitcoinExchange::processInput(std::ifstream &inputFile)
{
    std::string line;

    getline(inputFile, line);
    if (line != "date | value")
        throw std::runtime_error("Error: invalid header");
    while (getline(inputFile, line))
    {
        if (line.empty())
            continue;

        size_t bar = line.find(" | ");
        if (bar == std::string::npos || line[0] == ' ' || line[line.size() - 1] == ' ' || line[0] == '\t' || line[line.size() - 1] == '\t')
        {
            std::cout << "Error: bad input => " << line << std::endl;
            continue;
        }

        std::string date  = trim(line.substr(0, bar));
        std::string value = trim(line.substr(bar + 3));

        if (!isValidDate(date))
        {
            std::cout << "Error: invalid date => " << date << std::endl;
            continue;
        }

        if (!isValidValue(value))
        {
            float f = atof(value.c_str());
            if (value.find('-') != std::string::npos)
                std::cout << "Error: not a positive number." << std::endl;
            else if (f > 1000)
                std::cout << "Error: too large a number." << std::endl;
            else
                std::cout << "Error: invalid value => " << value << std::endl;
            continue;
        }

        float fvalue = convert(value);

        try 
        {
            float rate = daterate(date);
            std::cout << date << " => " << fvalue << " = " << rate * fvalue << std::endl;
        }
        catch (std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}
