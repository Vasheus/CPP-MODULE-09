#include "rpn.hpp"

RPN::RPN() {}
RPN::RPN(const RPN &other) : sstack(other.sstack) {}
RPN &RPN::operator=(const RPN &other)
{
    if (this != &other)
        sstack = other.sstack;
    return *this;
}
RPN::~RPN() {}

bool RPN::isDigit(char c) const
{
    return (c >= '0' && c <= '9');
}

bool RPN::isOperator(char c) const
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int RPN::evaluate(const std::string &str)
{
    while (!sstack.empty())
        sstack.pop();

    for (std::size_t i = 0; i < str.length(); ++i)
    {
        char c = str[i];

        if (c == ' ')
            continue;

        if (isDigit(c))
        {
            sstack.push(c - '0');
        }
        else if (isOperator(c))
        {
            if (sstack.size() < 2)
                throw std::runtime_error("not enough numbers");

            int b = sstack.top(); sstack.pop();
            int a = sstack.top(); sstack.pop();

            long long res = 0;

            if (c == '+')
                res = static_cast<long long>(a) + b;

            else if (c == '-')
                res = static_cast<long long>(a) - b;

            else if (c == '*')
                res = static_cast<long long>(a) * b;

            else if (c == '/')
            {
                if (b == 0)
                    throw std::runtime_error("division by zero");
                res = a / b;
            }

            if (res < std::numeric_limits<int>::min() ||
                res > std::numeric_limits<int>::max())
                throw std::out_of_range("overflow");

            sstack.push(static_cast<int>(res));
        }
        else
        {
            throw std::runtime_error("invalid character");
        }
    }

    if (sstack.size() != 1)
        throw std::runtime_error("invalid RPN format");

    return sstack.top();
}

