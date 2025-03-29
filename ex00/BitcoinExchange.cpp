#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    try
    {
        readCsvDataBase();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    _database = other._database;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    _database = other._database;
    return *this;
}

void BitcoinExchange::readCsvDataBase(void)
{
    std::string line;
    std::string word;
    std::vector<std::string> words;
    std::ifstream file("data.csv");

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open database file" << std::endl;
        exit(1);
    }

    std::getline(file, line); //skip the first line

    while (std::getline(file, line))  // Correct way to iterate
    {
        std::stringstream ss(line); // Convert the line to a stringstream
        words.clear(); // ensures words starts empty before processing a new line

        while (std::getline(ss, word, ','))
        {
            words.push_back(word);
        }
        if (words.size() < 2) continue; // Prevent accessing out of bounds
        _database[words[0]] = strtof(words[1].c_str(), NULL);
    }
    file.close();
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
    struct tm tm;
    
    if (!strptime(date.c_str(), "%Y-%m-%d", &tm))
        return false;

    int year = atoi(date.substr(0, 4).c_str());
    int month = atoi(date.substr(5, 2).c_str());
    int day = atoi(date.substr(8, 2).c_str());

    int maxDay;
    switch (month)
    {
        case 2:
            maxDay = 28;
            if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
                maxDay = 29;
            break;
        case 4: case 6: case 9: case 11:
            maxDay = 30;
            break;
        default:
            maxDay = 31;
            break;
    }
    return day <= maxDay;
}

void BitcoinExchange::checkForValue(std::string &line)
{
    float value;
    std::stringstream ss(line);
    std::string word;
    std::string date;
    std::vector<std::string> words;
    std::map<std::string, float>::iterator it;

    while (std::getline(ss, word, ' '))
    {
        if (word != "|") //skip the | separator between the date and the value
            words.push_back(word);
    }

    if (words.size() != 2) //check if i can access both before accessing
        throw BadDateException();

    if (words[1].find_first_not_of("-0123456789.") != std::string::npos) //check if the value is a number
        throw BadDateException();

    date = words[0];
    value = strtof(words[1].c_str(), NULL);

    if (!isValidDate(date))
        throw BadDateException();

    if (value < 0)
        throw NegativeNumberException();
    else if (value > 1000)
        throw NumberToLargeException();
        
    // Find the corresponding date in the database
    it = this->_database.find(date);
    if (it == this->_database.end())
    {
        it = this->_database.lower_bound(date); // Find the first date that is greater than the given date
        if (it == this->_database.begin())  // Check before decrementing
            throw NoDateToTrackException();
        it--; // Move to the closest previous date
    }

    // Print the result
    std::cout << date << " => " << value << " = " << it->second * value << std::endl; //it->second is the value of the exchange rate (bitcoin value) in the database
}

const char *BitcoinExchange::BadDateException::what() const throw()
{
    return "Error: bad input => ";
}

const char *BitcoinExchange::NumberToLargeException::what() const throw()
{
    return "Error: too large a number.";
}

const char *BitcoinExchange::NegativeNumberException::what() const throw()
{
    return "Error: not a positive number.";
}

const char *BitcoinExchange::NoDateToTrackException::what() const throw()
{
    return "Error: no date to check => ";
}

