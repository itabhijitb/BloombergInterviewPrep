//
//  overlap.h
//  interview
//
//  Created by Bhattacharjee, Abhijit on 3/25/18.
//  Copyright © 2018 Bhattacharjee, Abhijit. All rights reserved.
//

#ifndef overlap_h
#define overlap_h
#include <initializer_list>
#include <tuple>
namespace OverLap {
    auto overlap(std::initializer_list<std::tuple<size_t, size_t>> lists) {
        size_t start = std::get<0>(*lists.begin()), end = 0;
        std::list<std::tuple<size_t, size_t>> newlist;
        auto it = lists.begin();
        for(; next(it) != lists.end(); it++) {
            if (std::get<1>(*it) < std::get<0>(*next(it))) {
                end = std::get<1>(*it);
                newlist.push_back(std::make_tuple(start, end));
                start = std::get<0>(*next(it));
            }
        }
        end = std::get<1>(*it);
        newlist.push_back(std::make_tuple(start, end));
        return newlist;
    }
    template<typename TyLHS>
    auto Assert(TyLHS lseq, TyLHS rseq) {
        assert(std::equal(lseq.begin(), lseq.end(), rseq.begin()));
    }
    void Main() {
        Assert(overlap({std::make_tuple(1, 3),
                        std::make_tuple(2, 5),
                        std::make_tuple(8, 9)}),
               {{1, 5}, {8, 9}});
        Assert(overlap({std::make_tuple(1, 3),
            std::make_tuple(2, 6),
            std::make_tuple(4, 99)
        }),
               {{1, 99}});
    }
}

#endif /* overlap_h */
