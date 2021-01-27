//
//  main.cpp
//  Polyfit
//
//  Created by Patrick Löber on 23.11.18.
//  Copyright © 2018 Patrick Loeber. All rights reserved.
//

#include <iostream>
#include "PolyfitBoost.hpp"
#include "PolyfitEigen.hpp"

int main(int argc, const char * argv[]) {

    std::cout << "Testing Polyfit With Boost...\n";
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
    
    std::vector<double> coeffJacobi = polyfit_Eigen(x, y, 3);
    std::vector<double> coeffHouseholder = polyfit_Eigen(x, y, 3, std::vector<double>(), false );
    
    std::cout << "Testing Polyfit With Eigen lib...\n";
    std::cout << "Coefficients Jacobi Method:\n";
    for (auto it = coeffJacobi.begin(); it != coeffJacobi.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\nFitted y Values:\n";
    std::vector<double> testValuesYJacobi = polyval(coeffJacobi, testValuesX);
    for (auto it = testValuesYJacobi.begin(); it != testValuesYJacobi.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n\n";
    
    std::cout << "Coefficients Householder Method:\n";
    for (auto it = coeffHouseholder.begin(); it != coeffHouseholder.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\nFitted y Values:\n";
    std::vector<double> testValuesYHouseholder = polyval(coeffHouseholder, testValuesX);
    for (auto it = testValuesYHouseholder.begin(); it != testValuesYHouseholder.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n\n";
    
    return 0;
}
