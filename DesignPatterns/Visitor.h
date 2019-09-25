#pragma once

#include "DesignPatterns.h"

inline namespace VisitorNewEd {
	/*
	改进
	使用可变参数模板
	*/

	template <typename... Types>
	class Visitor;
	
	template <typename T, typename... Types>
	class Visitor<T, Types...> : Visitor<Types...> {
	public:
		Visitor() = default;
		virtual ~Visitor() = default;
		// 通过 using 避免隐藏基类的 Visit 同名方法
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
	
	void TestVisitor() {
		struct stA;
		struct stB;
		struct Base {
			using MyVisitor = Visitor<stA, stB>;
			virtual void Accept(MyVisitor&) = 0;
		};
		struct stA : Base {
			double val = 0.0;
			virtual void Accept(Base::MyVisitor& v) override {
				v.Visit(*this);
			}
		};
		struct stB : Base {
			int val = 0;
			virtual void Accept(Base::MyVisitor& v) override {
				v.Visit(*this);
			}
		};
		struct PrintVisitor : Base::MyVisitor {
			virtual void Visit(const stA& a) override {
				std::cout << "from stA: " << a.val << std::endl;
			}

			virtual void Visit(const stB& b) override {
				std::cout << "from stB: " << b.val << std::endl;
			}
		};

		PrintVisitor vis;
		stA a;
		a.val = 3.14159;
		stB b;
		b.val = 42;
		Base* base = &a;
		base->Accept(vis);
		base = &b;
		base->Accept(vis);
	}
} // inline namespace VisitorNewEd

namespace VisitorOldEd {
	/*
	缺点
	每增加一种被访问者类型就要在访问者基类 Visitor 中增加一个对应的纯虚函数，
	若新增 ConcreteElement3 则需要在 Visitor 中增加一个纯虚函数：
	virtual void Visit(ConcreteElement3* element) = 0;
	所以说 Visitor 的接口不稳定，所以需要重新定义一个稳定的接口层，
	即不会因为增加新的被访问者而修改接口层。
	*/
	class ConcreteElement1;
	class ConcreteElement2;

	// 访问者 基类
	class Visitor {
	public:
		Visitor() = default;
		virtual ~Visitor() = default;
		virtual void Visit(ConcreteElement1* element) = 0;
		virtual void Visit(ConcreteElement2* element) = 0;
	};

	// 被访问者 基类
	class Element {
	public:
		Element() = default;
		virtual ~Element() = default;
		virtual void Accept(Visitor& visitor) = 0;
	};

	// 访问者 子类
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

	// 被访问者 子类
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

	// 测试代码
	void TestVisitor() {
		ConcreteVisitor v;
		std::unique_ptr<Element> e1(new ConcreteElement1());
		std::unique_ptr<Element> e2(new ConcreteElement2());
		e1->Accept(v);
		e2->Accept(v);
	}
} // namespace VisitorOldEd
