#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <bits/stdc++.h>

class BitcoinExchange
{
private:
    std::map<std::string, float> _database;

    public:
    BitcoinExchange();
    ~BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);

    typedef std::map<std::string, float>::iterator iterator;

    void readCsvDataBase(void);
    void checkForValue(std::string &line);

    class BadDateException : public std::exception //bad input for the date. Example: 2020-13-01
    {
    public:
        const char *what() const throw();
    };

    class NumberToLargeException : public std::exception //The value of a certain amount of bitcoin on a certain date is too large
    {
        const char *what() const throw();
    };

    class NegativeNumberException : public std::exception //The value of a certain amount of bitcoin on a certain date is negative
    {
        const char *what() const throw();
    };

    class NoDateToTrackException : public std::exception //No dates in the database
    {
    public:
        const char *what() const throw();
    };
};

#endif // BITCOINEXCHANGE_HPP