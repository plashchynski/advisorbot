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
 * Fit a linear regression model to the data using Least Squares Estimates.
 * Math description: https://www.amherst.edu/system/files/media/1287/SLR_Leastsquares.pdf
 *
 * This method was originally proposed in:
 * Im, Eric Iksoon, A Note On Derivation of the Least Squares Estimator, Working Paper Series
 *      No. 96-11, University of Hawai’i at Manoa Department of Economics, 1996.
 */
void LinearRegression::fit(const std::vector<double> &x, const std::vector<double> &y)
{
    // Check that the input vectors have the same size
    if (x.size() != y.size())
    {
        throw std::invalid_argument("Input vectors must have the same size");
        return;
    }

    if (x.size() == 0)
    {
        throw std::invalid_argument("We need at least one data point to fit the model");
        return;
    }

    if (x.size() == 1)
    {
        /**
         * If we have only one data point, we can't fit a line
         * so we simply set the coefficient to the value of the data point
         * */
        b0 = y[0];
        b1 = 0;
        return;
    }

    // Convert to valarray to optimize performance by utilizing SIMD
    std::valarray<double> x_vec(x.data(), x.size());
    std::valarray<double> y_vec(y.data(), y.size());

    // Mean values of X and Y
    double x_mean = x_vec.sum() / x_vec.size();
    double y_mean = y_vec.sum() / y_vec.size();

    // Calculate the coefficients
    b1 = ((x_vec - x_mean) * (y_vec - y_mean)).sum() / std::pow(x_vec - x_mean, 2).sum();
    b0 = y_mean - b1 * x_mean;
}
