//
//  bracket.h
//  interview
//
//  Created by Bhattacharjee, Abhijit on 3/25/18.
//  Copyright © 2018 Bhattacharjee, Abhijit. All rights reserved.
//

#ifndef bracket_h
#define bracket_h
#include <string>
#include <stack>
namespace Bracket {
    auto count(std::string st) {
        std::stack<char> stack;
        for(auto& ch: st) {
            switch(ch) {
            case '{': case '[': case'(':
                stack.push(ch);
                continue;
            case '}':
                ch = '{';
                break;
            case ']':
                ch = '[';
                break;
            case ')':
                ch = '(';
                break;
            default:
                    continue;
            }
            if (stack.size() == 0) {
                return false;
            }
            if(stack.top() != ch) {
                return false;
            }
            stack.pop();
        }
        if (stack.size() > 0) {
            return false;
        }
        return true;
    }
    void Main() {
        assert(count("(aa)bb"));
        assert(count("[ aa [ bbb ]" ) == false);
        assert(count("aa } bbb { c") == false);
        assert(count("aa [ bb () ]"));
        assert(count("[aa { ] cc } ]") == false);
    }
}

#endif /* bracket_h */
