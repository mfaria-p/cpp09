#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>   // For input/output operations (std::cout, std::cerr)
#include <sstream>   // For string stream operations (std::stringstream)
#include <stack>      // For stack operations (std::stack)
#include <algorithm> // For algorithm functions (std::all_of)
#include <string>     // For string manipulation (std::string)
#include <exception>  // For custom exceptions (std::exception)

//stacks are used for LIFOs (Last In First Out) and queues are used for FIFO (First In First Out)

// stacks (LIFO)- Perfect for handling expressions where order matters
// Safer Access – Prevents unintended modifications since only the top element is accessible

//vectors give random access, whcih i dont want and additional opperands

class RPN
{
    private:
        std::stack<double> _stack;
    public:
        RPN();
        ~RPN();
        RPN(const RPN &other);
        RPN &operator=(const RPN &other);

        void EvaluateRPN(std::string &line);
        void doOperation(char op);
        void checkForEmptyStack(void);
        bool ft_isdigit(std::string str);

        class BadInputException : public std::exception
        {
            const char *what() const throw();
        };
};


#endif
