//
//  runlength.h
//  interview
//
//  Created by Bhattacharjee, Abhijit on 3/25/18.
//  Copyright © 2018 Bhattacharjee, Abhijit. All rights reserved.
//

#ifndef runlength_h
#define runlength_h
#include <string>
namespace RunLength {
    auto runLength(std::string st) {
        std::string result;
        if (st.empty()) {
            return result;
        }
        size_t count = 1;
        auto it = st.begin();
        for(; next(it) != st.end(); it++, count++) {
            if (*it != *next(it)) {
                result += std::string(1, *it) + std::to_string(count);
                count = 0;
            }
        }
        result += std::string(1, *it) + std::to_string(count);
        return result;
    }
    
    void Main() {
        assert(RunLength::runLength("aaaaabbbccd") == "a5b3c2d1");
        assert(RunLength::runLength("xyz") == "x1y1z1");
    }
}

#endif /* runlength_h */
