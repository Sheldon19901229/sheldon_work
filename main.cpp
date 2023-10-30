#include <iostream>
#include <memory>
#include "LearnStl.h"
#include "Sort.h"
#include <string>
//#include "Log.h"
#include "TimeStamp.h"
#include "Solution.h"
#include <thread>

using namespace std;

int main() {


    while(true) {
        std::cout << "ms:" << get_time_stamp_ms() << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}