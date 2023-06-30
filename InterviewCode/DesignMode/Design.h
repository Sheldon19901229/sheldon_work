// 外观模式
// 特点:将功能相同的特性封装在一起,子系统与客户端解耦,设计初期后开发过程中子系统越来越复杂
#include <iostream>
#include <memory>
#include <list>
#include <algorithm>
#include <functional>

using namespace std;
class Host {
public:
    void Start() {}
    void Close() {}
};

class LCDDispay {
public:
    void Start() {}
    void Close() {}
};

class Computer {
public:
    void Start() {
        m_host.Start();
        m_lcd.Start();
    }
    void Close() {
        m_host.Close();
        m_lcd.Close();
    }
private:
    Host m_host;
    LCDDispay m_lcd;
};

// 模板模式:骨架稳定,算法变化,稳定的函数写成非虚函数,算法写成虚函数,父类抽象,子类实现
// 缺点:每一个不同的实现都需要一个子类来实现,导致类的个数增加,使得系统更加庞大
// 工作实例:交叉板板对象的创建,Assemble函数中加载各个模块
class Computer {
public:
    void product()
    {
        installCpu();
        installRam();
        installGraphicsCard();
    }

protected:
    virtual void installCpu() = 0;
    virtual void installRam() = 0;
    virtual void installGraphicsCard() = 0;
};

class ComputerA : public Computer
{
protected:
    void installCpu() override
    {
        cout << "ComputerA install Inter Core i5" << endl;
    }

    void installRam() override
    {
        cout << "ComputerA install 2G Ram" << endl;
    }

    void installGraphicsCard() override
    {
        cout << "ComputerA install Gtx940 GraphicsCard" << endl;
    }
};

class ComputerB : public Computer
{
protected:
    void installCpu() override
    {
        cout << "ComputerB install Inter Core i7" << endl;
    }

    void installRam() override
    {
        cout << "ComputerB install 4G Ram" << endl;
    }

    void installGraphicsCard() override
    {
        cout << "ComputerB install Gtx960 GraphicsCard" << endl;
    }
};

// 代理模式(接口再封装)
// 特点:一个是真正的你要访问的对象(目标类)，一个是代理对象,真正对象与代理对象实现同一个接口,先访问代理类再访问真正要访问的对象,同交叉板加载子模块
class Gril
{
public:
    Gril(const string& name = "gril"):m_string(name){}
    string getName()
    {
        return m_string;
    }
private:
    string m_string;
};

class Profession
{
public:
    virtual ~Profession(){}
    virtual void profess() = 0;
};

class YoungMan : public Profession
{
public:
    YoungMan(const Gril& gril):m_gril(gril){}
    void profess()
    {
        cout << "Young man love " << m_gril.getName().data() << endl;
    }

private:
    Gril m_gril;
};

class ManProxy : public Profession
{
public:
    ManProxy(const Gril& gril):m_pMan(new YoungMan(gril)){}
    ~ManProxy()
    {
        delete m_pMan;
        m_pMan = nullptr;
    }
    void profess()
    {
        m_pMan->profess();
    }
private:
    YoungMan* m_pMan;
};

// 观察者模式:多个观察者具有相同的动作接口
// 特点:一(被观察者)对多(观察者们)
// 工作实例:GPIO通知多相机实现抓拍
class View;
//被观察者抽象类
class DataModel {
public:
    virtual ~DataModel(){}
    virtual void addView(View* view) = 0;
    virtual void removeView(View* view) = 0;
    virtual void notify() = 0;   //通知函数
};

//观察者抽象类
class View {
public:
    virtual ~View(){ cout << "~View()" << endl; }
    virtual void update() = 0;
    virtual void setViewName(const string& name) = 0;
    virtual const string& name() = 0;
};

//具体的被观察类
class IntDataModel:public DataModel {
public:
    ~IntDataModel()
    {
        m_pViewList.clear();
    }

    virtual void addView(View* view) override
    {
        shared_ptr<View> temp(view);
        auto iter = find(m_pViewList.begin(), m_pViewList.end(), temp);
        if(iter == m_pViewList.end())
        {
            m_pViewList.push_front(temp);
        }
        else
        {
            cout << "View already exists" << endl;
        }
    }

    void removeView(View* view) override
    {
        auto iter = m_pViewList.begin();
        for(; iter != m_pViewList.end(); iter++)
        {
            if((*iter).get() == view)
            {
                m_pViewList.erase(iter);
                cout << "remove view" << endl;
                return;
            }
        }
    }

