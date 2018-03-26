//
//  counter.h
//  interview
//
//  Created by Bhattacharjee, Abhijit on 3/25/18.
//  Copyright © 2018 Bhattacharjee, Abhijit. All rights reserved.
//

#ifndef counter_h
#define counter_h
#include <initializer_list>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <iterator>
#include <queue>
#include <unordered_map>
#include <functional>
namespace CounterNS {
    template<size_t N>
    class Counter {
        struct ArrayValue{
            size_t count = 0;
            std::string site = "";
            bool operator<(const ArrayValue& rhs) const {
                return count < rhs.count;
            }
            bool operator>(const ArrayValue& rhs) const {
                return count > rhs.count;
            }
        };
        struct CounterValue{
            size_t count = 0;
            typename std::array<ArrayValue, N>::iterator index = nullptr;
        };

        std::unordered_map<std::string, CounterValue> counter;
        std::array<ArrayValue, N> top;
        size_t size = 0;
    public:
        auto operator+=(std::string site) {
            counter[site].count ++;
            if (size < N && counter[site].count == 1) {
                top[size] = ArrayValue{counter[site].count, site};
                counter[site].index = std::next(top.begin(), size);
                size++;
            } else if (!counter[site].index){
                if (counter[site].count > top.back().count) {
                    counter[top.back().site].index = nullptr;
                    top.back() = ArrayValue{counter[site].count, site};
                    counter[site].index = std::prev(top.end());
                }
            } else if (counter[site].index  && counter[site].count > std::prev(counter[site].index)->count){
                /*
                 K   S1    S2    S3    S4
                 V  (3,0)  (2,1) (3,2) (2,1)
                           ^      |
                           |      V
                 T   0     1      2
                    (3,S1) (2,S2) (2,S3)
                           ^      |
                           |______|
                 site = S3
                 */
                auto prev_site = std::prev(counter[site].index)->site;
                std::iter_swap(counter[site].index, std::prev(counter[site].index));
                std::swap(counter[prev_site].index, counter[site].index);
                
            }
            if (counter[site].index) {
                counter[site].index->count = counter[site].count;
            }
            
        };
        const auto most_common_eod() {
            std::vector<ArrayValue> result;
            std::priority_queue<ArrayValue,
                                std::vector<ArrayValue>,
                                std::less<ArrayValue>> queue;
            for(auto& elem: counter) {
                queue.push(ArrayValue{elem.second.count, elem.first});
            }
            for(int i = 0; i < N && !queue.empty(); i++, queue.pop()) {
                result.push_back(queue.top());
                
            }
            return result;
            
        }
        const auto& most_common_tod() {
            return top;
        }
        
    };
    void Main() {
        Counter<4> counter;
        counter += "www.google.com";
        counter += "nytimes.com";
        counter += "guardian.co.uk";
        counter += "dev.ibm.com";
        counter += "www.google.com";
        counter += "nytimes.com";
        counter += "nytimes.com";
        counter += "dev.ibm.com";
        counter += "dev.ibm.com";
        counter += "dev.ibm.com";
        counter += "dev.ibm.com";
        counter += "www.google.com";
        counter += "www.google.com";
        counter += "www.google.com";
        counter += "www.google.com";
        for(auto& site: counter.most_common_tod()) {
            std::cout << site.site << '\t' << site.count << std::endl;
        }
        for(auto& site: counter.most_common_eod()) {
            std::cout << site.site << '\t' << site.count << std::endl;
        }
    }
};

#endif /* counter_h */
