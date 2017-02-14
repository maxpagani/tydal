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
#include <iomanip>
#include <numeric>

namespace OutputTranslator
{
    using namespace Tydal::Grammar;

    namespace
    {
        std::string toScalaId( std::string const& branchName )
        {
            std::string::const_iterator begin=branchName.begin();
            if( *begin == '"' )
            {
                ++begin;
            }
            std::string::const_iterator end=branchName.end();
            --end;
            if( *end != '"' )
            {
                ++end;
            }
            std::string id;
            for( auto i=begin; i!=end; ++i )
            {
                if( std::isalnum( *i ) )
                {
                    id.push_back( *i );
                }
                else {
                    id.push_back( '_' );
                    std::ostringstream hex;
                    hex << std::setfill('0') << std::setw(2) << std::hex
                        << static_cast<int>(*i);
                    id.append( hex.str() );
                }
            }
            return id;
        }

        std::string
        getVariantTypeName( std::string const& enclosingRecordName,
                            std::string const& fieldName )
        {
            std::cout << "ern: " << enclosingRecordName << "\n";
            std::cout << "fn:  " << fieldName << "\n";
            return enclosingRecordName + "_" + fieldName;
        }
        
        template<class It> std::string
        mkString( It begin,
                  It end,
                  std::string const& left,
                  std::string const& separator,
                  std::string const& right )
        {
            std::string result = left;
            if( begin != end )
            {
                result.append( *begin );
                ++begin;
                while( begin != end )
                {
                    result.append( separator );
                    result.append( *begin );
                    ++begin;
                }
            }
            result.append( right );
            return result;
        }
    }

    void Scala::pushEnclosingRecordName( std::string const& recordName )
    {
        m_enclosingRecordNames.push_back( recordName );
    }

    void Scala::popEnclosingRecordName()
    {
        assert( !m_enclosingRecordNames.empty() );
        m_enclosingRecordNames.pop_back();
    }

    std::vector<std::string> const& Scala::getEnclosingRecordNames() const
    {
        return m_enclosingRecordNames;
    }

    std::string Scala::getRecordNames() const
    {
        auto begin = m_enclosingRecordNames.begin();
        auto end = m_enclosingRecordNames.end();
        return mkString( begin, end, "", "_", "");
    }

    void
    Scala::tydalTypeToScala( std::shared_ptr<BaseType const> type,
                             std::string const& fieldName,
                             std::ostream& out )
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
            tydalTypeToScala( arrayType->getItemType(), fieldName, out );
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
                tydalTypeToScala( field.second->getType(), fieldName, out );
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
            out << variantType->getFieldType()->getTypeName();
            return;
        }
    }

    std::string computeVariantName( std::string const& fieldName,
                                    std::shared_ptr<VariantType const> type )
    {
        return fieldName + "_" + "cases";
    }
    
    
    void Scala::printField( std::ostream& out,
                            RecordType::ConstIterator::value_type const& field )
    {
        out << margin() << field.first << ": ";
        bool isOptional = field.second->isOptional();
        if( isOptional )
        {
            out << "Option[";
        }
        auto type = field.second->getType();
        tydalTypeToScala( type, field.first, out );
        if( isOptional )
        {
            out << "]";
        }
        auto variant = std::dynamic_pointer_cast<VariantType const>( type );
        if( variant != nullptr )
        {
            out << ",\n";
            out << margin() << computeVariantName( field.first, variant )
                << ": ";
            if( isOptional )
            {
                out << "Option[";
            }
            auto variantTypeName = mkString( getEnclosingRecordNames().begin(),
                                             getEnclosingRecordNames().end(),
                                             "", "_", "" );
            out << getVariantTypeName( getRecordNames(), field.first );
            if( isOptional )
            {
                out << "]";
            }
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
        std::string branchName = traitName + "_" + toScalaId(branch->getCaseValue());
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
        out << "\n" << margin() << ") extends " << traitName << "\n";
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
                std::string traitName = getVariantTypeName( name, field.first );
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
                                   std::shared_ptr<Tydal::Grammar::RecordType const> record,
                                   std::ostream& out )
    {
        for( auto const& field : *record )
        {
            auto variant = std::dynamic_pointer_cast<VariantType const>(field.second->getType());
            if( variant )
            {
            }
        }
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
                    ++iter;
                }
                return iter;
            }
    };

    void
    Scala::translateFields( const std::string& name,
                            std::shared_ptr<const Tydal::Grammar::RecordType> recordType,
                            std::ostream& out )
    {
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
    }

    void
    Scala::translateRecord( std::string const& name,
                            std::shared_ptr<RecordType const> record,
                            std::ostream& out )
    {
        std::ostringstream text;

        pushEnclosingRecordName( name );
        //translateSubRecords( name, recordType, out );
        translateVariantBranches( name, record, out );
/*
        implicit val simpleReads = new Reads[Simple] {
  override def reads(o: JsValue) = o.getAs[String] match {
    case "ABC" => abcReads.reads(o)
    case "CDF" => cdfReads.reads(o)
    case _ => JsFailure("Variant match failed for 'Simple'")
  }
 * */
        text << "case class " << name << " (\n";
        indent();
        translateFields( name, record, text );
        outdent();
        text << ")\n";
        out << text.str();

        popEnclosingRecordName();
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
    Scala::translateSimpleType( std::string const& fieldTypeName,
                                std::shared_ptr<SimpleType const> simpleType,
                                std::ostream& out )
    {
        out << "type " << fieldTypeName << " = ";
        tydalTypeToScala( simpleType, fieldTypeName, out );
    }

    void
    Scala::translateArray( std::string const& name,
                           std::shared_ptr<ArrayType const> arrayType,
                           std::ostream& out )
    {
        out << "type " << name << " = Array[";
        tydalTypeToScala( arrayType->getItemType(), name, out );
        out << "]\n";
    }


}  // end of namespace OutputTranslator
///@}


