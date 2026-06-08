#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>

class PmergeMe
{
    private:
        std::vector<int> vec;
        std::deque<int>  deq;


    public:
        void sortVector();
        void sortDeque();
        void fordJohnsonVector(std::vector<int>& v);
        void fordJohnsonDeque(std::deque<int>& d);
        double getTime() const;
        PmergeMe();
        PmergeMe(char **av);
        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();

        void run();
};

#endif
