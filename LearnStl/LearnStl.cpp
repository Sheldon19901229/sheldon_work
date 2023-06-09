#include "LearnStl.h"
#include <iostream>


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
    std::vector<Base> vec1;
    std::vector<Base> vec2;
    //vec1.push_back({2,3});
    vec2.emplace_back(2,3);
    

}


