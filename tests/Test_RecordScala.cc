/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Test_RecordScala.cc
 * Author: max
 *
 * Created on 09 November 2016, 22:39
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

void test_simple_record( TestSuite const& suite )
{
    Test test( suite, __func__ );
    auto program = Tydal::parse( "Type simple : Record\n"
                                 "    a: Int\n"
                                 "    b: Float\n"
                                 "    opt c: String\n"
                                 "End",
                                 "CreateParser_1.tydal" );
    TEST_ASSERT(test, program.begin() != program.end() );
    OutputTranslator::Scala scala;
    std::ostringstream out;
    scala.print( program, out );
    TEST_ASSERT( test, out.str() == "case class simple (\n"
            "    a: Int,\n"
            "    b: Float,\n"
            "    c: Option[String]\n"
            ")\n");
}

void test_record_in_record( TestSuite const& suite )
{
    Test test( suite, __func__ );
    auto program = Tydal::parse(
        "Type simple : Record\n"
        "    a: Int\n"
        "    b: Float\n"
        "    opt c: Record\n"
        "        a: String\n"
        "        b: Boolean\n"
        "    End\n"
        "End",
    "CreateParser_1.tydal" );

    TEST_ASSERT(test, program.begin() != program.end() );
    OutputTranslator::Scala scala;
    std::ostringstream out;
    scala.print( program, out );
    TEST_ASSERT( test, out.str() ==
        "case class simple(\n"
        "    a: Int,\n"
        "    b: Float,\n"
        "    c: Option[{\n"
        "        val a : String\n"
        "        val b : Boolean\n"
        "    }]\n"
        ")"
    );
}

void test_variant( TestSuite const& suite )
{
    Test test( suite, __func__ );
    auto program = Tydal::parse(
        "Type simple: Record\n"
        "    c1: Int\n"
        "    c2: String\n"
        "    c3: Record\n"
        "        aa: Int\n"
        "        bb: Bool\n"
        "    End\n"
        "    Variant a : String\n"
        "        Case \"ABC\" :\n"
        "            b : Int\n"
        "        Case \"DEF\" :\n"
        "            c : String\n"
        "            d : Int\n"
        "    End\n"
        "End",
        "CreateParser_2.tydal"
    );
    TEST_ASSERT(test, program.begin() != program.end() );
    OutputTranslator::Scala scala;
    std::ostringstream out;
    scala.print( program, out );
    std::cout << out.str() << "\n";

}

int main(int argc, char** argv)
{
    TestSuite suite( __FILE__ );

    test_simple_record( suite );
    test_record_in_record( suite );
    test_variant( suite );

    return EXIT_SUCCESS;
}

