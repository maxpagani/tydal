/*
 * File:   Test_ParseErrors.cc
 *
 * Malformed input must be reported, never hang or escape as an exception.
 */

#include <gtest/gtest.h>
#include <sstream>
#include "Tydal/Parser.hh"
#include "Tydal/ErrorFormatterTerse.hh"

using namespace Tydal::Grammar;

namespace
{
    struct ParseResult
    {
        Program program;
        int errorCount;
        std::string messages;
    };

    ParseResult parseWithErrors( std::string const& programText )
    {
        ErrorFormatterTerse formatter;
        std::ostringstream messages;
        GenericParser::ErrorLogger logger( &formatter, messages );
        Program program = Tydal::parse( programText, "Errors.tydal", logger );
        return { program, logger.getErrorCount(), messages.str() };
    }

    void expectError( std::string const& programText,
                      std::string const& expectedMessage )
    {
        ParseResult result = parseWithErrors( programText );
        EXPECT_GT( result.errorCount, 0 );
        EXPECT_EQ( result.program.begin(), result.program.end() );
        EXPECT_NE( result.messages.find( expectedMessage ), std::string::npos )
            << "messages were: " << result.messages;
    }
}

TEST( ParseErrors, UnknownCharacters )
{
    expectError( "Point = { x: Int, y: Int }\n",
                 "1:1: error: Unexpected token: 'Point'" );
}

TEST( ParseErrors, UnknownCharacterAfterType )
{
    expectError( "Type x: Int @\nType y: Float\n",
                 "1:13: error: Unexpected token: '@'" );
}

TEST( ParseErrors, UnknownType )
{
    expectError( "Type i: int32\n", "expecting a type, found 'int32'" );
}

TEST( ParseErrors, MissingColon )
{
    expectError( "Type p: Record\n  x Int\nEnd\n", "2:5: error: expecting ':', found 'Int'" );
}

TEST( ParseErrors, InvalidEnumLabel )
{
    expectError( "Type e: Enum\n  A, B, $\nEnd\n", "expecting enum label, '$' found" );
}

TEST( ParseErrors, DuplicatedRecordField )
{
    expectError( "Type r: Record\n  a: Int\n  a: Float\nEnd\n",
                 "3:3: error: duplicated record field 'a' (previously defined at line 2)" );
}

TEST( ParseErrors, UnterminatedRecord )
{
    expectError( "Type p: Record\n  x: Int\n", "unexpected end of file" );
}

TEST( ParseErrors, UnterminatedArray )
{
    expectError( "Type a: Array[Int\n", "unexpected end of file" );
}

TEST( ParseErrors, UnterminatedString )
{
    expectError( "Type s: String(\n", "unexpected end of file" );
}

TEST( ParseErrors, RecoversAtNextType )
{
    ParseResult result = parseWithErrors( "Type a: Wrong\n"
                                          "Type b: Int\n"
                                          "Type c: AlsoWrong\n" );
    EXPECT_EQ( result.errorCount, 2 );
    EXPECT_NE( result.messages.find( "1:9: error: expecting a type, found 'Wrong'" ),
               std::string::npos );
    EXPECT_NE( result.messages.find( "3:9: error: expecting a type, found 'AlsoWrong'" ),
               std::string::npos );
}

TEST( ParseErrors, ValidProgramHasNoErrors )
{
    ParseResult result = parseWithErrors( "Type i: Int\n" );
    EXPECT_EQ( result.errorCount, 0 );
    EXPECT_NE( result.program.begin(), result.program.end() );
}
