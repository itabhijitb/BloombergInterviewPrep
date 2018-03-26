#pragma once
#include <string>
#include <unordered_set>
#include <algorithm>
auto removeDup(std::string& st) {
	std::unordered_set<char> seen;
	st.erase(std::remove_if(
		std::begin(st),
		std::end(st),
		[&seen](char ch) {
		if (seen.count(ch) != 0) {
			return true;
		}
		else {
			seen.insert(ch);
			return false;
		}
	}), std::end(st));
	return st;
}
