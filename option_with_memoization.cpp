//
//  option_with_memoization.cpp
//  Assignment10
//
//  Created by miao on 11/8/14.
//  Copyright (c) 2014 miao. All rights reserved.
//

#include "option_with_memoization.h"
#include "BS.h"
//this is the construction function
//all the attributes are initialized here using the input from the command line
option_with_memoization::option_with_memoization(double expiration_time, int no_of_divisions, double risk_free_rate, double volatility, double initial_stock_price, double strike_price)
{
    this->expiration_time = expiration_time;
    this->no_of_divisions = no_of_divisions;
    this->risk_free_rate = risk_free_rate;
    this->volatility = volatility;
    this->initial_stock_price = initial_stock_price;
    this->strike_price = strike_price;
    
    //the up factor and probability of the up-stay-down ways are calculated here
    up_factor = exp(volatility*sqrt(2*expiration_time/((double) no_of_divisions)));
    R = exp(risk_free_rate*expiration_time/((double) no_of_divisions));
    uptick_prob = pow((sqrt(R)-1/sqrt(up_factor))/(sqrt(up_factor)-1/sqrt(up_factor)), 2);
    downtick_prob = pow((sqrt(up_factor)-sqrt(R))/(sqrt(up_factor)-1/sqrt(up_factor)), 2);
    notick_prob = 1 - uptick_prob - downtick_prob;
}

//in display function, the pricing functions are called and all the information
//of the options is displayed here
void option_with_memoization::display()
{
    cout << "Recursive Trinomial American-Asian Option Pricing" << endl;
    cout << "Expiration Time (Years) = " << expiration_time << endl;
    cout << "Number of Divisions = " << no_of_divisions << endl;
    cout << "Risk Free Interest Rate = " << risk_free_rate << endl;
    cout << "Volatility (%age of stock value) = " << volatility*100 << endl;
    cout << "Initial Stock Price = " << initial_stock_price << endl;
    cout << "Strike Price = " << strike_price << endl;
    cout << "--------------------------------------" << endl;
    cout << "Up Factor = " << up_factor << endl;
    cout << "Uptick Probability = " << uptick_prob << endl;
    cout << "Notick Probability = " << notick_prob << endl;
    cout << "Downtick Probability = " << downtick_prob << endl;
    cout << "--------------------------------------" << endl;
    initialize();
    double call_price1 = American_call_option(0, 0, initial_stock_price);
    cout << "Trinomail Price of an American Call Option = " << call_price1 << endl;
    initialize();
    double put_price1 = American_put_option(0, 0, initial_stock_price);
    cout << "Trinomail Price of an American Put Option = " << put_price1 << endl;
    cout << "--------------------------------------" << endl;
    initialize();
    double call_price2 = European_call_option(0, 0);
    cout << "Trinomail Price of an European Call Option = " << call_price2 << endl;
    double call_price3 = option_price_call_black_scholes(initial_stock_price, strike_price, risk_free_rate, volatility, expiration_time);
    cout << "Price of an European Call Option according to B-S = " << call_price3 << endl;
    cout << "--------------------------------------" << endl;
    initialize();
    double put_price2 = European_put_option(0, 0);
    cout << "Trinomail Price of an European Put Option = " << put_price2 << endl;
    double put_price3 = option_price_put_black_scholes(initial_stock_price, strike_price, risk_free_rate, volatility, expiration_time);
    cout << "Price of an European Put Option according to B-S = " << put_price3 << endl;
    cout << "--------------------------------------" << endl;
}

//the recursive function pricing the american-asian call option
//american-asian options uses the average price to compare with the strike price
double option_with_memoization::American_call_option(int k, int i, double current_price)
{
    if (k == no_of_divisions)
        return max((double)0.0, (current_price - strike_price));
    else if(list[k][k+i] != -9999)  //before calculate, find whether this price has been calculated according to k and i
        return list[k][k+i];
    else{
        double up, stay, down;
        up = American_call_option(k+1, i+1, up_factor*current_price);
        stay = American_call_option(k+1, i, current_price);
        down = American_call_option(k+1, i-1, current_price/up_factor);
        double result = max(current_price-strike_price, (uptick_prob*up + notick_prob*stay + downtick_prob*down)/R);
        list[k][k+i] = result;
        return result;
    }
    
}

//the recursive function pricing the american-asian put option
double option_with_memoization::American_put_option(int k, int i, double current_price)
{
    if (k == no_of_divisions)
        return max((double)0.0, (strike_price - current_price));
    else if(list[k][k+i] != -9999)
        return list[k][k+i];
    else{
        double up, stay, down;
        up = American_put_option(k+1, i+1, up_factor*current_price);
        stay = American_put_option(k+1, i, current_price);
        down = American_put_option(k+1, i-1, current_price/up_factor);
        double result = max(strike_price - current_price, (uptick_prob*up + notick_prob*stay + downtick_prob*down)/R);
        list[k][k+i] = result;
        return result;
    }
}

double option_with_memoization::European_call_option(int k, int i)
{
    if (k == no_of_divisions)
        return max((double)0.0, ((initial_stock_price*pow(up_factor, ((double) i))) - strike_price));
    else if(list[k][k+i] != -9999)
        return list[k][k+i];
    else{
        double up, stay, down;
        up = European_call_option(k+1, i+1);
        stay = European_call_option(k+1, i);
        down = European_call_option(k+1, i-1);
        double result = ((uptick_prob*up + notick_prob*stay + downtick_prob*down)/R);
        list[k][k+i] = result;
        return result;
    }

}


double option_with_memoization::European_put_option(int k, int i)
{
    
    if (k == no_of_divisions)
        return max((double)0.0, (strike_price - (initial_stock_price*pow(up_factor, ((double) i)))));
    else if(list[k][k+i] != -9999){
        return list[k][k+i];
    }
    else{
        double result;
        double up, stay, down;
        up = European_put_option(k+1, i+1);
        stay = European_put_option(k+1, i);
        down = European_put_option(k+1, i-1);
        result = (uptick_prob*up + notick_prob*stay + downtick_prob*down)/R;
        list[k][k+i] = result;
        return result;
    }
}

void option_with_memoization::initialize()
{
    if (list != NULL){
        for (int i=0; i<no_of_divisions; i++)
            delete list[i];
        delete list;
    }
    list = new double* [no_of_divisions];
    for (int i=0; i<no_of_divisions; i++)
        list[i] = new double [2 * no_of_divisions + 1];
    
    for (int i=0; i<no_of_divisions; i++){
        for (int j=0; j<2*no_of_divisions+1; j++){
            list[i][j] = -9999;
        }
    }
}

option_with_memoization::~option_with_memoization()
{
    if (list != NULL){
        for (int i=0; i<no_of_divisions; i++)
            delete list[i];
        delete list;
    }
    list = new double* [no_of_divisions];
}








