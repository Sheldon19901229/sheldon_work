#include <map>
#include <iostrteam>
#include <functional>

// method-1
using namespace std;
class Base;
using func_t = int(Base::*)(int);
class Base {
public:
    Base(){}
    int func_0(int var) {
        cout << "func_0:" << var << endl;
        return 0;
    }

    int func_1(int var) {
        cout << "func_1:" << var << endl;
        return 0;
    }

    void Run(int cmd) {
        auto item = m_func.find(cmd);
        if (item != m_func.end()) {
            (this->*(item->second))(cmd);
        }
    }

private:

    static std::map<int, func_t> m_func;
};

std::map<int, func_t> Base::m_func = {
    {0x0, &Base::func_0},
    {0x1, &Base::func_1}
};

// method-2
class Base {
public:
    Base(){
        m_func.emplace(0x0, std::bind(&Base::func_0, this, std::placeholders::_1));
        m_func.emplace(0x1, std::bind(&Base::func_1, this, std::placeholders::_1));
        m_func.emplace(0x2, [&](int a){ return func_2(a);});
        m_func.emplace(0x3, [&](int a){ return func_3(a);});
    }

    int func_0(int var) {
        cout << "func_0:" << var << endl;
        return 0;
    }

    int func_1(int var) {
        cout << "func_1:" << var << endl;
        return 0;
    }

    int func_2(int var) {
        cout << "func_2:" << var << endl;
        return 0;
    }

    int func_3(int var) {
        cout << "func_3:" << var << endl;
        return 0;
    }

    void Run(int cmd) {
        auto item = m_func.find(cmd);
        if (item != m_func.end()) {
          item->second(cmd);
        }
    }

private:
    std::map<int, std::function<int(int)>> m_func;
};
