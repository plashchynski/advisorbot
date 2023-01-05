/**
 * This test created in order to access the performance of CSV parsing
 * using boost::tokenizer.
*/

#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE AdvisorbotTests
#endif

#include <boost/test/unit_test.hpp>

#include <fstream>
#include <boost/tokenizer.hpp>

#include <CSVReader.h>
#include <OrderBookEntry.h>

typedef boost::tokenizer< boost::escaped_list_separator<char> > Tokenizer;

BOOST_AUTO_TEST_SUITE(csv_reader_with_boost_tokenizer_test_suite)

    BOOST_AUTO_TEST_CASE(read_big_csv_file_test)
    {
        std::vector<OrderBookEntry> entries;
        std::ifstream csvFile{"20200601.csv"};
        std::string line;

        while(std::getline(csvFile, line))
        {
            Tokenizer tok(line);
            std::vector<std::string> tokens(tok.begin(), tok.end());

            OrderBookEntry obe = CSVReader::stringsToOBE(tokens);

            entries.push_back(obe);
        }

        BOOST_CHECK_EQUAL(entries[0].timestamp, "2020/06/01 11:57:30.328127");
    }

BOOST_AUTO_TEST_SUITE_END()
