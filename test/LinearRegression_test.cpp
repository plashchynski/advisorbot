/**
 * This test created in order to access the performance of CSV parsing using
 * the original tokenization method CSVReader::tokenise() provided by the course.
*/

#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE AdvisorbotTests
#endif

#include <boost/test/unit_test.hpp>

#include <LinearRegression.h>

BOOST_AUTO_TEST_SUITE(linear_regression_test_suite)

    BOOST_AUTO_TEST_CASE(simple_line)
    {
        LinearRegression lr;
        lr.fit({1,2,3,4,5}, {1,2,3,4,5});

        BOOST_CHECK_EQUAL(lr.predict(6), 6);
    }

    BOOST_AUTO_TEST_CASE(input_vectors_different_size_exception)
    {
        LinearRegression lr;
        BOOST_CHECK_THROW(lr.fit({1,2,3}, {1,2}), std::invalid_argument);
    }

    BOOST_AUTO_TEST_CASE(at_least_one_data_point_exception)
    {
        LinearRegression lr;
        BOOST_CHECK_THROW(lr.fit({}, {}), std::invalid_argument);
    }

    BOOST_AUTO_TEST_CASE(one_data_point_handling)
    {
        LinearRegression lr;
        lr.fit({16}, {16});
        BOOST_CHECK_EQUAL(lr.predict(99), 16);
    }

BOOST_AUTO_TEST_SUITE_END()
