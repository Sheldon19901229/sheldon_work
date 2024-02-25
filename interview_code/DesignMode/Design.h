// ���ģʽ
// �ص�:��������ͬ�����Է�װ��һ��,��ϵͳ��ͻ��˽���,��Ƴ��ں󿪷���������ϵͳԽ��Խ����
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

// ģ��ģʽ:�Ǽ��ȶ�,�㷨�仯,�ȶ��ĺ���д�ɷ��麯��,�㷨д���麯��,�������,����ʵ��
// ȱ��:ÿһ����ͬ��ʵ�ֶ���Ҫһ��������ʵ��,������ĸ�������,ʹ��ϵͳ�����Ӵ�
// ����ʵ��:���������Ĵ���,Assemble�����м��ظ���ģ��
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

// ����ģʽ(�ӿ��ٷ�װ)
// �ص�:һ������������Ҫ���ʵĶ���(Ŀ����)��һ���Ǵ������,����������������ʵ��ͬһ���ӿ�,�ȷ��ʴ������ٷ�������Ҫ���ʵĶ���,ͬ����������ģ��
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

// �۲���ģʽ:����۲��߾�����ͬ�Ķ����ӿ�
// �ص�:һ(���۲���)�Զ�(�۲�����)
// ����ʵ��:GPIO֪ͨ�����ʵ��ץ��
class View;
//���۲��߳�����
class DataModel {
public:
    virtual ~DataModel(){}
    virtual void addView(View* view) = 0;
    virtual void removeView(View* view) = 0;
    virtual void notify() = 0;   //֪ͨ����
};

//�۲��߳�����
class View {
public:
    virtual ~View(){ cout << "~View()" << endl; }
    virtual void update() = 0;
    virtual void setViewName(const string& name) = 0;
    virtual const string& name() = 0;
};

//����ı��۲���
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

//����Ĺ۲�����
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

// ���ģʽ:��������ϳ����νṹ�Ա�ʾ������-���塱�Ĳ�νṹ�����ģʽʹ�ÿͻ��˶Ե����������϶����ʹ�þ���һֱ��
// �ص�:ϣ���ͻ��˺�����϶����뵥������Ĳ�ͬ���ͻ��˽�ͳһ��ʹ����Ͻṹ�е����ж���,��۲�������,���۲����Ǳ����޸�
// �����࣬�ṩ��Ϻ͵��������һ�½ӿ�
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

//����ĵ�������ʵ���࣬����֦����
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
            //��Ӧ���ڴ˴�ʹ��list<T>.erase(list<T>::iterator iter),�ᵼ��iter++��������ɾ��Ŀ               ��Ԫ��֮�󣬱���return��
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

//����ĵ�������ʵ���࣬����Ҷ����
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

//����ĵ�������ʵ���࣬����Ҷ����
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

//����ĵ�������ʵ���࣬����Ҷ����
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

// ����ģʽ:����ģʽ��ָ����һϵ�е��㷨,�����ǵ�����װ��������ʹ���ǿ��Ի����滻,ʹ���㷨���Զ�����ʹ�����Ŀͻ��˶��仯,�ͻ��˽ӿڲ���,�㷨��̬��
// �ص�:�����Ի��㷨��Ϊ�ͻ��˵Ĳ���
// ����ʵ��:���������������м���ModuleIAL,DeviceIAl,���������

//���������,�ṩһ���ӿ�
class Hurt {
public:
    virtual void blood() = 0;
    virtual ~Hurt() = default;
};

//����Ĳ���ʵ����:Adc������ͨ����
class AdcHurt : public Hurt {
public:
    void blood() override
    {
        cout << "Adc hurt, Blood loss" << endl;
    }
};

//����Ĳ���ʵ����:Apc���ܹ���
class ApcHurt : public Hurt {
public:
    void blood() override
    {
        cout << "Apc Hurt, Blood loss" << endl;
    }
};

// ������ɫ��1:����һ��������ָ�������
class Soldier {
public:
    Soldier(Hurt* hurt):m_pHurt(hurt) {}
    //�ڲ�ͬ�Ĳ�����,����Ϸ��ɫ���ֳ���ͬ�Ĺ���
    void attack() {
        m_pHurt->blood();
    }
private:
    Hurt* m_pHurt; // ��ָ̬��
};

// ������Ա�ǩ
typedef enum
{
    Hurt_Type_Adc,
    Hurt_Type_Apc,
    Hurt_Type_Num
} HurtType;

