/**
 * This test created in order to access the performance of CSV parsing using
 * the original tokenization method CSVReader::tokenise() provided by the course.
*/

#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE AdvisorbotTests
#endif

#include <boost/test/unit_test.hpp>

#include <fstream>
#include <boost/algorithm/string.hpp>

#include <CSVReader.h>
#include <OrderBookEntry.h>



BOOST_AUTO_TEST_SUITE(csv_reader_test_suite)

    BOOST_AUTO_TEST_CASE(read_big_csv_file_test)
    {
        std::vector<OrderBookEntry> entries;
        std::ifstream csvFile{"20200601.csv"};
        std::string line;

        while(std::getline(csvFile, line))
        {
            OrderBookEntry obe = CSVReader::stringsToOBE(CSVReader::tokenise(line, ','));

            entries.push_back(obe);
        }

        BOOST_CHECK_EQUAL(entries[0].timestamp, "2020/06/01 11:57:30.328127");
    }

BOOST_AUTO_TEST_SUITE_END()
