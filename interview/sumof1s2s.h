//
//  sumof1s2s.h
//  interview
//
//  Created by Bhattacharjee, Abhijit on 3/25/18.
//  Copyright © 2018 Bhattacharjee, Abhijit. All rights reserved.
//

#ifndef sumof1s2s_h
#define sumof1s2s_h
#include <map>
namespace Sum1s2s {
    std::map<size_t, size_t> memo;
    auto sum1(size_t n) {
        if (n < 3) return n;
        if (memo.count(n) == 0) {
            return memo[n] = sum1(n-1) + sum1(n-2);
        }
        return memo[n];
    }
    
    auto sum2(size_t n) {
        return 2 * n - 3;
    }
    void Main() {
        std::cout<< sum2(10) << std::endl;
    }
}

#endif /* sumof1s2s_h */
