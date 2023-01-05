/**
 * @brief A class implementing a linear regression model
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
         * @brief Fit a linear regression model to the data
        */
        void fit(const std::vector<double> &x, const std::vector<double> &y);

        /**
         * @brief Predict the value of y for a given value of x
        */
        double predict(const double &x);
};
