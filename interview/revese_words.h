//
//  revese_words.h
//  interview
//
//  Created by Bhattacharjee, Abhijit on 3/25/18.
//  Copyright © 2018 Bhattacharjee, Abhijit. All rights reserved.
//

#ifndef revese_words_h
#define revese_words_h
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
namespace ReverseWords {
    auto reverseWords(std::string st) {
        std::istringstream iss(st);
        std::string rev;
        std::vector<std::string> tokens;
        std::copy(std::istream_iterator<std::string>(iss),
                  std::istream_iterator<std::string>(),
                  std::back_inserter(tokens));
        auto it_front = tokens.begin();
        auto it_back = next(tokens.rbegin());
        for(;
            std::distance(it_front, it_back.base()) > 0;
            it_front++, it_back++
            ) {
            std::iter_swap(it_front, it_back.base());
        }
        std::accumulate(tokens.begin(),
                        tokens.end(),
                        std::string(),
                        [](auto result, auto st) {
                            result = result + " " + st;
                            return result;
                        });
        return st;
    }
    void Main() {
        reverseWords("Mary has a little lamb");
    }
};

#endif /* revese_words_h */
