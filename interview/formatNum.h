//
//  formatNum.h
//  interview
//
//  Created by Bhattacharjee, Abhijit on 3/20/18.
//  Copyright © 2018 Bhattacharjee, Abhijit. All rights reserved.
//

#ifndef formatNum_h
#define formatNum_h
#include <string>
#include <iostream>
namespace formatNum {


    std::string formatNum(int num) {
        std::string result;
        for(; num; num /= 10) {
            result += num % 10;
        }
        std::cout << result << std::endl;
        return result;
    }
    int Main() {
        std::string res;
        int _num;
        std::cin >> _num;
        
        res = formatNum(_num);
        std::cout << "Hello";
        
        return 0;
    }
}
#endif /* formatNum_h */
