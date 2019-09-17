/*
�۲���ģʽ
�������֮���һ�ֶ�Զ��������ϵ��
��һ�������״̬�����ı�ʱ��
�������������Ķ��󶼵õ�֪ͨ�����Զ����¡�
*/

#pragma once
#include "DesignPatterns.h"
#include <forward_list>
#include <map>

inline namespace ObserverNewEd {
	/*
	�Ľ�
	ͨ����֪ͨ�ӿڲ������� std::function ������̳�
	ͨ���ɱ����ģ�������ת���������ӿڱ仯������Ӱ��
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
		// ע��۲���
		int Connect(Function f) {
			return Assgin(f);
		}
		// �Ƴ��۲���
		void Disconnect(int id) {
			m_connections.erase(id);
		}
		// ֪ͨ���й۲���
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
		int m_observerId = 0; // �۲��߶�Ӧ���
		std::map<int, Function> m_connections;
	};
}

namespace ObserverOldEd {
	/*
	ȱ��
	����ͨ�ã�ֻ�ܶ� Observer �ĳ��������������Ч��
	���ܴ�����
	*/

	class Subject;

	// �۲��߽ӿ���
	class Observer {
	public:
		virtual ~Observer();
		virtual void Update(Subject* theChangedSubject) = 0;
	protected:
		Observer();
	};

	// ������
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
		std::forward_list<Observer*> _observers; // �۲����б�
	};
}

// ���Դ���
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