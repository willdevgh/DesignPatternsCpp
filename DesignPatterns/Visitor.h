#pragma once

#include "DesignPatterns.h"

inline namespace VisitorNewEd {
	/*
	�Ľ�
	ʹ�ÿɱ����ģ��
	*/
	template <typename... Types>
	class Visitor;

	template <typename T, typename... Types>
	class Visitor<T, Types...> : Visitor<Types...> {
	public:
		Visitor() = default;
		virtual ~Visitor() = default;
		// ͨ�� using �������ػ���� Visit ͬ������
		using Visitor<Types...>::Visit;
		virtual void Visit(const T&) = 0;
	};

	template <typename T>
	class Visitor<T> {
	public:
		Visitor() = default;
		virtual ~Visitor() = default;
		virtual void Visit(const T&) = 0;
	};
}

namespace VisitorOldEd {
	/*
	ȱ��
	ÿ����һ�ֱ����������;�Ҫ�ڷ����߻��� Visitor ������һ����Ӧ�Ĵ��麯����
	������ ConcreteElement3 ����Ҫ�� Visitor ������һ�����麯����
	virtual void Visit(ConcreteElement3* element) = 0;
	����˵ Visitor �Ľӿڲ��ȶ���������Ҫ���¶���һ���ȶ��Ľӿڲ㣬
	��������Ϊ�����µı������߶��޸Ľӿڲ㡣
	*/
	class ConcreteElement1;
	class ConcreteElement2;

	// ������ ����
	class Visitor {
	public:
		Visitor() = default;
		virtual ~Visitor() = default;
		virtual void Visit(ConcreteElement1* element) = 0;
		virtual void Visit(ConcreteElement2* element) = 0;
	};

	// �������� ����
	class Element {
	public:
		Element() = default;
		virtual ~Element() = default;
		virtual void Accept(Visitor& visitor) = 0;
	};

	// ������ ����
	class ConcreteVisitor : public Visitor {
	public:
		ConcreteVisitor() = default;
		virtual ~ConcreteVisitor() = default;
		virtual void Visit(ConcreteElement1* element) override {
			std::cout << "Visit ConcreteElement1\n";
		};
		virtual void Visit(ConcreteElement2* element) override {
			std::cout << "Visit ConcreteElement2\n";
		};
	};

	// �������� ����
	class ConcreteElement1 : public Element {
	public:
		ConcreteElement1() = default;
		virtual ~ConcreteElement1() = default;
		virtual void Accept(Visitor& visitor) override {
			visitor.Visit(this);
		}
	};

	class ConcreteElement2 : public Element {
	public:
		ConcreteElement2() = default;
		virtual ~ConcreteElement2() = default;
		virtual void Accept(Visitor& visitor) override {
			visitor.Visit(this);
		}
	};

	// ���Դ���
	void TestVisitor() {
		ConcreteVisitor v;
		std::unique_ptr<Element> e1(new ConcreteElement1());
		std::unique_ptr<Element> e2(new ConcreteElement2());
		e1->Accept(v);
		e2->Accept(v);
	}

}
