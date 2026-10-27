/**
 * File:   Test_SimpleScala.cc
 * Author: max
 *
 * Created on 08 November 2016, 22:39
 */

#include <gtest/gtest.h>
#include <sstream>
#include "Tydal/Parser.hh"
#include "Tydal/Grammar/SimpleType.hh"
#include "OutputTranslator/Scala.hh"

namespace
{
    void testSimpleType( char const* typeName )
    {
        std::string fileName{"TypeInt_2.tydal"};
        std::string programText{ "Type i: " };
        programText.append( typeName );
        Tydal::Grammar::Program program = Tydal::parse( programText, fileName.c_str() );

        OutputTranslator::Scala scala;
        std::ostringstream out;
        scala.print( program, out );
        EXPECT_EQ( out.str(), std::string("type i = ")+typeName+"\n" );
    }
}

TEST( SimpleScala, EmptyProgram )
{
    auto program = Tydal::parse( "", "CreateParser_1.tydal" );
    EXPECT_EQ( program.begin(), program.end() );
    OutputTranslator::Scala scala;
    std::ostringstream out;
    scala.print( program, out );
    EXPECT_EQ( out.str(), "" );
}

TEST( SimpleScala, TypeInt )
{
    testSimpleType( "Int" );
}

TEST( SimpleScala, TypeBool )
{
    testSimpleType( "Boolean" );
}

TEST( SimpleScala, TypeFloat )
{
    testSimpleType( "Float" );
}
