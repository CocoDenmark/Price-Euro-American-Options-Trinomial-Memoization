//
//  BS.h
//  The b-s method to calculate price for european option is realized in this head file.
//  Assignment10
//
//  Created by miao on 11/19/14.
//  Copyright (c) 2014 miao. All rights reserved.
//

#ifndef Assignment10_BS_h
#define Assignment10_BS_h

double N(double z) {
    if (z > 6.0) { return 1.0; }; // this guards against overflow
    if (z < -6.0) { return 0.0; };
    double b1 = 0.31938153;
    double b2 = -0.356563782;
    double b3 = 1.781477937;
    double b4 = -1.821255978;
    double b5 = 1.330274429;
    double p = 0.2316419;
    double c2 = 0.3989423;
    double a=fabs(z);
    double t = 1.0/(1.0+a*p);
    double b = c2*exp((-z)*(z/2.0));
    double n = ((((b5*t+b4)*t+b3)*t+b2)*t+b1)*t;
    n = 1.0-b*n;
    if ( z < 0.0 ) n = 1.0 - n;
    return n;
}


double option_price_put_black_scholes(double S,      // spot price
                                      double K,      // Strike (exercise) price,
                                      double r,      // interest rate
                                      double sigma,  // volatility
                                      double time){
    double time_sqrt = sqrt(time);
    double d1 = (log(S/K)+r*time)/(sigma*time_sqrt) + 0.5*sigma*time_sqrt;
    double d2 = d1-(sigma*time_sqrt);
    return K*exp(-r*time)*N(-1*d2) - S*N(-1*d1);
}

double option_price_call_black_scholes(double S,       // spot (underlying) price
                                       double K,       // strike (exercise) price,
                                       double r,       // interest rate
                                       double sigma,   // volatility
                                       double time) {  // time to maturity
    double time_sqrt = sqrt(time);
    double d1 = (log(S/K)+r*time)/(sigma*time_sqrt)+0.5*sigma*time_sqrt; 
    double d2 = d1-(sigma*time_sqrt);
    return S*N(d1) - K*exp(-r*time)*N(d2);
}


#endif
