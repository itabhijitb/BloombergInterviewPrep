#pragma once
#include <iostream>
#include <cstdlib>

class Bomb {
	int x;
public:
	Bomb(): x(0) {}
	~Bomb() {
		throw "bomb";
	}

	void * operator new(size_t n) throw() {
		std::cout << "operator new called" << std::endl;
		return malloc(n);
	}

	void operator delete(void *p) throw() {
		std::cout << "operator delete called" << std::endl;
		if (p != nullptr) {
			delete p;
		}
	}

};

void f() {
	Bomb myBomb;

	Bomb *pBomb = new Bomb();
	try {
		delete pBomb;
	}
	catch (...) {
		std::cout << "caught exception" << std::endl;
	}
	throw "new Bomb";
}
int Main() {
	try {
		f();
	}
	catch (char *message) {
		std::cout << "f threw" << message << std::endl;
	}
	return 0;
}

