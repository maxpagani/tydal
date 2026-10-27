/*
 * File:   Test_ComplexTypes.cc
 * Author: max
 *
 * Created on 5 novembre 2016, 22.04
 */

#include <gtest/gtest.h>
#include "Tydal/Grammar/Program.hh"
#include "Tydal/Parser.hh"
#include "Tydal/Grammar/RecordType.hh"
#include "Tydal/Grammar/ArrayType.hh"
#include "Tydal/Grammar/EnumLabel.hh"
#include "Tydal/Grammar/EnumType.hh"
#include "Tydal/Grammar/StringType.hh"
#include "Tydal/Errors/BasicError.hh"
#include "Tydal/Grammar/VariantType.hh"
#include "Tydal/Grammar/SimpleType.hh"

using namespace Tydal::Grammar;

namespace
{
    void
    expectSimpleType( std::shared_ptr<BaseType const> ptrType,
                      SimpleType::Type type )
    {
        ASSERT_TRUE( ptrType );
        auto simpleType = std::dynamic_pointer_cast<SimpleType const>( ptrType );
        ASSERT_TRUE( simpleType );
        EXPECT_EQ( simpleType->getType(), type );
    }

    void
    expectStringType( std::shared_ptr<BaseType const> ptrType )
    {
        ASSERT_TRUE( ptrType );
        auto stringType = std::dynamic_pointer_cast<StringType const>( ptrType );
        EXPECT_TRUE( stringType );
    }
}

TEST( ComplexTypes, Multi )
{
    std::string fileName{"TypeMulti.tydal"};
    std::string programText{ "Type i: Int\n"
                             "Type f: Float\n"
                             "Type b: Boolean"};
    Program program = Tydal::parse( programText, fileName.c_str() );
    bool intFound=false;
    bool floatFound = false;
    bool boolFound = false;

    for( auto& type : program )
    {
        if( type.first == "i" )
        {
            EXPECT_FALSE( intFound );
            EXPECT_EQ( type.second->getTypeName(), "Int" );
            intFound = true;
        }
        else if( type.first == "f" )
        {
            EXPECT_FALSE( floatFound );
            EXPECT_EQ( type.second->getTypeName(), "Float" );
            floatFound = true;
        }
        else if( type.first == "b" )
        {
            EXPECT_FALSE( boolFound );
            EXPECT_EQ( type.second->getTypeName(), "Bool" );
            boolFound = true;
        }
        else
        {
            ADD_FAILURE() << "unexpected type " << type.first;
        }
    }
    EXPECT_TRUE( intFound && floatFound && boolFound );
}

TEST( ComplexTypes, RecordEmpty )
{
    std::string fileName{"TypeEmptyRecord.tydal"};
    std::string programText{ "Type record: Record\n"
                             "End" };
    Program program = Tydal::parse( programText, fileName.c_str() );
    auto iter = program.begin();
    ASSERT_NE( iter, program.end() );
    EXPECT_EQ( iter->first, "record" );
    ++iter;
    EXPECT_EQ( iter, program.end() );
}

TEST( ComplexTypes, RecordFields )
{
    std::string fileName{"TypeRecord.tydal"};
    std::string programText{ "Type record: Record\n"
                             "    a: Int\n"
                             "    b: Float\n"
                             "    c: Boolean\n"
                             "End" };
    Program program = Tydal::parse( programText, fileName.c_str() );
    auto iter = program.begin();
    ASSERT_NE( iter, program.end() );
    EXPECT_EQ( iter->first, "record" );
    auto record = std::dynamic_pointer_cast<RecordType const>( iter->second );
    ASSERT_TRUE( record );

    // and now test for the three fields

    bool intFound = false;
    bool floatFound = false;
    bool boolFound = false;

    for( auto& field: *record )
    {
        if( field.first == "a" )
        {
            EXPECT_FALSE( intFound );
            intFound = true;
            auto intField = field.second;
            EXPECT_EQ( intField->getName(), "a" );
            EXPECT_EQ( intField->getType()->getTypeName(), "Int" );
        }
        else if( field.first == "b" )
        {
            EXPECT_FALSE( floatFound );
            floatFound = true;
            auto floatField = field.second;
            EXPECT_EQ( floatField->getName(), "b" );
            EXPECT_EQ( floatField->getType()->getTypeName(), "Float" );
        }
        else if( field.first == "c" )
        {
            EXPECT_FALSE( boolFound );
            boolFound = true;
            auto boolField = field.second;
            EXPECT_EQ( boolField->getName(), "c" );
            EXPECT_EQ( boolField->getType()->getTypeName(), "Bool" );
        }
        else
        {
            ADD_FAILURE() << "unexpected field " << field.first;
        }
    }
    EXPECT_TRUE( intFound && floatFound && boolFound );
    ++iter;
    EXPECT_EQ( iter, program.end() );
}

TEST( ComplexTypes, Array )
{
    std::string fileName{"TypeArray.tydal"};
    std::string programText{ "Type array: Array[Int]" };
    Program program = Tydal::parse( programText, fileName.c_str() );
    auto iter = program.begin();
    ASSERT_NE( iter, program.end() );
    EXPECT_EQ( iter->first, "array" );
    auto array = std::dynamic_pointer_cast<ArrayType const>( iter->second );
    ASSERT_TRUE( array );
    EXPECT_EQ( array->getItemType()->getTypeName(), "Int" );
    ++iter;
    EXPECT_EQ( iter, program.end() );
}