    virtual void notify() override
    {
        auto iter = m_pViewList.begin();
        for(; iter != m_pViewList.end(); iter++)
        {
            (*iter).get()->update();
        }
    }

private:
    list<shared_ptr<View>> m_pViewList; 
};

//具体的观察者类
class TableView : public View {
public:
    TableView() : m_name("unknow"){}
    TableView(const string& name) : m_name(name){}
    ~TableView(){ cout << "~TableView(): " << m_name.data() << endl; }

    void setViewName(const string& name)
    {
        m_name = name;
    }

    const string& name()
    {
        return m_name;
    }

    void update() override
    {
        cout << m_name.data() << " update" << endl;
    }

private:
    string m_name;
};

// 组合模式:将对象组合成树形结构以表示“部分-整体”的层次结构，组合模式使得客户端对单个对象和组合对象的使用具有一直性
// 特点:希望客户端忽略组合对象与单个对象的不同，客户端将统一的使用组合结构中的所有对象,与观察者类似,但观察者是被动修改
// 抽象类，提供组合和单个对象的一致接口
class Company
{
public:
    Company(const string& name): m_name(name){}
    virtual ~Company(){ cout << "~Company()" << endl;}

    virtual void add(Company* ) = 0;
    virtual void remove(const string&) = 0;
    virtual void display(int depth) = 0;

    virtual const string& name()
    {
        return m_name;
    }

protected:
    string m_name;
};

//具体的单个对象实现类，“树枝”类
class HeadCompany : public Company
{
public:
    HeadCompany(const string& name): Company(name){}
    virtual ~HeadCompany(){ cout << "~HeadCompany()" << endl;}

    void add(Company* company) override
    {
        shared_ptr<Company> temp(company);
        m_companyList.push_back(temp);
    }

    void remove(const string& strName) override
    {
        list<shared_ptr<Company>>::iterator iter = m_companyList.begin();
        for(; iter != m_companyList.end(); iter++)
        {
            if((*iter).get()->name() == strName)
            {
            //不应该在此处使用list<T>.erase(list<T>::iterator iter),会导致iter++错误，这里删除目               标元素之后，必须return。
                m_companyList.erase(iter);
                return;
            }
        }
    }

    void display(int depth) override
    {
        for(int i = 0; i < depth; i++)
        {
            cout << "-";
        }
        cout << this->name().data() << endl;
        list<shared_ptr<Company>>::iterator iter = m_companyList.begin();
        for(; iter!= m_companyList.end(); iter++)
        {
            (*iter).get()->display(depth + 1);
        }
    }

private:
    list<shared_ptr<Company>> m_companyList;
};

//具体的单个对象实现类，“树叶”类
class ResearchCompany : public Company
{
public:
    ResearchCompany(const string& name): Company(name){}
    virtual ~ResearchCompany(){ cout << "~ResearchCompany()" << endl;}

    void add(Company* ) override
    {
    }

    void remove(const string&) override
    {
    }

    void display(int depth) override
    {
        for(int i = 0; i < depth; i++)
        {
            cout << "-";
        }
        cout << m_name.data() << endl;
    }
};

//具体的单个对象实现类，“树叶”类
class SalesCompany : public Company
{
public:
    SalesCompany(const string& name): Company(name){}
    virtual ~SalesCompany(){ cout << "~SalesCompany()" << endl;}

    void add(Company* ) override
    {
    }

    void remove(const string&) override
    {
    }

    void display(int depth) override
    {
        for(int i = 0; i < depth; i++)
        {
            cout << "-";
        }
        cout << m_name.data() << endl;
    }
};

//具体的单个对象实现类，“树叶”类
class FinanceCompany : public Company
{
public:
    FinanceCompany(const string& name): Company(name){}
    virtual ~FinanceCompany(){ cout << "~FinanceCompany()" << endl;}

    void add(Company* ) override
    {
    }

    void remove(const string&) override
    {
    }

    void display(int depth) override
    {
        for(int i = 0; i < depth; i++)
        {
            cout << "-";
        }
        cout << m_name.data() << endl;
    }
};


