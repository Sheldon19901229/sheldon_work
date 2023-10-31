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
    std::cout << GetMsTimeStamp() << endl;
    return 0;
}