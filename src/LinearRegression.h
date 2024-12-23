/**
 * A class implementing a linear regression model
 *
 * Example usage:
 *  LinearRegression lr;
 *  lr.fit({1,2,3,4,5}, {1,2,3,4,5});
 *  std::cout << lr.predict(6) << std::endl; // should be 6
*/

#include <vector>

class LinearRegression
{
    private:
        // Coefficients of the linear regression model
        double b0, b1;

    public:
        LinearRegression();

        /**
         * Fit a linear regression model to the data
         * use Least Squares Estimates
         *
         * @param x vector of independent variable values
         * @param y vector of dependent variable values
        */
        void fit(const std::vector<double> &x, const std::vector<double> &y);

        /**
         * Predict the value of y for a given value of x
         *
         * @param x value of the independent variable
         *
         * @return predicted value of the dependent variable
        */
        double predict(const double &x);
};
