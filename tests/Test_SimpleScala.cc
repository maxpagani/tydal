/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Test_SimpleScala.cc
 * Author: max
 *
 * Created on 08 November 2016, 22:39
 */

#include <stdlib.h>
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
    std::cout << out.str() << '\n';
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
/*
    std::cout << "%TEST_STARTED% test2 (Test_CreateParser)\n" << std::endl;
    test2();
    std::cout << "%TEST_FINISHED% time=0 test2 (Test_CreateParser)" << std::endl;
*/

    return EXIT_SUCCESS;
}

