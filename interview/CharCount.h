#pragma once
#include <unordered_map>
#include<algorithm>
#include <cctype>
template<typename Ty>
auto findmaxoccur(const Ty &seq) {
	std::unordered_map<Ty::value_type, size_t> counter{ 0 };
	for (auto& token : seq) {
		if (std::isalpha(token)) {
			counter[token]++;
		}
	}
	auto max_elem =  std::max_element(
		std::begin(counter),
		std::end(counter),
		[](const std::pair<Ty::value_type, size_t>& lhs,
			const std::pair<Ty::value_type, size_t> &rhs) {
		return lhs.second < rhs.second;
	});
	return *max_elem;
}