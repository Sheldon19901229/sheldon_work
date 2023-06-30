#pragma once
#include <mutex>
#include <memory>

// 单例类的特点
// 1.构造函数和析构函数为私有类型(采用智能指针时,析构函数不能为私有),目的是禁止外部构造和析构。
// 2.拷贝构造函数和赋值构造函数是私有类型,目的是禁止外部拷贝和赋值,确保实例的唯一性。
// 3.类中有一个获取实例的静态方法，可以全局访问。

// 单例模式 懒汉式 线程安全
class SingleInstance_0 {
public:

	static SingleInstance_0* GetInstance() {
		if (m_instance == nullptr) {
			m_instanceMutex.lock();
			if (m_instance == nullptr) {
				m_instance = new SingleInstance_0();
			}
			m_instanceMutex.unlock();
		}
		return m_instance;
	}

	static void DeleteInstance() {
        m_instanceMutex.lock();
		if (m_instance != nullptr) {
			delete m_instance;
		}

		m_instance = nullptr;
        m_instanceMutex.unlock();
	}

private:
	SingleInstance_0()  = default;
	~SingleInstance_0() = default;
	SingleInstance_0(const SingleInstance_0& rhs);
	SingleInstance_0(const SingleInstance_0&& rhs);
	const SingleInstance_0& operator=(const SingleInstance_0& rsh);
	const SingleInstance_0& operator=(const SingleInstance_0&& rsh);

private:

	static SingleInstance_0* m_instance;
	static std::mutex m_instanceMutex;
};
SingleInstance_0* SingleInstance_0::m_instance = nullptr;
std::mutex SingleInstance_0::m_instanceMutex;

// 单例模式 饿汉式 线程安全
class SingleInstance_1 {
public:

	static SingleInstance_1* GetInstance() {
		return m_instance;
	}

	static void DeleteInstance() {
		if (m_instance != nullptr) {
			delete m_instance;
		}
		m_instance = nullptr;
	}

private:

	SingleInstance_1() = default;
	~SingleInstance_1() = default;
	SingleInstance_1(const SingleInstance_1& rhs);
	const SingleInstance_1& operator=(const SingleInstance_1& rsh);

private:

	static SingleInstance_1* m_instance;
};
SingleInstance_1* SingleInstance_1::m_instance = new SingleInstance_1();

// 单例模式 C++11 call_once线程安全
class SingleInstance_2 {
public:
    static std::shared_ptr<SingleInstance_2> GetInstance() {
        std::call_once(flag, [&] {m_instance = std::shared_ptr<SingleInstance_2>(new SingleInstance_2());});
        return m_instance;
    }

    ~SingleInstance_2() = default; // 需要定义析构函数
	

private:
    SingleInstance_2()  = default;
	SingleInstance_2(const SingleInstance_2& rhs);
	const SingleInstance_2& operator=(const SingleInstance_2& rsh);

private:
    static std::shared_ptr<SingleInstance_2> m_instance;
    static std::once_flag flag;
};
std::shared_ptr<SingleInstance_2> SingleInstance_2::m_instance = nullptr;
std::once_flag SingleInstance_2::flag;

// 改进的单例模式,c++11的例表参数
template<typename T>
class SingleInstance_3 {
public:
   template<typename... Args>
   static T* Instance(Args&&... agrs) {
        if (m_instance == nullptr) {
            m_instance = new T(std::forward<Args>(args)...);
        }
        return m_instance;
   }
	
    static T* GetInstance() {
        return m_instance;
    }

    static void DeleteInstance() {
        delete m_instance;
        m_instance = nullptr;
    }

private:
    SingleInstance_3()  = default;
    virtual ~SingleInstance_3() =  default;
	SingleInstance_2(const SingleInstance_2& rhs);
	const SingleInstance_3& operator=(const SingleInstance_3& rsh);

private:
    static T* m_instance;
};
template<class T> T* SingleInstance_3<T>::m_instance = nullptr;