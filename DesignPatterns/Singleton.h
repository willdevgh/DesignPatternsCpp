/*
����ģʽ
��֤һ����ֻ��һ��ʵ�������ṩһ����������ȫ�ַ��ʵ㡣
*/

#pragma once

template <typename T>
class Singleton {
public:
	template<typename... Args>
	static T* Instance(Args&&... args) {
		if (m_pInstance == nullptr) {
			m_pInstance = new T(std::forward<Args>(args)...);
		}
		return m_pInstance;
	}
	static T* GetInstance() {
		if (m_pInstance == nullptr) {
			throw std::logic_error("instance is not initialize.");
		}
		return m_pInstance;
	}
	static void DestroyInstance() {
		delete m_pInstance;
		m_pInstance = nullptr;
	}
private:
	Singleton(void);
	virtual ~Singleton(void);
	Singleton(const Singleton&);
	Singleton& operator = (const Singleton&);
	static T* m_pInstance;
};

template <typename T>
T* Singleton<T>::m_pInstance = nullptr;