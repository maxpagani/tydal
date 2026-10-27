/*
 * File:   Test_CreateParser.cc
 * Author: max
 *
 * Created on 29 ottobre 2016, 11.58
 */

#include <gtest/gtest.h>
#include "Tydal/Parser.hh"
#include "Tydal/Grammar/SimpleType.hh"

using namespace Tydal::Grammar;

namespace
{
    void testSimpleType( char const* typeName )
    {
        std::string fileName{"TypeInt_2.tydal"};
        std::string programText{ "Type i: " };
        programText.append( typeName );
        Program program = Tydal::parse( programText, fileName.c_str() );
        auto typeIter = program.begin();
        ASSERT_NE( typeIter, program.end() );

        std::string name;
        std::shared_ptr<BaseType const> type;
        std::tie(name,type) = *typeIter;
        EXPECT_EQ( name, "i" );

        ++typeIter;
        EXPECT_EQ( typeIter, program.end() );

        GenericParser::ReadingPosition const& position = type->getPosition();
        EXPECT_EQ( position.getFileName(), fileName );
        EXPECT_EQ( position.getLineNumber(), 1 );
        EXPECT_EQ( position.getColumnNumber(), 1 );

        EXPECT_EQ( type->getTypeName(), typeName );
        EXPECT_TRUE( type->isComplete() );
        EXPECT_FALSE( type->isPartial() );

        auto specificType = std::dynamic_pointer_cast<SimpleType const>( type );
        EXPECT_TRUE( specificType );
    }
}

TEST( CreateParser, EmptyProgram )
{
    auto program = Tydal::parse( "", "CreateParser_1.tydal" );
    EXPECT_EQ( program.begin(), program.end() );
}

TEST( CreateParser, TypeInt )
{
    testSimpleType( "Int" );
}

TEST( CreateParser, TypeBool )
{
    testSimpleType( "Bool" );
}

TEST( CreateParser, TypeFloat )
{
    testSimpleType( "Float" );
}
