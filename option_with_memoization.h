//
//  option_with_memoization.h
//  Assignment10
//
//  Created by miao on 11/8/14.
//  Copyright (c) 2014 miao. All rights reserved.
//

#ifndef __Assignment10__option_with_memoization__
#define __Assignment10__option_with_memoization__

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;



class option_with_memoization
{
private:
    double up_factor, uptick_prob, notick_prob, downtick_prob, risk_free_rate, strike_price;
    double initial_stock_price, expiration_time, volatility, R;
    int no_of_divisions;
    double **list; //here the pointer to pointer is used to memorize the price that has been calculated
public:
    option_with_memoization(double expiration_time, int no_of_divisions, double risk_free_rate, double volatility, double initial_stock_price, double strike_price);
    ~option_with_memoization();
    void display();
    double American_call_option(int k, int i, double current_price);
    double American_put_option(int k, int i, double current_price);
    double European_call_option(int k, int i);
    double European_put_option(int k, int i);

    void initialize();
};

#endif /* defined(__Assignment10__option_with_memoization__) */
