#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <bits/stdc++.h>

//why the container map?
// - Key-Value Pairs: The std::map stores dates as keys (std::string) and exchange rates as values (float)
// - Automatic Sorting by Date: std::map automatically keeps keys (dates) in sorted order
//                              This allows for easy range queries, like finding the closest past date using lower_bound()
// - Unique Dates (No Duplicates): std::map ensures that each date appears only once.

//vectors and lists accept duplicates and are not sorted! so i couldn t use the lower_bound() function

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