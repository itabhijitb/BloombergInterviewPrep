//
//  addLL.hpp
//  interview
//
//  Created by Bhattacharjee, Abhijit on 3/19/18.
//  Copyright © 2018 Bhattacharjee, Abhijit. All rights reserved.
//

#ifndef addLL_hpp
#define addLL_hpp

#include <forward_list>
#include <stack>
#include <string>
#include <stdexcept>
#include <iostream>
#include <cassert>
#include <algorithm>
#include "addLL.hpp"
namespace addLL {


    auto add(std::forward_list<int> lhs, std::forward_list<int> rhs) {
        std::stack<int> lstack, rstack;
        std::forward_list<int> result;
        for(auto& elem: lhs) {
            lstack.push(elem);
            if (elem > 9) {
                throw std::out_of_range(std::string() + "Digit " + std::to_string(elem) + " is outside the range");
            }
        }
        for(auto& elem: rhs) {
            rstack.push(elem);
            if (elem > 9) {
                throw std::out_of_range(std::string() + "Digit " + std::to_string(elem) + " is outside the range");
            }
        }
        int carry = 0;
        for(;!lstack.empty() && !rstack.empty();lstack.pop(), rstack.pop()) {
            auto sum = lstack.top() + rstack.top() + carry;
            result.push_front(sum % 10);
            carry = sum / 10;
        }
        auto &rest = (!lstack.empty()? lstack:  rstack);
        for(;!rest.empty(); rest.pop()) {
            auto sum = rest.top() + carry;
            result.push_front(sum % 10);
            carry = sum / 10;
        }
        if (carry) {
            result.push_front(carry);
        }
        return result;
    }
    template<typename TyLHS>
    auto Assert(TyLHS lseq, TyLHS rseq) {
        assert(std::equal(lseq.begin(), lseq.end(), rseq.begin()));
    }
    int Main() {
        Assert(add({1, 2, 3, 4, 5}, {6, 7, 8}), {1, 3, 0, 2, 3});
        Assert(add({}, {6, 7, 8}), {6, 7, 8});
        Assert(add({}, {0}), {0});
        Assert(add({}, {}), {});
        Assert(add({9, 9, 9, 9, 9}, {1}), {1, 0, 0, 0, 0, 0});
        return 0;
    }
}

#endif /* addLL_hpp */
