/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Test_ComplexTypes.cc
 * Author: max
 *
 * Created on 5 novembre 2016, 22.04
 */

#include "tests/SimpleTestSuite.hh"
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

/*
 * Simple C++ Test Suite
 */

using namespace Tydal::Grammar;

namespace
{
    void test_multi( TestSuite const& suite )
    {
        Test test(suite,__func__);

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
                TEST_ASSERT(test, !intFound);
                TEST_ASSERT(test, type.second->getTypeName() == "Int" );
                intFound = true;
            }
            else if( type.first == "f" )
            {
                TEST_ASSERT(test, !floatFound);
                TEST_ASSERT(test, type.second->getTypeName() == "Float" );
                floatFound = true;

            }
            else if( type.first == "b" )
            {
                TEST_ASSERT(test,!boolFound);
                TEST_ASSERT(test, type.second->getTypeName() == "Bool" );
                boolFound = true;
            }
            else
            {
                TEST_ASSERT(test, false);
            }
        }
        TEST_ASSERT(test, intFound && floatFound && boolFound );
    }

    void test_record_empty( TestSuite const& suite )
    {
        Test test(suite,__func__);

        std::string fileName{"TypeEmptyRecord.tydal"};
        std::string programText{ "Type record: Record\n"
                                 "End" };
        Program program = Tydal::parse( programText, fileName.c_str() );
        auto iter = program.begin();
        TEST_ASSERT(test,iter != program.end() );

        TEST_ASSERT( test, iter->first == "record" );


        ++iter;
        TEST_ASSERT( test, iter == program.end() );
    }

    void test_record_fields( TestSuite const& suite )
    {
        Test test(suite,__func__);

        std::string fileName{"TypeRecord.tydal"};
        std::string programText{ "Type record: Record\n"
                                 "    a: Int\n"
                                 "    b: Float\n"
                                 "    c: Boolean\n"
                                 "End" };
        Program program = Tydal::parse( programText, fileName.c_str() );
        auto iter = program.begin();
        TEST_ASSERT(test,iter != program.end() );
        TEST_ASSERT( test, iter->first == "record" );
        auto record = std::dynamic_pointer_cast<RecordType const>( iter->second );
        TEST_ASSERT( test, record.operator bool() );

        // and now test for the three fields

        bool intFound = false;
        bool floatFound = false;
        bool boolFound = false;

        for( auto& field: *record )
        {
            if( field.first == "a" )
            {
                TEST_ASSERT( test, !intFound );
                intFound = true;
                auto intField = field.second;
                TEST_ASSERT( test, intField->getName() == "a" );
                TEST_ASSERT( test, intField->getType()->getTypeName() == "Int" );
            }
            else if( field.first == "b" )
            {
                TEST_ASSERT( test, !floatFound );
                floatFound = true;
                auto floatField = field.second;
                TEST_ASSERT( test, floatField->getName() == "b" );
                TEST_ASSERT( test, floatField->getType()->getTypeName() == "Float" );
            }
            else if( field.first == "c" )
            {
                TEST_ASSERT( test, !boolFound );
                boolFound = true;
                auto boolField = field.second;
                TEST_ASSERT( test, boolField->getName() == "c" );
                TEST_ASSERT( test, boolField->getType()->getTypeName() == "Bool" );
            }
            else
            {
                TEST_ASSERT(test,false);
            }
        }
        TEST_ASSERT( test, intFound && floatFound && boolFound );
        ++iter;
        TEST_ASSERT( test, iter == program.end() );
    }


    void test_array( TestSuite const& suite )
    {
        Test test(suite,__func__);

        std::string fileName{"TypeArray.tydal"};
        std::string programText{ "Type array: Array[Int]" };
        Program program = Tydal::parse( programText, fileName.c_str() );
        auto iter = program.begin();
        TEST_ASSERT(test,iter != program.end() );
        TEST_ASSERT( test, iter->first == "array" );
        auto array = std::dynamic_pointer_cast<ArrayType const>( iter->second );
        TEST_ASSERT( test, array.operator bool() );
        TEST_ASSERT( test, array->getItemType()->getTypeName() == "Int" );
        ++iter;
        TEST_ASSERT( test, iter == program.end() );
    }

    void test_enum( TestSuite const& suite )
    {
        Test test(suite,__func__);

        std::string fileName{"TypeEnum.tydal"};
        std::string programText{ "Type enum: Enum\n"
                                 "    FOO\n"
                                 "    BAR\n"
                                 "    BAZ\n"
                                 "End" };
        Program program = Tydal::parse( programText, fileName.c_str() );
        auto iter = program.begin();
        TEST_ASSERT(test,iter != program.end() );
        TEST_ASSERT( test, iter->first == "enum" );
        auto enumPtr = std::dynamic_pointer_cast<EnumType const>( iter->second );
        TEST_ASSERT( test, enumPtr.operator bool() );

        // and now test for the three fields

        bool fooFound = false;
        bool barFound = false;
        bool bazFound = false;

        for( auto& label: *enumPtr )
        {
            if( label.getLabelName() == "FOO" )
            {
                TEST_ASSERT( test, !fooFound );
                fooFound = true;
            }
            else if( label.getLabelName() == "BAR" )
            {
                TEST_ASSERT( test, !barFound );
                barFound = true;
            }
            else if( label.getLabelName() == "BAZ" )
            {
                TEST_ASSERT( test, !bazFound );
                bazFound = true;
            }
            else
            {
                TEST_ASSERT(test,false);
            }
        }
        TEST_ASSERT( test, fooFound && barFound && bazFound );
        ++iter;
        TEST_ASSERT( test, iter == program.end() );
    }

    void test_string( TestSuite const& suite )
    {
        Test test(suite,__func__);
        std::string fileName{"TypeString.tydal"};
        std::string programText{ "Type simple: String\n"
                                 "Type complex: String(Template)" };
        Program program = Tydal::parse( programText, fileName.c_str() );
        auto iter = program.begin();
        TEST_ASSERT( test,iter != program.end() );
        TEST_ASSERT( test, iter->first == "simple" );
        auto stringPtr = std::dynamic_pointer_cast<StringType const>( iter->second );
        TEST_ASSERT( test, stringPtr.operator bool() );
        TEST_ASSERT( test, stringPtr->getSpecification() == "" );
        ++iter;
        TEST_ASSERT( test,iter != program.end() );
        stringPtr = std::dynamic_pointer_cast<StringType const>( iter->second );
        TEST_ASSERT( test, stringPtr.operator bool() );
        TEST_ASSERT( test, stringPtr->getSpecification() == "Template" );
        ++iter;
        TEST_ASSERT( test, iter == program.end() );
    }

    void
    testSimpleType( TestSuite const& test,
                    std::shared_ptr<BaseType const> ptrType,
                    SimpleType::Type type )
    {
        TEST_ASSERT( test, ptrType.operator bool() );
        auto simpleType = std::dynamic_pointer_cast<SimpleType const>( ptrType );
        TEST_ASSERT( test, simpleType.operator bool() );
        TEST_ASSERT( test, simpleType->getType() == type );
    }

    void test_variant( TestSuite const& suite )
    {
        Test test(suite,__func__);
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
        try
        {
            Program program = Tydal::parse( programText, "Variant.tydal" );
            auto iter = program.begin();
            TEST_ASSERT( test,iter != program.end() );
            TEST_ASSERT( test, iter->first == "simple" );
            auto record = std::dynamic_pointer_cast<RecordType const>( iter->second );
            TEST_ASSERT( test, record.operator bool() );
            ++iter;
            TEST_ASSERT( test,iter == program.end() );
            auto field = record->begin();
            TEST_ASSERT( test, field != record->end() );
            TEST_ASSERT( test, field->first == "a" );
            auto variant = std::dynamic_pointer_cast<VariantType const>( iter->second );
            TEST_ASSERT( test, variant.operator bool() );
            auto type = std::dynamic_pointer_cast<StringType const>(variant->getFieldType());
            TEST_ASSERT( test, type.operator bool() );
            ++field;
            TEST_ASSERT( test, field == record->end() );
            auto entry = variant->begin();
            TEST_ASSERT( test, entry != variant->end() );
            TEST_ASSERT( test, (*entry)->getCaseValue() == "ABC" );
            auto abcField = (*entry)->begin();
            TEST_ASSERT( test, abcField != (*entry)->end() );
            TEST_ASSERT( test, abcField->first == "b" );
            testSimpleType( test, abcField->second, SimpleType::INT );
            ++abcField;
            TEST_ASSERT( test, abcField != (*entry)->end() );
            TEST_ASSERT( test, abcField->first == "c" )
            TEST_ASSERT( test, std::dynamic_pointer_cast<BasicType const>() )
        }
        catch( Tydal::Errors::BasicError const& e )
        {
            std::cout << "Exception:\n"
                      << " " << e.what() << "\n";
            TEST_ASSERT( test, false );
        }
        catch( ... )
        {
            std::cout << "generic exception caught\n";
            TEST_ASSERT( test, false );
        }
    }
}

int main(int argc, char** argv)
{
    TestSuite suite( __FILE__ );

    test_multi( suite );
    test_record_empty( suite );
    test_record_fields( suite );
    test_array( suite );
    test_enum( suite );
    test_string( suite );
    test_variant( suite );

    return EXIT_SUCCESS;
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