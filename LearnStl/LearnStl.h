#ifndef LEARNCTL_H
#define LEARNCTL_H

#include <vector>
#include <iostream>
class Base
{
private:
    int m_val;
public:
    Base() : m_val(0) {
        std::cout << "default constructor." << std::endl;
    }

    Base(int x, int y) : m_val(x) {
        std::cout << "constructor." << std::endl;
    }

    Base(const Base &rsh) {
        std::cout << "copy." << std::endl;
        m_val = rsh.m_val;
    }
    ~ Base() {
        std::cout << "~Base." << std::endl;
    }
};



enum TestType {
    TEST_BEGIN = 0,
    TEST_VEC,
    TEST_END = 255
};
class LearnStl
{
private:
    void LearnVector();
public:
    LearnStl() =  default;
    ~LearnStl() = default;

    void Test(TestType type);
};

#endif