/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Test_NestedTypes.cc
 * Author: max
 *
 * Created on 6 novembre 2016, 22.18
 */

#include <stdlib.h>
#include <iostream>
#include "tests/SimpleTestSuite.hh"
#include "Tydal/Parser.hh"
#include "Tydal/Grammar/SimpleType.hh"
#include "Tydal/Grammar/ArrayType.hh"
#include "Tydal/Grammar/RecordType.hh"

using namespace Tydal::Grammar;

void test_array_of_records( TestSuite const& suite )
{
    Test test( suite, __func__ );

    std::string fileName{"TypeNested_1.tydal"};
    std::string programText{ "Type ar: Array[Record\n"
                             "  a : Int\n"
                             "  b : Float\n"
                             "End]"};
    Program program = Tydal::parse( programText, fileName.c_str() );
    auto typeIter = program.begin();
    TEST_ASSERT( test, typeIter != program.end() );

    std::string name;
    std::shared_ptr<BaseType const> type;
    std::tie(name,type) = *typeIter;
    TEST_ASSERT( test, name == "ar" );
    ++typeIter;
    TEST_ASSERT( test, typeIter == program.end() );

    auto array = std::dynamic_pointer_cast<ArrayType const>(type);
    TEST_ASSERT( test, array.operator bool());
    auto record = std::dynamic_pointer_cast<RecordType const>(array->getItemType());
    TEST_ASSERT( test, record.operator bool());

    bool aFound = false;
    bool bFound = false;
    for( auto& field : *record )
    {
        if( field.first == "a" )
        {
            TEST_ASSERT( test, !aFound );
            aFound = true;
            TEST_ASSERT( test, field.second->getType()->getTypeName() == "Int");
        }
        else if( field.first == "b")
        {
            TEST_ASSERT( test, !bFound );
            bFound = true;
            TEST_ASSERT( test, field.second->getType()->getTypeName() == "Float");
        }
        else
        {
            TEST_ASSERT( test, false );
        }
    }
    TEST_ASSERT( test, aFound && bFound );
}

void
test_record_with_record(TestSuite const& suite)
{

}

void
test_record_with_array(TestSuite const& suite)
{

}

void
test_record_with_enum(TestSuite const& suite)
{

}

void
test_string_with_enum(TestSuite const& suite)
{
    Test test( suite, __func__ );

    std::string fileName{"TypeNested_5.tydal"};
    std::string programText{ "Type str: String(Enum\n"
                             "  FOO\n"
                             "  BAR\n"
                             "End)"};
    Program program = Tydal::parse( programText, fileName.c_str() );
    auto typeIter = program.begin();
    TEST_ASSERT( test, typeIter != program.end() );
}


int main(int argc, char** argv)
{
    TestSuite suite( __FILE__ );

    test_array_of_records( suite );
    test_record_with_record(suite);
    test_record_with_array(suite);
    test_record_with_enum(suite);
    test_string_with_enum(suite);

    return EXIT_SUCCESS;
}