// ������ɫ��2:����һ�����Ա�ǩ����
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

// ������ɫ��3:ʵ��ģ�崫�ݲ��ԡ�
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
// 2.����ָ��:ֱ��ע��,���ƻص�
void adcHurt()
{
    std::cout << "Adc Hurt" << std::endl;
}

void apcHurt()
{
    std::cout << "Apc Hurt" << std::endl;
}

//������ɫ�࣬ ʹ�ô�ͳ�ĺ���ָ��
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

//������ɫ�࣬ ʹ��std::function<>
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

// ������ģʽ
// �ص�:������Ƚϸ��ӵĳ���,�ɽ�����Builder�͹�����Direcor���
// ����Ĳ�Ʒ��
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

//�������࣬�ṩ����ӿڡ�
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

//����Ľ�����
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

//����Ľ�����
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

//Director�࣬�������ʵ��������������ϵ��ָ�ӹ������ഴ��ʵ��
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
    OrderBuilder* mBuilder = new MeatOrderBuilder;  //ע����󹹽������������������������ʱ�Ż�                                                      �����������������
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

// ������ģʽ
// �ӿ�ת�����е������ģʽ����Ҫ�ǶԲ�ͬ���ܽӿڵ�ͳһ
// ���˶��к�ջ��ʵ��
//˫�˶��У� ��������
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

//˳���࣬����Ŀ����
class Sequence  
{
public:
    virtual void push(int x) = 0;
    virtual void pop() = 0;
};

//ջ,����ȳ�, ������
class Stack:public Sequence   
{
public:
    //��Ԫ����ӵ���ջ�Ķ�����
    void push(int x) override
    {
        m_deque.push_front(x);
    }
    //�Ӷ�ջ��ɾ������Ԫ��
    void pop() override
    {
        m_deque.pop_front();
    }
private:
    Deque m_deque;
};

//���У��Ƚ��ȳ���������
class Queue:public Sequence  
{
public:
    //��Ԫ����ӵ�����β��
    void push(int x) override
    {
        m_deque.push_back(x);
    }
    //�Ӷ�����ɾ������Ԫ��
    void pop() override
    {
        m_deque.pop_front();
    }
private:
    Deque m_deque;
};

// �Ž�ģʽ:һ�ж�����ӿ�,�õ�ʲôʵ����ʲô����
// ���ƴ���,�ڵ���ʱ���ҵ��ŽӵĶ���
//����App�࣬�ṩ�ӿ�
class App
{
public:
    virtual ~App(){ cout << "~App()" << endl; }
    virtual void run() = 0;
};

//�����Appʵ����
class GameApp:public App
{
public:
    void run()
    {
        cout << "GameApp Running" << endl;
    }
};

//�����Appʵ����
class TranslateApp:public App
{
public:
    void run()
    {
        cout << "TranslateApp Running" << endl;
    }
};

//�����ֻ��࣬�ṩ�ӿ�
class MobilePhone
{
public:
    virtual ~MobilePhone(){ cout << "~MobilePhone()" << endl;}
    virtual void appRun(App* app) = 0;  //ʵ��App���ֻ����Ž�
};

//������ֻ�ʵ����
class XiaoMi:public MobilePhone
{
public:
    void appRun(App* app)
    {
        cout << "XiaoMi: ";
        app->run();
    }
};

//������ֻ�ʵ����
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
// װ��ģʽ:��������ü̳з�ʽʵ�ֶ��⹦��ʱ
// �ص�:װ������Ҫ�Ա�װ�ζ������Ӹ�������
// ���󹹼���Component����ɫ������һ������ӿڣ��Թ淶׼�����ո������εĶ���
class Component
{
public:
    virtual ~Component(){}

    virtual void configuration() = 0;
};

//���幹����Concrete Component����ɫ������һ����Ҫ���ո������ε��ࡣ
class Car : public Component
{
public:
    void configuration() override
    {
        cout << "A Car" << endl;
    }
};

//װ�Σ�Decorator����ɫ������һ��������Component�������ʵ������ʵ��һ������󹹼��ӿ�һ�µĽӿڡ�
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

//����װ�Σ�Concrete Decorator����ɫ�������������������ϸ��ӵ����Ρ�
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

//����װ�Σ�Concrete Decorator����ɫ�������������������ϸ��ӵ����Ρ�
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

//����װ�Σ�Concrete Decorator����ɫ�������������������ϸ��ӵ����Ρ�
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