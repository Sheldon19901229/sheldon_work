#include <iostream>
#include <memory>
#include "LearnStl.h"
#include "Sort.h"
#include <string>
#include "Log.h"
#include "TimeStamp.h"
#include "Solution.h"

using namespace std;

int main() {
    Solution obj;
    cout << obj.GetPressedString("aaaccccccccddcccccc") << endl;


    std::cout << "ns:" << GetTimeCount(TIME_STAMP_NS) << endl;
    std::cout << "us:" << GetTimeCount(TIME_STAMP_US) << endl;
    std::cout << "ms:"<< GetTimeCount(TIME_STAMP_MS) << endl;
    std::cout << "s:" << GetTimeCount(TIME_STAMP_S) << endl;
    std::cout << "min:"<< GetTimeCount(TIME_STAMP_MIN) << endl;
    std::cout << "hour:"<< GetTimeCount(TIME_STAMP_H) << endl;
    std::cout << GetMsTimeStamp() << endl;
    return 0;
}