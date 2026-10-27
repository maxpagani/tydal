#include <gtest/gtest.h>
#include <sstream>
#include "Tydal/Parser.hh"
#include "Tydal/Grammar/SimpleType.hh"
#include "OutputTranslator/Scala.hh"

TEST( RecordScala, SimpleRecord )
{
    auto program = Tydal::parse( "Type simple : Record\n"
                                 "    a: Int\n"
                                 "    b: Float\n"
                                 "    opt c: String\n"
                                 "End",
                                 "CreateParser_1.tydal" );
    ASSERT_NE( program.begin(), program.end() );
    OutputTranslator::Scala scala;
    std::ostringstream out;
    scala.print( program, out );
    EXPECT_EQ( out.str(), "case class simple (\n"
            "    a: Int,\n"
            "    b: Float,\n"
            "    c: Option[String]\n"
            ")\n");
}

TEST( RecordScala, RecordInRecord )
{
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

    ASSERT_NE( program.begin(), program.end() );
    OutputTranslator::Scala scala;
    std::ostringstream out;
    scala.print( program, out );
    EXPECT_EQ( out.str(),
        "case class simple (\n"
        "    a: Int,\n"
        "    b: Float,\n"
        "    c: Option[{\n"
        "        val a : String\n"
        "        val b : Boolean\n"
        "    }]\n"
        ")\n"
    );
}

TEST( RecordScala, Variant )
{
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
    ASSERT_NE( program.begin(), program.end() );
    OutputTranslator::Scala scala;
    std::ostringstream out;
    scala.print( program, out );
    EXPECT_EQ( out.str(),
            "sealed trait simple_a\n"
            "\n"
            "case class simple_a_ABC(\n"
            "    b: Int\n"
            ") extends simple_a\n"
            "case class simple_a_DEF(\n"
            "    c: String,     d: Int\n"
            ") extends simple_a\n"
            "case class simple (\n"
            "    a: String,\n"
            "    a_cases: simple_a,\n"
            "    c1: Int,\n"
            "    c2: String,\n"
            "    c3: {\n"
            "        val aa : Int\n"
            "        val bb : Boolean\n"
            "    }\n"
            ")\n"
    );
}
