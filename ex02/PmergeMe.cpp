#include "PmergeMe.hpp"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <sys/time.h>

static int parsePositive(const char *s)
{
    long result = 0;
    int i = 0;

    if (!s || s[0] == '\0')
        throw std::runtime_error("empty input av[i]");

    while (s[i])
    {
        if (s[i] < '0' || s[i] > '9')
            throw std::runtime_error("non numeric input av[i]");

        result = result * 10 + (s[i] - '0');

        if (result > 2147483647)
            throw std::runtime_error("int out of range");

        i++;
    }

    return (int)result;
}

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(char **av)
{
    for (int i = 0; av[i]; ++i)
    {
        int value;
        value = parsePositive(av[i]);
        vec.push_back(value);
        deq.push_back(value);
    }
}

PmergeMe::PmergeMe(const PmergeMe& other)
{
    *this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other)
    {
        vec = other.vec;
        deq = other.deq;
    }
    return *this;
}
PmergeMe::~PmergeMe() {}


double PmergeMe::getTime() const
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1e6 + tv.tv_usec;
}

static std::vector<size_t> buildJacobsthal(size_t n)
{
    std::vector<size_t> j;

    j.push_back(0);
    j.push_back(1);

    while (j.back() < n)
        j.push_back(j[j.size() - 1] + 2 * j[j.size() - 2]);

    return j;
}

static std::vector<size_t> buildInsertionOrder(size_t n)
{
    std::vector<size_t> order;
    if (n == 0)
        return order;

    order.push_back(0);

    if (n == 1)
        return order;

    std::vector<size_t> jacob = buildJacobsthal(n - 1);
    size_t prevIndex = 0;
    
    for (size_t i = 2; i < jacob.size(); ++i)
    {
        size_t currIncdex = jacob[i];
        if (currIncdex > n - 1)
            currIncdex = n - 1;

        for (size_t j = currIncdex; j > prevIndex; --j)
            order.push_back(j);

        prevIndex = currIncdex;
    }

    return order;
}


void PmergeMe::fordJohnsonVector(std::vector<int>& v)
{
    if (v.size() <= 1)
        return;

    std::vector<int> large;
    std::vector<int> small;

    for (size_t i = 0; i + 1 < v.size(); i += 2)
    {
        if (v[i] < v[i + 1])
        {
            small.push_back(v[i]);
            large.push_back(v[i + 1]);
        }
        else
        {
            small.push_back(v[i + 1]);
            large.push_back(v[i]);
        }
    }

    if (v.size() % 2)
        large.push_back(v.back());

    fordJohnsonVector(large);

    if (!small.empty())
    {
        int value = small[0];
        size_t left = 0;
        size_t right = large.size();

        while (left < right)
        {
            size_t mid = (left + right) / 2;
            if (large[mid] < value)
                left = mid + 1;
            else
                right = mid;
        }
        large.insert(large.begin() + left, value);
    }

    if (small.size() > 1)
    {
        std::vector<size_t> order = buildInsertionOrder(small.size() - 1);

        for (size_t i = 0; i < order.size(); ++i)
        {
            int value = small[order[i] + 1];

            size_t left = 0, right = large.size();
            while (left < right)
            {
                size_t mid = (left + right) / 2;
                if (large[mid] < value)
                    left = mid + 1;
                else
                    right = mid;
            }
            large.insert(large.begin() + left, value);
        }
    }

    v = large;
}




void PmergeMe::fordJohnsonDeque(std::deque<int>& d)
{
    if (d.size() <= 1)
        return;

    std::deque<int> large;
    std::deque<int> small;

    for (size_t i = 0; i + 1 < d.size(); i += 2)
    {
        if (d[i] < d[i + 1])
        {
            small.push_back(d[i]);
            large.push_back(d[i + 1]);
        }
        else
        {
            small.push_back(d[i + 1]);
            large.push_back(d[i]);
        }
    }

    if (d.size() % 2)
        large.push_back(d.back());

    fordJohnsonDeque(large);

    std::vector<size_t> order = buildInsertionOrder(small.size());

    for (size_t i = 0; i < order.size(); ++i)
    {
        int value = small[order[i]];

        size_t left = 0;
        size_t right = large.size();

        while (left < right)
        {
            size_t mid = (left + right) / 2;
            if (large[mid] < value)
                left = mid + 1;
            else
                right = mid;
        }

        large.insert(large.begin() + left, value);
    }

    d = large;
}


void PmergeMe::run()
{
    std::cout << "Before: ";
    for (size_t i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    double startVec = getTime();
    fordJohnsonVector(vec);
    double endVec = getTime();

    double startDeq = getTime();
    fordJohnsonDeque(deq);
    double endDeq = getTime();

    std::cout << "After:  ";
    for (size_t i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    std::cout << "Time to process a range of "
              << vec.size()
              << " elements with std::vector : "
              << (endVec - startVec)
              << " us" << std::endl;

    std::cout << "Time to process a range of "
              << deq.size()
              << " elements with std::deque  : "
              << (endDeq - startDeq)
              << " us" << std::endl;
}
