/**
 * @addtogroup Group
 * @{
 * @file OutputTranslator/Scala.cc
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-10-18
 *
 */

#include <OutputTranslator/Scala.hh>
#include <iostream>

namespace OutputTranslator
{
    using namespace Tydal::Grammar;

    void
    Scala::tydalTypeToScala( std::shared_ptr<BaseType const> type, std::ostream& out )
    {
        auto simpleType = std::dynamic_pointer_cast<SimpleType const>(type);
        if( simpleType )
        {
            switch( simpleType->getType() )
            {
                case SimpleType::BOOL:
                    out << "Boolean";
                    return;

                case SimpleType::FLOAT:
                    out << "Float";
                    return;

                case SimpleType::INT:
                    out << "Int";
                    return;

                default:
                    assert( false );
                    return;
            }
        }
        auto stringType = std::dynamic_pointer_cast<StringType const>(type);
        if( stringType )
        {
            out << "String";
            return;
        }
        auto enumType = std::dynamic_pointer_cast<EnumType const>(type);
        if( enumType )
        {
            out << "*Enum Type Not (yet) Implemented*";
            return;
        }
        auto arrayType = std::dynamic_pointer_cast<ArrayType const>(type);
        if( arrayType )
        {
            out << "Array[";
            tydalTypeToScala( arrayType->getItemType(), out );
            out << "]";
            return;
        }
        auto recordType = std::dynamic_pointer_cast<RecordType const>(type);
        if( recordType )
        {
            out << "{\n";
            indent();
            for( auto& field: *recordType )
            {
                out << margin() << "val " << field.first << " : ";
                if( field.second->isOptional() )
                {
                    out << "Option[";
                }
                tydalTypeToScala( field.second->getType(), out );
                if( field.second->isOptional() )
                {
                    out << margin() << "]";
                }
                out << '\n';
            }
            outdent();
            out << margin() << "}";

        }
    }

    void Scala::printField( std::ostream& out,
                            RecordType::ConstIterator::value_type const& field )
    {
            out << margin() << field.first << ": ";
            if( field.second->isOptional() )
            {
                out << "Option[";
            }
            tydalTypeToScala( field.second->getType(), out );
            if( field.second->isOptional() )
            {
                out << "]";
            }
    }

    void
    Scala::translateRecord( std::string const& name,
                            std::shared_ptr<RecordType const> recordType,
                            std::ostream& out )
    {
        out << margin() << "case class " << name << "(\n";
        indent();
        auto iter = recordType->begin();
        printField( out, *iter );
        ++iter;
        for( ; iter != recordType->end(); ++iter )
        {
            out << ",\n";
            printField( out, *iter );
        }
        outdent();
        out << "\n" << margin() << ")";
    }

    void
    Scala::translateEnum( std::string const& name,
                          std::shared_ptr<EnumType const> enumType,
                          std::ostream& out )
    {
        out << "*enum not implemented yet*\n";
    }

    void
    Scala::translateString( std::string const& name,
                            std::shared_ptr<StringType const> stringType,
                            std::ostream& out )
    {
        out << "*string not implemented yet*\n";
    }

    void
    Scala::translateSimpleType( std::string const& name,
                                std::shared_ptr<SimpleType const> simpleType,
                                std::ostream& out )
    {
        out << "type " << name << " = ";
        tydalTypeToScala( simpleType, out );
    }

    void
    Scala::translateArray( std::string const& name,
                           std::shared_ptr<ArrayType const> arrayType,
                           std::ostream& out )
    {
        out << "type " << name << " = Array[";
        tydalTypeToScala( arrayType->getItemType(), out );
        out << "]\n";
    }


}  // end of namespace OutputTranslator
///@}


