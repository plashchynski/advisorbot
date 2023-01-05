#include "LinearRegression.h"
#include <numeric>
#include <valarray>

LinearRegression::LinearRegression()
{
    // Initialize the coefficients to zero
    b0 = 0;
    b1 = 0;
}

/**
 * Predict the value of y for a given value of x
 */ 
double LinearRegression::predict(const double &x)
{
    return b0 + b1 * x;
}

/**
 * Fit a linear regression model to the data
 * use Least Squares Estimates
 * Math description: https://www.amherst.edu/system/files/media/1287/SLR_Leastsquares.pdf
 */
void LinearRegression::fit(const std::vector<double> &x, const std::vector<double> &y)
{
    // Convert to valarray to optimize performance by utilizing SIMD
    std::valarray<double> x_vec(x.data(), x.size());
    std::valarray<double> y_vec(x.data(), x.size());

    double x_mean = x_vec.sum() / x_vec.size();
    double y_mean = y_vec.sum() / y_vec.size();

    b1 = ((x_vec - x_mean) * (y_vec - y_mean)).sum() / std::pow(x_vec - x_mean, 2).sum();
    b0 = y_mean - b1 * x_mean;
}
