/**
 * @file SimpleTestSuite.cc
 * @author Massimiliano Pagani
 *
 * @date 2016-11-05 15:59:31
 */

#include "tests/SimpleTestSuite.hh"
#include <cstring>
#include <iostream>

std::string
removeFileExtension( char const* name )
{
    char const* dot = std::strstr( name, "." );
    if( dot == nullptr )
    {
        return name;
    }
    return std::string( name, dot );
}

TestSuite::TestSuite( char const* testSuite, void (setup)() ) :
           m_suiteName{ removeFileExtension( testSuite )}
{
    std::cout << "%SUITE_STARTING% " << m_suiteName << std::endl;
    if( setup != nullptr )
    {
        setup();
    }
    std::cout << "%SUITE_STARTED%" << std::endl;
}

TestSuite::~TestSuite()
{
    std::cout << "%SUITE_FINISHED% time=0" << std::endl;
}

inline std::string const&
TestSuite::getName() const
{
    return m_suiteName;
}

Test::Test( TestSuite const& testSuite, const char* testName) :
      m_testSuite{ testSuite },
      m_testName{ testName }
{
    std::cout << "%TEST_STARTED% " << m_testName << " ("
             << testSuite.getName() << ")" << std::endl;

    std::cout << testSuite.getName() << " " << m_testName << std::endl;
}

Test::~Test()
{
    std::cout << "%TEST_FINISHED% time=0 " << m_testName << " ("
              << m_testSuite.getName() << ")" << std::endl;
}

void Test::fail( char const* message )
{
    std::cout << "%TEST_FAILED% time=0 testname=" << m_testName
              << " (" << m_testSuite.getName() << ") message="
              << message << std::endl;
}


