#include "LearnStl.h"
#include <iostream>
#include <algorithm>


void LearnStl::Test(TestType type)
{
    if (type < TEST_BEGIN || type > TEST_END) {
        std::cout << "Test type err:"  << type << std::endl;
        return;
    }

    switch (type)
    {
    case TEST_VEC: {
        std::cout << "Vector test begin" << std::endl;
        LearnVector();
        std::cout << "Vector test end" << std::endl;
        break;
    }
    default:
        break;
    }

}

void LearnStl::LearnVector()
{
   
    //Base base(3,2);
    std::vector<int> vec1 = {
        1,5,4,2,5,9,7,8,9,3
    };
    auto printVec = [&] () {
        for (auto it : vec1) {
            std::cout << it << "," << std::endl;
        }
    };

    std::sort(vec1.begin(),vec1.end(), [&](int a, int b) { return a < b ;});
    printVec();
}