int main()
{
    HeadCompany* headRoot = new HeadCompany("Head Root Company");

    HeadCompany* childRoot1 = new HeadCompany("Child Company A");
    ResearchCompany* r1 = new ResearchCompany("Research Company A");
    SalesCompany* s1 = new SalesCompany("Sales Company A");
    SalesCompany* s2 = new SalesCompany("Sales Company B");
    FinanceCompany* f1 = new FinanceCompany("FinanceCompany A");
    
    childRoot1->add(r1);
    childRoot1->add(s1);
    childRoot1->add(s2);
    childRoot1->add(f1);

    HeadCompany* childRoot2 = new HeadCompany("Child Company B");
    ResearchCompany* r2 = new ResearchCompany("Research Company B");
    SalesCompany* s3 = new SalesCompany("Sales Company C");
    SalesCompany* s4 = new SalesCompany("Sales Company D");
    FinanceCompany* f2 = new FinanceCompany("FinanceCompany B");
    
    childRoot2->add(r2);
    childRoot2->add(s3);
    childRoot2->add(s4);
    childRoot2->add(f2);

    headRoot->add(childRoot1);
    headRoot->add(childRoot2);
    headRoot->display(1);
    
    cout << "\n***************\n" << endl;

    childRoot1->remove("Sales Company B");
    headRoot->display(1);
    
    cout << "\n***************\n" << endl;

    delete headRoot;
    headRoot = nullptr;

    return 0;
}

// 策略模式:策略模式是指定义一系列的算法,把它们单独封装起来并且使它们可以互相替换,使得算法可以独立于使用它的客户端而变化,客户端接口不变,算法多态。
// 特点:将策略或算法作为客户端的参数
// 工作实例:交叉板的组件层代码中加载ModuleIAL,DeviceIAl,分组组件等

//抽象策略类,提供一个接口
class Hurt {
public:
    virtual void blood() = 0;
    virtual ~Hurt() = default;
};

//具体的策略实现类:Adc持续普通攻击
class AdcHurt : public Hurt {
public:
    void blood() override
    {
        cout << "Adc hurt, Blood loss" << endl;
    }
};

//具体的策略实现类:Apc技能攻击
class ApcHurt : public Hurt {
public:
    void blood() override
    {
        cout << "Apc Hurt, Blood loss" << endl;
    }
};

// 环境角色类1:传入一个策略类指针参数。
class Soldier {
public:
    Soldier(Hurt* hurt):m_pHurt(hurt) {}
    //在不同的策略下,该游戏角色表现出不同的攻击
    void attack() {
        m_pHurt->blood();
    }
private:
    Hurt* m_pHurt; // 多态指针
};

// 定义策略标签
typedef enum
{
    Hurt_Type_Adc,
    Hurt_Type_Apc,
    Hurt_Type_Num
} HurtType;

// 环境角色类2:传入一个策略标签参数
class Mage {
public:
    Mage(HurtType type)
    {
        switch(type)
        {
        case Hurt_Type_Adc:
            m_pHurt = new AdcHurt();
            break;
        case Hurt_Type_Apc:
            m_pHurt = new ApcHurt();
            break;
        default:
            break;
        }
    }
    ~Mage()
    {
        delete m_pHurt;
        m_pHurt = nullptr;
        cout << "~Mage()" << endl;
    }

    void attack()
    {
        m_pHurt->blood();
    }
private:
    Hurt* m_pHurt;
};

// 环境角色类3:实现模板传递策略。
template<typename T>
class Archer {
public:
    void attack()
    {
        m_hurt.blood();
    }
private:
    T m_hurt;
};

int main() {
    Archer<ApcHurt>* arc = new Archer<ApcHurt>;
    arc->attack();

    delete arc;
    arc = nullptr;
    
    return 0;
}
// 2.函数指针:直接注册,类似回调
void adcHurt()
{
    std::cout << "Adc Hurt" << std::endl;
}

void apcHurt()
{
    std::cout << "Apc Hurt" << std::endl;
}

//环境角色类， 使用传统的函数指针
class Soldier
{
public:
    typedef void (*Function)();
    Soldier(Function fun): m_fun(fun)
    {
    }
    void attack()
    {
        m_fun();
    }
private:
    Function m_fun;
};

//环境角色类， 使用std::function<>
class Mage
{
public:
    typedef std::function<void()> Function;

    Mage(Function fun): m_fun(fun)
    {
    }
    void attack()
    {
        m_fun();
    }
private:
    Function m_fun;
};

