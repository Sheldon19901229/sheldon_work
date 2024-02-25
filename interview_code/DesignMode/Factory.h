// 工厂模式是一种创建模式,用于常见复杂类对象
// 简单工厂
// 特点:由工厂根据客户参数实现产品
// 缺点:产品越多,程序臃肿
#include <iostream>

// 产品
class Product {
public:
    virtual void ShowMsg() = 0;
    virtual ~Product() = default;
};

class ProductA : public Product {
public:
    void ShowMsg() override {
        std::cout << "I am Product A!" << std::endl; 
    }

    ~ProductA() override = default;
};

class ProductB : public Product {
public:
    void ShowMsg() override {
        std::cout << "I am Product B!" << std::endl; 
    }

    ~ProductB() override = default;
};

// 工厂
class Factory {
public:
    Product* GetProduct(int id) {
        Product *obj = nullptr;
        switch (id) {
            case 1 : {
                obj = new ProductA();
                break;
            }
           
            case 2 : {
                obj = new ProductB();
                break;
            }
            default: {
                obj = nullptr;
                break;
            }

        }
        return obj;
    }
};

// 方法工厂
// 特点:抽象工厂,Switch-case子类化
// 缺点:子类多
class IIFactory {
public:
    virtual Product* GetProduct(int id) = 0;     
};

class AFactory : public IIFactory{
public:
    Product* GetProduct(int id) override {
        return new ProductA();
    }
};

class BFactory : public IIFactory{
public:
    Product* GetProduct(int id) override {
        return new ProductB();
    }
};

// 抽象工厂:产品定义方法,产品系列作为工厂子类实现方法
// 特点:抽象产品方法,子类按产品系列实现,当存在多个产品系列，而客户端只使用一个系列的产品时，可以考虑使用抽象工厂模式。
// 缺点:增加产品系列,增加创建接口 

class IDriver {
public:
    virtual void InitDriver() = 0;
};

class AboardDriver : public IDriver {
public:
    void InitDriver() override {
        std::cout << "A Driver" << std::endl;
    }
};

class BboardDriver : public IDriver {
public:
    void InitDriver() override {
        std::cout << "B Driver" << std::endl;
    }
};

class IAlmProcess
{
public:
    virtual void GetAlm() = 0;
};

class AAlmProcess : public IAlmProcess {
public:
    void GetAlm() override {
        std:: cout << "A Alm" << std::endl;
    }
};

class BAlmProcess : public IAlmProcess {
public:
    void GetAlm() override {
        std:: cout << "B Alm" << std::endl;
    }
};

class IFactory {
public:
    virtual IDriver* GetDriver() = 0;
    virtual IAlmProcess* LoadAlm() = 0;
};

class ABoardFactory : public IFactory {
public:
    IDriver* GetDriver() override {
        return new AboardDriver();
    }

    IAlmProcess* LoadAlm() override {
        return new AAlmProcess();
    }
};