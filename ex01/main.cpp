#include "RPN.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Usage: " << av[0] << " <RPN expression>" << std::endl;
        return 1;
    }

    RPN rpn;
    std::string line(av[1]);

    try
    {
        rpn.EvaluateRPN(line);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}