TEST( ComplexTypes, Enum )
{
    std::string fileName{"TypeEnum.tydal"};
    std::string programText{ "Type enum: Enum\n"
                             "    FOO\n"
                             "    BAR\n"
                             "    BAZ\n"
                             "End" };
    Program program = Tydal::parse( programText, fileName.c_str() );
    auto iter = program.begin();
    ASSERT_NE( iter, program.end() );
    EXPECT_EQ( iter->first, "enum" );
    auto enumPtr = std::dynamic_pointer_cast<EnumType const>( iter->second );
    ASSERT_TRUE( enumPtr );

    // and now test for the three labels

    bool fooFound = false;
    bool barFound = false;
    bool bazFound = false;

    for( auto& label: *enumPtr )
    {
        if( label.getLabelName() == "FOO" )
        {
            EXPECT_FALSE( fooFound );
            fooFound = true;
        }
        else if( label.getLabelName() == "BAR" )
        {
            EXPECT_FALSE( barFound );
            barFound = true;
        }
        else if( label.getLabelName() == "BAZ" )
        {
            EXPECT_FALSE( bazFound );
            bazFound = true;
        }
        else
        {
            ADD_FAILURE() << "unexpected label " << label.getLabelName();
        }
    }
    EXPECT_TRUE( fooFound && barFound && bazFound );
    ++iter;
    EXPECT_EQ( iter, program.end() );
}

TEST( ComplexTypes, String )
{
    std::string fileName{"TypeString.tydal"};
    std::string programText{ "Type simple: String\n"
                             "Type complex: String(Template)" };
    Program program = Tydal::parse( programText, fileName.c_str() );
    auto iter = program.begin();
    ASSERT_NE( iter, program.end() );
    EXPECT_EQ( iter->first, "simple" );
    auto stringPtr = std::dynamic_pointer_cast<StringType const>( iter->second );
    ASSERT_TRUE( stringPtr );
    EXPECT_EQ( stringPtr->getSpecification(), "" );
    ++iter;
    ASSERT_NE( iter, program.end() );
    stringPtr = std::dynamic_pointer_cast<StringType const>( iter->second );
    ASSERT_TRUE( stringPtr );
    EXPECT_EQ( stringPtr->getSpecification(), "Template" );
    ++iter;
    EXPECT_EQ( iter, program.end() );
}

TEST( ComplexTypes, Variant )
{
    std::string programText{
        "Type simple: Record\n"
        "    Variant a : String\n"
        "        Case \"ABC\" :\n"
        "            b : Int\n"
        "        Case \"DEF\" :\n"
        "            c : String\n"
        "            d : Int\n"
        "    End\n"
        "End"};
    Program program = Tydal::parse( programText, "Variant.tydal" );
    auto iter = program.begin();
    ASSERT_NE( iter, program.end() );
    EXPECT_EQ( iter->first, "simple" );
    auto record = std::dynamic_pointer_cast<RecordType const>( iter->second );
    ASSERT_TRUE( record );
    ++iter;
    EXPECT_EQ( iter, program.end() );
    auto field = record->begin();
    ASSERT_NE( field, record->end() );
    EXPECT_EQ( field->first, "a" );
    auto variant = std::dynamic_pointer_cast<VariantType const>( field->second->getType() );
    ASSERT_TRUE( variant );
    auto type = std::dynamic_pointer_cast<StringType const>(variant->getFieldType());
    EXPECT_TRUE( type );
    ++field;
    EXPECT_EQ( field, record->end() );
    auto entry = variant->begin();
    ASSERT_NE( entry, variant->end() );
    EXPECT_EQ( (*entry)->getCaseValue(), "\"ABC\"" );
    auto abcField = (*entry)->begin();
    ASSERT_NE( abcField, (*entry)->end() );
    EXPECT_EQ( abcField->first, "b" );
    expectSimpleType( abcField->second->getType(), SimpleType::INT );
    ++abcField;
    EXPECT_EQ( abcField, (*entry)->end() );
    ++entry;
    ASSERT_NE( entry, variant->end() );
    EXPECT_EQ( (*entry)->getCaseValue(), "\"DEF\"" );
    auto defField = (*entry)->begin();
    ASSERT_NE( defField, (*entry)->end() );
    EXPECT_EQ( defField->first, "c" );
    expectStringType( defField->second->getType() );
    ++defField;
    ASSERT_NE( defField, (*entry)->end() );
    EXPECT_EQ( defField->first, "d" );
    expectSimpleType( defField->second->getType(), SimpleType::INT );
    ++defField;
    EXPECT_EQ( defField, (*entry)->end() );
    ++entry;
    EXPECT_EQ( entry, variant->end() );
}

/* Errors to check:
 *
 * Record has duplicated field 'a'
 *
 *         std::string programText{
            "Type simple: Record\n"
            "    Variant a : String\n"
            "        Case \"ABC\" :\n"
            "            a : Int\n"
            "        Case \"DEF\" :\n"
            "            b : String\n"
            "            c : Int\n"
            "    End\n"
            "End"};
*/
