#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }

    BitcoinExchange btc;
    if (!btc.makemap("data.csv"))
        return 1;

    std::ifstream input(av[1]);
    if (!input.is_open())
    {
        std::cout << "Error: could not open file." << std::endl;
        return 1;
    }
    try
    {
        btc.processInput(input);
    }
    catch(std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
