#ifndef LEARNCTL_H
#define LEARNCTL_H

#include <vector>
#include <iostream>

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