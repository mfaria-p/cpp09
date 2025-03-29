#include "RPN.hpp"

RPN::RPN() {}   

RPN::~RPN() {}

RPN::RPN(const RPN &other) : _stack(other._stack) {}

RPN &RPN::operator=(const RPN &other)
{
    if (this != &other)
    {
        _stack = other._stack;
    }
    return *this;
}

void RPN::EvaluateRPN(std::string &line) {
    std::stringstream ss(line);
    std::string word;

    while (std::getline(ss, word, ' ')) 
    {
        if (word.empty()) continue;
        if ((word == "+" || word == "-" || word == "*" || word == "/") && word.size() == 1) 
        {
            if (_stack.size() < 2)
            {
                throw BadInputException();
            }
            doOperation(word[0]);
        } 
        else if (ft_isdigit(word)) 
        {
            //int num = atoi(word.c_str());
            double num = strtol(word.c_str(), NULL, 10);
            if (num >= 0 && num <= 9)
                _stack.push(num);
            else
            {
                throw BadInputException();
            }
        } 
        else 
        {
            throw BadInputException();
        }
    }

    if (_stack.size() != 1)
    {
        throw BadInputException();
    }

    std::cout << _stack.top() << std::endl;
}

void RPN::doOperation(char op)
{
    checkForEmptyStack();
    double b = _stack.top();
    _stack.pop();
    checkForEmptyStack();
    double a = _stack.top();
    _stack.pop();

    switch (op)
    {
        case '+':
            _stack.push(a + b);
            break;
        case '-':
            _stack.push(a - b);
            break;
        case '*':
            _stack.push(a * b);
            break;
        case '/':
            if (b == 0)
                throw BadInputException(); // Division by zero
            _stack.push(a / b);
            break;
        default:
        {
            throw BadInputException(); // Invalid operator
        }

    }
}

void RPN::checkForEmptyStack(void)
{
    if (_stack.empty())
        throw BadInputException();
}

const char *RPN::BadInputException::what() const throw()
{
    return "Error";
}

bool    RPN::ft_isdigit(std::string str)
{
    std::string:: iterator itr;
    for (itr = str.begin(); itr < str.end(); itr++) {
        if (!isdigit(*itr))
            return (false);
    }
    return (true);
}
