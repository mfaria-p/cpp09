#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    BitcoinExchange bitcoinExchange;

    std::ifstream file(av[1]);
    std::string line;

    if (!file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    std::getline(file, line); // Skip the first line (header)
    while (std::getline(file, line))
    {
        // Check if the line is empty or if it contains only whitespace
        std::string trimmedLine = line;
        trimmedLine.erase(0, trimmedLine.find_first_not_of(" \t\n\r\f\v")); // Trim leading whitespace
        trimmedLine.erase(trimmedLine.find_last_not_of(" \t\n\r\f\v") + 1); // Trim trailing whitespace
        if (trimmedLine.empty())
            continue; // Skip empty lines
        if (line.empty())
            continue; // Skip empty lines
        try
        {
            bitcoinExchange.checkForValue(line);
        }
        catch(const BitcoinExchange::BadDateException &e)
        {
            std::cerr << e.what() << line << std::endl;
        }
        catch(const std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    file.close();
    return 0;
}
