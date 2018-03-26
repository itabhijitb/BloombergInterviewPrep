#pragma once
#include <queue>
#include <string>
#include <map>
#include <set>
#include <iostream>
class StreamCounter {
private:
	std::map<std::string, size_t> counter;
	std::map<size_t,
		std::set<std::map<std::string, size_t>::const_iterator>> indexes;
public:
	StreamCounter& operator+=(std::string word) {
		counter[word] += 1;
		if (counter[word] > 1) {
			std::map<std::string, size_t>::const_iterator it = counter.find(word);
			indexes[counter[word] - 1].erase(it);
		}
		indexes[counter[word]];// .insert(counter.find[word]);
	}

	auto print() {
		for (auto &index : indexes) {
			std::cout << index.first << "\t" << "[";
			for (auto &it : index.second) {
				std::cout << it->first << ",";
			}
			std::cout << "]" << std::endl;
		}
	}
};
