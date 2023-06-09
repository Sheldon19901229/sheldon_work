#include <iostream>
#include <memory>
#include "LearnStl.h"


using namespace std;

int main() {
    unique_ptr<LearnStl> obj = make_unique<LearnStl>();
    obj->Test(TEST_VEC);
    return 0;
}