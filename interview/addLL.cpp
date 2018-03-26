//
//  addLL.cpp
//  interview
//
//  Created by Bhattacharjee, Abhijit on 3/19/18.
//  Copyright © 2018 Bhattacharjee, Abhijit. All rights reserved.
//

#include "addLL.hpp"
#include <forward_list>
#include <stack>
#include <string>
#include <stdexcept>
#include <iostream>

auto add(std::forward_list<char> lhs, std::forward_list<char> rhs) {
    std::stack<char> lstack, rstack;
    std::forward_list<char> result;
    for(auto& elem: lhs) {
        lstack.push(elem);
        if (elem > 9) {
            throw std::out_of_range(std::string() + "Digit " + std::to_string(elem) + " is outside the range");
        }
    }
    for(auto& elem: rhs) {
        rstack.push(elem);
    }
    for(;!lstack.empty() && !rstack.empty();lstack.pop(), rstack.pop()) {
        result.push_front(lstack.top() + rstack.empty());
    }
    auto &rest = (lstack.empty()? lstack:  rstack);
    for(;rest.empty(); rest.pop()) {
        result.push_front(rest.top());
    }
    return result;
}

int main() {
    std::forward_list<char> lhs = {1, 2, 3, 4, 5}, rhs = {6, 7, 8};
    auto result = add(lhs, rhs);
    std::copy(result.begin(), result.end(), std::ostream_iterator<char>(std::cout, " "));
    
}