int main()
{
    Soldier* soldier = new Soldier(apcHurt);
    soldier->attack();
    delete soldier;
    soldier = nullptr;
    return 0;
}

// 建造者模式
// 特点:对象构造比较复杂的场景,由建造者Builder和管理者Direcor组合
// 具体的产品类
class Order
{
public:
    void setFood(const string& food)
    {
        m_strFood = food;
    }

    const string& food()
    {
        cout << m_strFood.data() << endl;
        return m_strFood;
    }
    
    void setDrink(const string& drink)
    {
        m_strDrink = drink;
    }

    const string& drink()
    {
        cout << m_strDrink << endl;
        return m_strDrink;
    }

private:
    string m_strFood;
    string m_strDrink;
};

//抽象建造类，提供建造接口。
class OrderBuilder
{
public:
    virtual ~OrderBuilder()
    {
        cout << "~OrderBuilder()" << endl;
    }
    virtual void setOrderFood() = 0;
    virtual void setOrderDrink() = 0;
    virtual Order* getOrder() = 0;
};

//具体的建造类
class VegetarianOrderBuilder : public OrderBuilder 
{
public:
    VegetarianOrderBuilder()
    {
        m_pOrder = new Order;
    }

    ~VegetarianOrderBuilder()
    {
        cout << "~VegetarianOrderBuilder()" << endl;
        delete m_pOrder;
        m_pOrder = nullptr;
    }

    void setOrderFood() override
    {
        m_pOrder->setFood("vegetable salad");
    }

    void setOrderDrink() override
    {
        m_pOrder->setDrink("water");
    }

    Order* getOrder() override
    {
        return m_pOrder;
    }

private:
    Order* m_pOrder;
};

//具体的建造类
class MeatOrderBuilder : public OrderBuilder
{
public:
    MeatOrderBuilder()
    {
        m_pOrder = new Order;
    }
    ~MeatOrderBuilder()
    {
        cout << "~MeatOrderBuilder()" << endl;
        delete m_pOrder;
        m_pOrder = nullptr;
    }

    void setOrderFood() override
    {
        m_pOrder->setFood("beef");
    }

    void setOrderDrink() override
    {
        m_pOrder->setDrink("beer");
    }

    Order* getOrder() override
    {
        return m_pOrder;
    }

private:
    Order* m_pOrder;
};

//Director类，负责管理实例创建的依赖关系，指挥构建者类创建实例
class Director
{
public:
    Director(OrderBuilder* builder) : m_pOrderBuilder(builder)
    {
    }
    void construct()
    {
        m_pOrderBuilder->setOrderFood();
        m_pOrderBuilder->setOrderDrink();
    }

private:
    OrderBuilder* m_pOrderBuilder;
};


int main()
{
//  MeatOrderBuilder* mBuilder = new MeatOrderBuilder;
    OrderBuilder* mBuilder = new MeatOrderBuilder;  //注意抽象构建类必须有虚析构函数，解析时才会                                                      调用子类的析构函数
    Director* director = new Director(mBuilder);
    director->construct();
Order* order = mBuilder->getOrder();
order->food();
order->drink();

delete director;
director = nullptr;

delete mBuilder;
mBuilder = nullptr;

return 0;
}

// 适配器模式
// 接口转换，有点像代理模式，主要是对不同功能接口的统一
// 单端队列和栈的实现
//双端队列， 被适配类
class Deque
{
public:
    void push_back(int x)
    {
        cout << "Deque push_back:" << x << endl;
    }
    void push_front(int x)
    {
        cout << "Deque push_front:" << x << endl;
    }
    void pop_back()
    {
        cout << "Deque pop_back" << endl;
    }
    void pop_front()
    {
        cout << "Deque pop_front" << endl;
    }
};

//顺序类，抽象目标类
class Sequence  
{
public:
    virtual void push(int x) = 0;
    virtual void pop() = 0;
};

//栈,后进先出, 适配类
class Stack:public Sequence   
{
public:
    //将元素添加到堆栈的顶部。
    void push(int x) override
    {
        m_deque.push_front(x);
    }
    //从堆栈中删除顶部元素
    void pop() override
    {
        m_deque.pop_front();
    }
private:
    Deque m_deque;
};

//队列，先进先出，适配类
class Queue:public Sequence  
{
public:
    //将元素添加到队列尾部
    void push(int x) override
    {
        m_deque.push_back(x);
    }
    //从队列中删除顶部元素
    void pop() override
    {
        m_deque.pop_front();
    }
private:
    Deque m_deque;
};

