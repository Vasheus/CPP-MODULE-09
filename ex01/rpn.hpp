#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>
#include <iostream>
#include <cstdlib>

class RPN
    {
        private:
            std::stack<int> sstack;
        public:
            RPN();
            RPN(const RPN &other);
            RPN &operator=(const RPN &other);
            ~RPN();

            int evaluate(const std::string &expression);
            bool isOperator(char c) const;
            bool isDigit(char c) const;
    };

#endif
