# /*

g++ -Wall -ISources -I. -g -std=gnu++17 "$0" \
    tests/SimpleTestSuite.cc \
    Sources/Tydal/ErrorFormatterTerse.cc \
    Sources/Tydal/Parser.cc \
    Sources/Tydal/TokenIterator.cc \
    Sources/Tydal/Grammar/?*.cc \
    Sources/GenericParser/?*.cc \
    Sources/Tydal/Errors/?*.cc
./a.out || ./a.exe
return

# /*
 * File:   Test_CreateParser.cc
 * Author: max
 *
 * Created on 29 ottobre 2016, 11.58
 */

#include <cstdlib>
#include <iostream>
#include "Tydal/Parser.hh"
#include "Tydal/Grammar/SimpleType.hh"
/*
 * Simple C++ Test Suite
 */

#include "tests/SimpleTestSuite.hh"

void test_empty_program( TestSuite const& suite )
{
    Test test( suite, __func__ );
    auto program = Tydal::parse( "", "CreateParser_1.tydal" );
    TEST_ASSERT(test, program.begin() == program.end() );
}

void testSimpleType( TestSuite const& suite, char const* testName, char const* typeName )
{
    Test test( suite, testName );

    using namespace Tydal::Grammar;

    std::string fileName{"TypeInt_2.tydal"};
    std::string programText{ "Type i: " };
    programText.append( typeName );
    Program program = Tydal::parse( programText, fileName.c_str() );
    auto typeIter = program.begin();
    TEST_ASSERT( test, typeIter != program.end() );

    std::string name;
    std::shared_ptr<BaseType const> type;
    std::tie(name,type) = *typeIter;
    TEST_ASSERT( test, name == "i" );

    ++typeIter;
    TEST_ASSERT( test, typeIter == program.end() );

    GenericParser::ReadingPosition const& position = type->getPosition();
    TEST_ASSERT( test, position.getFileName() == fileName );
    TEST_ASSERT( test, position.getLineNumber() == 1 );
    TEST_ASSERT( test, position.getColumnNumber() == 1 );

    TEST_ASSERT( test, type->getTypeName() == typeName );
    TEST_ASSERT( test, type->isComplete() );
    TEST_ASSERT( test, !type->isPartial() );

    auto specificType = std::dynamic_pointer_cast<SimpleType const>( type );
    TEST_ASSERT( test, specificType.operator bool() );
}

void test_type_int( TestSuite const& suite )
{
    testSimpleType( suite, __func__, "Int");
}

void test_type_bool( TestSuite const& suite )
{
    testSimpleType( suite, __func__, "Bool");
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

