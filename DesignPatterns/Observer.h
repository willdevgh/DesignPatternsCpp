/*
观察者模式
定义对象之间的一种多对多的依赖关系，
当一个对象的状态发生改变时，
所有依赖于它的对象都得到通知并被自动更新。
*/

#pragma once
#include "DesignPatterns.h"
#include <forward_list>
#include <map>

inline namespace ObserverNewEd {
	/*
	改进
	通过被通知接口参数化和 std::function 来替代继承
	通过可变参数模板和完美转发来消除接口变化产生的影响
	*/
	class NonCopyable {
	protected:
		NonCopyable() = default;
		~NonCopyable() = default;
		NonCopyable(const NonCopyable&) = delete;
		NonCopyable& operator=(const NonCopyable&) = delete;
	};

	template <typename Function>
	class Events : NonCopyable {
	public:
		Events() = default;
		~Events() = default;
		// 注册观察者
		int Connect(Function f) {
			return Assgin(f);
		}
		// 移除观察者
		void Disconnect(int id) {
			m_connections.erase(id);
		}
		// 通知所有观察者
		template <typename... Args>
		void Notify(Args&&... args) {
			for (auto& conn : m_connections) {
				conn.second(std::forward<Args>(args)...);
			}
		}
	private:
		int Assgin(Function f) {
			int nId = m_observerId++;
			m_connections.emplace(nId, f);
			return nId;
		}
		int m_observerId = 0; // 观察者对应编号
		std::map<int, Function> m_connections;
	};
}

namespace ObserverOldEd {
	/*
	缺点
	不够通用，只能对 Observer 的抽象类的派生类有效。
	不能带参数
	*/

	class Subject;

	// 观察者接口类
	class Observer {
	public:
		virtual ~Observer();
		virtual void Update(Subject* theChangedSubject) = 0;
	protected:
		Observer();
	};

	// 主题类
	class Subject {
	public:
		virtual ~Subject() = default;
		virtual void Attach(Observer* o) {
			_observers.push_front(o);
		};
		virtual void Detach(Observer* o) {
			_observers.remove(o);
		};
		virtual void Notify() {
			auto update = [&](Observer* o) { o->Update(this); };
			std::for_each(_observers.begin(), _observers.end(), update);
		};
	protected:
		Subject() = default;
	private:
		std::forward_list<Observer*> _observers; // 观察者列表
	};
}

// 测试代码
void TestObserver() {
	auto printAdd = [](int a, int b) {
		std::cout << a << " + " << b << " = " << a + b << std::endl;
	};

	auto printMul = [](int a, int b) {
		std::cout << a << " * " << b << " = " << a * b << std::endl;
	};

	Events<std::function<void(int, int)>> evt;
	int idAdd = evt.Connect(printAdd);
	int idMul = evt.Connect(printMul);
	evt.Notify(3, 5);
}