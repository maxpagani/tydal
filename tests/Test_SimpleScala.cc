# /*

g++ -Wall -ISources -I. -g -std=gnu++17 "$0" \
    tests/SimpleTestSuite.cc \
    Sources/Tydal/ErrorFormatterTerse.cc \
    Sources/Tydal/Parser.cc \
    Sources/Tydal/TokenIterator.cc \
    Sources/Tydal/Grammar/?*.cc \
    Sources/GenericParser/?*.cc \
    Sources/Tydal/Errors/?*.cc \
    Sources/OutputTranslator/Base.cc \
    Sources/OutputTranslator/Scala.cc
./a.out || ./a.exe
return
*/
/**
 * File:   Test_SimpleScala.cc
 * Author: max
 *
 * Created on 08 November 2016, 22:39
 */

#include <cstdlib>
#include <iostream>
#include "Tydal/Parser.hh"
#include "Tydal/Grammar/SimpleType.hh"
#include "OutputTranslator/Scala.hh"
/*
 * Simple C++ Test Suite
 */

#include "tests/SimpleTestSuite.hh"

void test_empty_program( TestSuite const& suite )
{
    Test test( suite, __func__ );
    auto program = Tydal::parse( "", "CreateParser_1.tydal" );
    TEST_ASSERT(test, program.begin() == program.end() );
    OutputTranslator::Scala scala;
    std::ostringstream out;
    scala.print( program, out );
    TEST_ASSERT( test, out.str() == "" );
}

void testSimpleType( TestSuite const& suite, char const* testName, char const* typeName )
{
    Test test( suite, testName );

    using namespace Tydal::Grammar;

    std::string fileName{"TypeInt_2.tydal"};
    std::string programText{ "Type i: " };
    programText.append( typeName );
    Program program = Tydal::parse( programText, fileName.c_str() );

    OutputTranslator::Scala scala;
    std::ostringstream out;
    scala.print( program, out );
    TEST_ASSERT( test, out.str() == std::string("type i = ")+typeName );
}

void test_type_int( TestSuite const& suite )
{
    testSimpleType( suite, __func__, "Int");
}

void test_type_bool( TestSuite const& suite )
{
    testSimpleType( suite, __func__, "Boolean");
}

void test_type_float( TestSuite const& suite )
{
    testSimpleType( suite, __func__, "Float");
}

int main(int argc, char** argv)
{
    TestSuite suite( __FILE__ );

    test_empty_program( suite );
    test_type_int( suite );
    test_type_bool( suite );
    test_type_float( suite );

    return EXIT_SUCCESS;
}

