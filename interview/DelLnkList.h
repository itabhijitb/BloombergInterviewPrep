#pragma once
#include <list>
template<typename Ty>
auto delElem(std::list<Ty> &lst, Ty val) {
	for (auto &it = std::begin(lst); it != std::end(lst); it++) {
		if (*it == val) {
			auto curr = it;
			it = next(it);
			lst.erase(curr);
		}
	}
}