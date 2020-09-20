//
//  main.cpp
//  Polyfit
//
//  Created by Patrick Löber on 23.11.18.
//  Copyright © 2018 Patrick Loeber. All rights reserved.
//

#include <iostream>
#include "PolyfitBoost.hpp"

int main(int argc, const char * argv[]) {

    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> weights;
    
    for (int i = 0; i <= 5; ++i)
    {
        x.push_back(double(i));
        weights.push_back(i*i);
    }

    y.push_back(0.0);
    y.push_back(0.8);
    y.push_back(0.9);
    y.push_back(0.1);
    y.push_back(-0.8);
    y.push_back(-0.1);
    
    std::cout << "Testing Polyfit With Boost...\n";
    std::vector<double> coeff = polyfit_boost(x, y, 3);
    std::vector<double> coeffWeighted = polyfit_boost(x, y, 3, weights);
    
    std::cout << "Coefficients:\n";
    for (auto it = coeff.begin(); it != coeff.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\nCoefficients weighted:\n";
    for (auto it = coeffWeighted.begin(); it != coeffWeighted.end(); ++it)
        std::cout << *it << " ";
    
    std::vector<double> testValuesX(x);
    
    std::cout << "\nFitted y Values:\n";
    std::vector<double> testValuesY = polyval(coeff, testValuesX);
    for (auto it = testValuesY.begin(); it != testValuesY.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n\n";
    
    return 0;
}
