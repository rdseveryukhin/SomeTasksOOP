#include <iostream>

struct Number;
struct BinaryOperation;

struct Visitor {
	virtual void visitNumber(Number const* number) = 0;
	virtual void visitBinaryOperation(BinaryOperation const* operation) = 0;
	virtual ~Visitor() { }
};

struct Expression
{
	virtual double evaluate() const = 0;
	virtual void visit(Visitor* vistitor) const = 0;
	virtual ~Expression() { }
};

struct Number : Expression
{
	Number(double value)
		: value(value)
	{}

	double evaluate() const override {
		return value;
	}

	double get_value() const { return value; }

	void visit(Visitor* visitor) const { visitor->visitNumber(this); }

private:
	double value;
};

struct BinaryOperation : Expression
{
	BinaryOperation(Expression const* left, char op, Expression const* right)
		: left(left), op(op), right(right)
	{ }
	~BinaryOperation() override {
		delete left;
		delete right;
	}

	double evaluate() const override {
		if (op == '+') {
			return left->evaluate() + right->evaluate();
		}
		else if (op == '-') {
			return left->evaluate() - right->evaluate();
		}
		else if (op == '*') {
			return left->evaluate() * right->evaluate();
		}
		else if (op == '/') {
			return left->evaluate() / right->evaluate();
		}
	}

	Expression const* get_left() const { return left; }
	Expression const* get_right() const { return right; }
	char get_op() const { return op; }

	void visit(Visitor* visitor) const { visitor->visitBinaryOperation(this); }

private:
	Expression const* left;
	Expression const* right;
	char op;
};

struct PrintVisitor : Visitor {
	void visitNumber(Number const* number)
	{
		std::cout << number->get_value();

	}

	void visitBinaryOperation(BinaryOperation const* bop)
	{
		std::cout << '(';
		bop->get_left()->visit(this);
		std::cout << bop->get_op();
		bop->get_right()->visit(this);
		std::cout << ')';

	}
};

int main() {
	Expression* sube = new BinaryOperation(new Number(4.5), '*', new Number(5));
	Expression* expr = new BinaryOperation(new Number(3), '+', sube);
	PrintVisitor visitor;
	expr->visit(&visitor);
}
