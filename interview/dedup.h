//
//  dedup.h
//  interview
//
//  Created by Bhattacharjee, Abhijit on 3/23/18.
//  Copyright © 2018 Bhattacharjee, Abhijit. All rights reserved.
//

#ifndef dedup_h
#define dedup_h
#include <algorithm>
#include <vector>
#include <tuple>
#include <iterator>
namespace DeDup {
    template<typename Ty>
    auto dedup1(Ty set1, Ty set2) {
        decltype(set1) first_set, second_set, both_set;
        std::set_difference(set1.begin(), set1.end(), set2.begin(), set2.end(),
                            std::inserter(first_set, first_set.begin()));
        std::set_difference(set2.begin(), set2.end(), set1.begin(), set1.end(),
                            std::inserter(second_set, second_set.begin()));
        std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(),
                              std::inserter(both_set, both_set.begin()));
        return std::tuple<decltype(set1), decltype(set1), decltype(set1)>(first_set, second_set, both_set);
    }
    template<typename Ty>
    auto dedup2(Ty set1, Ty set2) {
        decltype(set1) first_set, second_set, both_set;
        auto it_set1 = set1.begin(), it_set2 = set2.begin();
        auto it_first_set = std::inserter(first_set, first_set.begin()),
        it_second_set = std::inserter(second_set, second_set.begin()),
        it_third_set = std::inserter(both_set, both_set.begin());
        for(;it_set1 != set1.end() && it_set2 != set2.end();) {
            if (*it_set1 < *it_set2) {
                it_first_set = *it_set1;
                it_set1++;
            } else if (*it_set1 > *it_set2) {
                it_second_set = *it_set2;
                it_set2++;
            } else {
                it_third_set = *it_set1;
                it_set1++;
                it_set2++;
            }
        }
        for(;it_set1 != set1.end();it_set1++) {
            it_first_set = *it_set1;
        }
        for(;it_set2 != set2.end();it_set2++) {
            it_second_set = *it_set2;
        }
        return std::tuple<decltype(set1), decltype(set1), decltype(set1)>(first_set, second_set, both_set);
    }
    template<typename TyLHS>
    auto Assert(TyLHS lseq, TyLHS rseq) {
        assert(std::equal(lseq.begin(), lseq.end(), rseq.begin()));
    }
    int Main() {
        auto result = DeDup::dedup2<std::vector<int>>({1,2,3,5,8}, {1,3,4,5,9});
        return 0;
    }
}
#endif /* dedup_h */
