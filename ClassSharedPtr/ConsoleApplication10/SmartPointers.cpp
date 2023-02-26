#include <iostream>

struct Expression {
	Expression (const char* str) : str(str) {}
	const char* str;
};
struct Number;
struct BinaryOperation;

struct SharedPtr
{
	// реализуйте следующие методы

	explicit SharedPtr(Expression *ptr = 0) {
		this->ptr_ = ptr;
		this->count = new size_t(0);
	}

	~SharedPtr() {
		if ((*count) > 0) {
			(*count)--;
		}
		else {
			delete ptr_;
			delete count;
		}
	}

	SharedPtr(const SharedPtr &other) {
		this->ptr_ = other.ptr_;
		this->count = other.count;
		(*count)++;
	}

	SharedPtr& operator=(const SharedPtr &other) {
		if (this != &other) {
			if ((*count) > 0) {
				(*count)--;
			}
			else {
				delete ptr_;
				delete count;
			}
			this->ptr_ = other.ptr_;
			this->count = other.count;
			(*count)++;
		}
		return *this;
	}

	Expression* get() const {
		return ptr_;
	}

	void reset(Expression *ptr = 0) {
		if ((*count) > 0) {
			(*count)--;
		}
		else {
			delete ptr_;
			delete count;
		}
		ptr_ = ptr;
		count = new size_t(0);
	}

	Expression& operator*() const {
		return *ptr_;
	}

	Expression* operator->() const {
		return ptr_;
	}
private:
	Expression* ptr_;
	size_t* count;
};

int main() {

	SharedPtr p1;
	SharedPtr p2(new Expression("expr1"));
	SharedPtr p3(new Expression("expr2"));
	SharedPtr p4(p2);
	SharedPtr p5;
	p5 = p2;
	p5 = p4;
	p1 = p5;
	p3.reset(NULL);
	p3 = p5;
	p5.reset(NULL);
	SharedPtr p6;
	SharedPtr p7;
	p7 = p7;
	p7.reset(NULL);
	p7.reset(new Expression("expr3"));
	SharedPtr p8(new Expression("expr4"));
	p8.reset(NULL);
	p1 = p1;
	
	if (_CrtDumpMemoryLeaks()) {
		std::cout << "memory leak is detected" << std::endl;
	}
	else {
		std::cout << "no memory leaks" << std::endl;
	}
}