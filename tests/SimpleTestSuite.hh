/**
 * @file SimpleTestSuite.hh
 * @author Massimiliano Pagani
 *
 * @date 2016-11-05 15:59:31
 */

#if !defined( SIMPLE_TEST_SUITE_HH )
#define SIMPLE_TEST_SUITE_HH

#include <string>

class TestSuite
{
    public:
        TestSuite( char const* testSuite, void (setup)() = nullptr );
        ~TestSuite();

        std::string const& getName() const;
    private:
      std::string m_suiteName;
};

class Test
{
    public:
        Test( TestSuite const& suite, char const* testName );
        ~Test();
        void fail( char const* message );
    private:
        TestSuite const& m_testSuite;
        std::string m_testName;
};

#define TEST_STRING_OF( L ) #L

#define TEST_ASSERT_IMPL( T, C, L )       \
    while( !(C) )                                \
    {                                            \
        T.fail( #C " (line: " TEST_STRING_OF( L ) ")"); \
        break;                                   \
    }

#define TEST_ASSERT( T, C )                   \
    TEST_ASSERT_IMPL( T, C, __LINE__ )



#endif /* SIMPLE_TEST_SUITE_HH */

