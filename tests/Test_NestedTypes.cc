/*
 * File:   Test_NestedTypes.cc
 * Author: max
 *
 * Created on 6 novembre 2016, 22.18
 */

#include <gtest/gtest.h>
#include "Tydal/Parser.hh"
#include "Tydal/Grammar/SimpleType.hh"
#include "Tydal/Grammar/ArrayType.hh"
#include "Tydal/Grammar/RecordType.hh"

using namespace Tydal::Grammar;

TEST( NestedTypes, ArrayOfRecords )
{
    std::string fileName{"TypeNested_1.tydal"};
    std::string programText{ "Type ar: Array[Record\n"
                             "  a : Int\n"
                             "  b : Float\n"
                             "End]"};
    Program program = Tydal::parse( programText, fileName.c_str() );
    auto typeIter = program.begin();
    ASSERT_NE( typeIter, program.end() );

    std::string name;
    std::shared_ptr<BaseType const> type;
    std::tie(name,type) = *typeIter;
    EXPECT_EQ( name, "ar" );
    ++typeIter;
    EXPECT_EQ( typeIter, program.end() );

    auto array = std::dynamic_pointer_cast<ArrayType const>(type);
    ASSERT_TRUE( array );
    auto record = std::dynamic_pointer_cast<RecordType const>(array->getItemType());
    ASSERT_TRUE( record );

    bool aFound = false;
    bool bFound = false;
    for( auto& field : *record )
    {
        if( field.first == "a" )
        {
            EXPECT_FALSE( aFound );
            aFound = true;
            EXPECT_EQ( field.second->getType()->getTypeName(), "Int" );
        }
        else if( field.first == "b")
        {
            EXPECT_FALSE( bFound );
            bFound = true;
            EXPECT_EQ( field.second->getType()->getTypeName(), "Float" );
        }
        else
        {
            ADD_FAILURE() << "unexpected field " << field.first;
        }
    }
    EXPECT_TRUE( aFound && bFound );
}

TEST( NestedTypes, RecordWithRecord )
{
    GTEST_SKIP() << "not implemented";
}

TEST( NestedTypes, RecordWithArray )
{
    GTEST_SKIP() << "not implemented";
}

TEST( NestedTypes, RecordWithEnum )
{
    GTEST_SKIP() << "not implemented";
}

TEST( NestedTypes, StringWithEnum )
{
    std::string fileName{"TypeNested_5.tydal"};
    std::string programText{ "Type str: String(Enum\n"
                             "  FOO\n"
                             "  BAR\n"
                             "End)"};
    Program program = Tydal::parse( programText, fileName.c_str() );
    auto typeIter = program.begin();
    EXPECT_NE( typeIter, program.end() );
}
