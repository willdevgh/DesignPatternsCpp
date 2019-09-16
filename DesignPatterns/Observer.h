/*
�۲���ģʽ
�������֮���һ�ֶ�Զ��������ϵ��
��һ�������״̬�����ı�ʱ��
�������������Ķ��󶼵õ�֪ͨ�����Զ����¡�
*/

#pragma once
#include <forward_list>
#include <algorithm>
#include <string>
#include <functional>
#include <map>

inline namespace NewEd {
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

	template <typename Func>
	class Events : NonCopyable {
	public:
		Events() = default;
		~Events() = default;
		// ע��۲��� ��ֵ����
		int Connect(Func&& f) {
			return Assgin(f);
		}
		// ע��۲���
		int Connect(const Func& f) {
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
		int Assgin(Func&& f) {
			int nId = m_observerId++;
			m_connections.emplace(nId, std::forward<Func>(f));
			return nId;
		}
		int m_observerId = 0; // �۲��߶�Ӧ���
		std::map<int, Func> m_connections;
	};
}

namespace OldEd {
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
