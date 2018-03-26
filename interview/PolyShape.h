#pragma once
#include <iostream>
#include <sstream>
class Shape {
protected:
	size_t length;
	virtual std::string Trace() = 0;
public:
	Shape(size_t length) : length(length) {}
	virtual void Draw() {
		std::cout << "Start Drawing" << std::endl;
		std::cout << Trace() << std::endl;
		std::cout << "End Drawing" << std::endl;
	}

};

class Circle : public Shape {
	static const size_t repeat = 360;
	static const size_t angle = 1;
	virtual std::string Trace() {
		std::stringstream op;
		op << "REPEAT " << repeat << "[FD" << length << " RT" << angle << "]";
		return op.str();
	}
public:
	Circle(size_t length) : Shape(length) {}
};

class Square : public Shape {
	static const size_t repeat = 4;
	static const size_t angle = 90;
	virtual std::string Trace() {
		std::stringstream op;
		op << "REPEAT " << repeat << "[FD" << length << " RT" << angle << "]";
		return op.str();
	}
public:
	Square(size_t length) : Shape(length) {}
};


class Triangle : public Shape {
	static const size_t repeat = 3;
	static const size_t angle = 60;
	virtual std::string Trace() {
		std::stringstream op;
		op << "REPEAT " << repeat << "[FD" << length << " RT" << angle << "]";
		return op.str();
	}
public:
	Triangle(size_t length) : Shape(length) {}
};
