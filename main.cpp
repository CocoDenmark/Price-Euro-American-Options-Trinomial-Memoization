//
//  main.cpp
//  Assignment10
//
//  Created by miao on 11/8/14.
//  Copyright (c) 2014 miao. All rights reserved.
//


#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include "option_with_memoization.h"
using namespace std;

int main(int argc, const char * argv[]) {
    
    float risk_free_rate, strike_price;
    float initial_stock_price, expiration_time, volatility;
    int no_of_divisions;
   	
    sscanf (argv[1], "%f", &expiration_time);   //the input from the command line
    sscanf (argv[2], "%d", &no_of_divisions);
    sscanf (argv[3], "%f", &risk_free_rate);
    sscanf (argv[4], "%f", &volatility);
    sscanf (argv[5], "%f", &initial_stock_price);
    sscanf (argv[6], "%f", &strike_price);
    
    class option_with_memoization option(expiration_time, no_of_divisions, risk_free_rate, volatility, initial_stock_price, strike_price); //initialize an object
    
    option.display(); //tell the imformation about the given option
    return 0;
}