// 桥接模式:一切都是虚接口,用到什么实例化什么对象
// 类似代理,在调用时在找到桥接的对象
//抽象App类，提供接口
class App
{
public:
    virtual ~App(){ cout << "~App()" << endl; }
    virtual void run() = 0;
};

//具体的App实现类
class GameApp:public App
{
public:
    void run()
    {
        cout << "GameApp Running" << endl;
    }
};

//具体的App实现类
class TranslateApp:public App
{
public:
    void run()
    {
        cout << "TranslateApp Running" << endl;
    }
};

//抽象手机类，提供接口
class MobilePhone
{
public:
    virtual ~MobilePhone(){ cout << "~MobilePhone()" << endl;}
    virtual void appRun(App* app) = 0;  //实现App与手机的桥接
};

//具体的手机实现类
class XiaoMi:public MobilePhone
{
public:
    void appRun(App* app)
    {
        cout << "XiaoMi: ";
        app->run();
    }
};

//具体的手机实现类
class HuaWei:public MobilePhone
{
public:
    void appRun(App* app)
    {
        cout << "HuaWei: ";
        app->run();
    }
};

int main()
{
    App* gameApp = new GameApp;
    App* translateApp = new TranslateApp;
    MobilePhone* mi = new XiaoMi;
    MobilePhone* hua = new HuaWei;
    mi->appRun(gameApp);
    mi->appRun(translateApp);
    hua->appRun(gameApp);
    hua->appRun(translateApp);

    delete hua;
    hua = nullptr;
    delete mi;
    mi = nullptr;
    delete gameApp;
    gameApp = nullptr;
    delete translateApp;
    translateApp = nullptr;

    return 0;
}
// 装饰模式:不方便采用继承方式实现额外功能时
// 特点:装饰类需要对被装饰对象增加附加责任
// 抽象构件（Component）角色：给出一个抽象接口，以规范准备接收附加责任的对象。
class Component
{
public:
    virtual ~Component(){}

    virtual void configuration() = 0;
};

//具体构件（Concrete Component）角色：定义一个将要接收附加责任的类。
class Car : public Component
{
public:
    void configuration() override
    {
        cout << "A Car" << endl;
    }
};

//装饰（Decorator）角色：持有一个构件（Component）对象的实例，并实现一个与抽象构件接口一致的接口。
class DecorateCar : public Component
{
public:
    DecorateCar(Component* car) : m_pCar(car){}

    void configuration() override
    {
        m_pCar->configuration();
    }

private:
    Component* m_pCar;
};

//具体装饰（Concrete Decorator）角色：负责给构件对象添加上附加的责任。
class DecorateLED : public DecorateCar
{
public:
    DecorateLED(Component* car) : DecorateCar(car){}

    void configuration() override
    {
        DecorateCar::configuration();
        addLED();
    }

private:
    void addLED()
    {
        cout << "Install LED" << endl;
    }

};

//具体装饰（Concrete Decorator）角色：负责给构件对象添加上附加的责任。
class DecoratePC : public DecorateCar
{
public:
    DecoratePC(Component* car) : DecorateCar(car){}

    void configuration() override
    {
        DecorateCar::configuration();
        addPC();
    }

private:
    void addPC()
    {
        cout << "Install PC" << endl;
    }
};

//具体装饰（Concrete Decorator）角色：负责给构件对象添加上附加的责任。
class DecorateEPB : public DecorateCar
{
public:
    DecorateEPB(Component* car) : DecorateCar(car){}

    void configuration() override
    {
        DecorateCar::configuration();
        addEPB();
    }

private:
    void addEPB()
    {
        cout << "Install Electrical Park Brake" << endl;
    }
};

int main()
{
    Car* car = new Car;
    DecorateLED* ledCar = new DecorateLED(car);
    DecoratePC* pcCar = new DecoratePC(ledCar);
    DecorateEPB* epbCar = new DecorateEPB(pcCar);

    epbCar->configuration();

    delete epbCar;
    epbCar = nullptr;

    delete pcCar;
    pcCar = nullptr;

    delete ledCar;
    ledCar = nullptr;

    delete car;
    car = nullptr;

    return 0;
}

 // https://www.cnblogs.com/schips/p/12306851.html