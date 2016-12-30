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
#include <sstream>

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
            return;
        }
        auto variantType = std::dynamic_pointer_cast<VariantType const>(type);
        if( variantType != nullptr )
        {

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
    Scala::translateSimpleRecord( std::string const& name,
                                  std::shared_ptr<RecordType const> recordType,
                                  std::ostream& out )
    {
        out << margin() << "case class " << name << "(\n";
        indent();
        auto iter = recordType->begin();
        if( iter != recordType->end() )
        {
            printField( out, *iter );
            ++iter;
            for( ; iter != recordType->end(); ++iter )
            {
                out << ",\n";
                printField( out, *iter );
            }
            out << "\n";
        }
        outdent();
        out << margin() << ")";
    }

    void
    Scala::translateSubRecords( std::string const& name,
                                std::shared_ptr<RecordType const> recordType,
                                std::ostream& out )
    {
        for( auto const& field : *recordType )
        {
            auto record = std::dynamic_pointer_cast<RecordType const>(field.second->getType());
            if( record )
            {
                translateRecord( name + "_" + field.first,
                                 record,
                                 out );
            }
        }
    }

    void
    Scala::translateVariantBranch( std::string const& traitName,
                                   std::shared_ptr<VariantType const> variant,
                                   std::shared_ptr<VariantCaseEntry const> branch,
                                   std::ostream& out )
    {
        std::string branchName = traitName + "_" + branch->getCaseValue();
        out << margin() << "case class " << branchName << "(\n";
        if( !branch->isEmpty() )
        {
            indent();
            bool isFirst = true;
            for( auto const& field : *branch )
            {
                if( isFirst )
                {
                    isFirst = false;
                }
                else
                {
                    out << ", ";
                }
                printField( out, field );
            }
            outdent();
        }
        out << ") extends " << traitName << "\n";
    }

    void
    Scala::translateVariantBranches( std::string const& name,
                                     std::shared_ptr<RecordType const> recordType,
                                     std::ostream& out )
    {
        for( auto const& field : *recordType )
        {
            auto variant = std::dynamic_pointer_cast<VariantType const>(field.second->getType());
            if( variant )
            {
                std::string traitName = name + "_" + field.first;
                out << margin() << "sealed trait " << traitName << "\n\n";
                for( auto const& branch : *variant )
                {
                    translateVariantBranch( traitName,
                                            variant,
                                            branch,
                                            out );
                }
            }
        }
    }

    void
    Scala::translateRecordVariant( std::string const& name,
                                   std::shared_ptr<Tydal::Grammar::RecordType const> recordType,
                                   std::ostream& out )
    {

    }

    class PlainFieldIterator
    {
        private:
            typedef Tydal::Grammar::RecordType::ConstIterator ConstIterator;
        public:
            PlainFieldIterator( ConstIterator begin,
                                ConstIterator end ) :
                        m_iter{ seek(begin,end)},
                        m_end{ end }
            {
            }

            PlainFieldIterator( PlainFieldIterator const& ) = default;
            PlainFieldIterator& operator=( PlainFieldIterator const& ) = default;

            ConstIterator::value_type operator*() const
            {
                return *m_iter;
            }

            PlainFieldIterator operator++()
            {
                if( m_iter != m_end )
                {
                    ++m_iter;
                }
                return PlainFieldIterator( m_iter, m_end );
            }

            bool operator != ( ConstIterator const& iter )
            {
                return m_iter != iter;
            }
        private:
            ConstIterator m_iter;
            ConstIterator m_end;

            static ConstIterator seek( ConstIterator iter, ConstIterator end )
            {
                while( iter != end )
                {
                    auto type = iter->second->getType();
                    if( !std::dynamic_pointer_cast<RecordType const>(type) &&
                        !std::dynamic_pointer_cast<VariantType const>(type) )
                    {
                        break;
                    }
                }
                return iter;
            }
    };

    void
    Scala::translatePlainFields( const std::string& name,
                                 std::shared_ptr<const Tydal::Grammar::RecordType> recordType,
                                 std::ostream& out )
    {
        auto iter = PlainFieldIterator( recordType->begin(),
                                        recordType->end());
        if( iter != recordType->end() )
        {

            printField( out, *iter );
            ++iter;
            for( ; iter != recordType->end(); ++iter )
            {
                out << ",\n";
                printField( out, *iter );
            }
            out << "\n";
        }
    }

    void
    Scala::translateRecord( std::string const& name,
                            std::shared_ptr<RecordType const> recordType,
                            std::ostream& out )
    {
        std::ostringstream text;

        translateSubRecords( name, recordType, out );
        translateVariantBranches( name, recordType, out );
/*
        implicit val simpleReads = new Reads[Simple] {
  override def reads(o: JsValue) = o.getAs[String] match {
    case "ABC" => abcReads.reads(o)
    case "CDF" => cdfReads.reads(o)
    case _ => JsFailure("Variant match failed for 'Simple'")
  }
 * */
        translateRecordVariant( name, recordType, out );
        text << "case class " << name << " (\n";
        indent();
        translatePlainFields( name, recordType, text );
        outdent();
        text << ")\n";
        out << text.str();
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


