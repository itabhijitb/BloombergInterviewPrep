//
//  average.h
//  interview
//
//  Created by Bhattacharjee, Abhijit on 3/25/18.
//  Copyright © 2018 Bhattacharjee, Abhijit. All rights reserved.
//

#ifndef average_h
#define average_h
#include <initializer_list>
#include <algorithm>
#include <numeric>
namespace Average {
    template<size_t N>
    auto average(std::initializer_list<size_t> nums) {
        std::vector<size_t> result;
        for(auto it = nums.begin() ; std::distance(it, nums.end()) > N - 1; it++) {
            auto it_end = it;
            std::advance(it_end, N);
            result.push_back(std::accumulate(it, [&](decltype(it) it){std::advance(it, N); return it;}(it), 0) / N);
            
        }
        return result;
    }
    template<typename TyLHS>
    auto Assert(TyLHS lseq, TyLHS rseq) {
        assert(std::equal(lseq.begin(), lseq.end(), rseq.begin()));
    }
    void Main() {
        
        Assert(average<3>({1, 2, 3, 4, 5}), {2, 3, 4});
    }
}
#endif /* average_h */
