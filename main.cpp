#include <iostream>
#include <memory>
#include "LearnStl.h"
#include "Sort.h"
#include <string>
#include "Log.h"
#include "TimeStamp.h"
#include "Solution.h"
#include <thread>

using namespace std;

int main()
{
    std::thread th = std::thread([] () { while (true) {
        WriteLog("[info]:test cpp %d", __LINE__);
        this_thread::sleep_for(std::chrono::seconds(1));
    } });

    th.join();
    return 0;
}