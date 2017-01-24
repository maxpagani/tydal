/**
 * @addtogroup OutputTranslator
 * @{
 * @file OutputTranslator/Scala.hh
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-10-18
 *
 */


#if !defined( OUTPUTTRANSLATOR_SCALA_HH )
#define OUTPUTTRANSLATOR_SCALA_HH

#include "OutputTranslator/Base.hh"
#include "Tydal/Grammar/BaseType.hh"
#include "Tydal/Grammar/VariantType.hh"

namespace OutputTranslator
{
    class Scala : public Base
    {
        private:
            virtual void translateRecord( std::string const& name,
                                          std::shared_ptr<Tydal::Grammar::RecordType const> recordType,
                                          std::ostream& out ) override;
            virtual void translateEnum( std::string const& name,
                                        std::shared_ptr<Tydal::Grammar::EnumType const> enumType,
                                        std::ostream& out ) override;
            virtual void translateString( std::string const& name,
                                          std::shared_ptr<Tydal::Grammar::StringType const> stringType,
                                          std::ostream& out ) override;
            virtual void translateSimpleType( std::string const& name,
                                              std::shared_ptr<Tydal::Grammar::SimpleType const> simpleType,
                                              std::ostream& out ) override;
            virtual void translateArray( std::string const& name,
                                         std::shared_ptr<Tydal::Grammar::ArrayType const> arrayType,
                                         std::ostream& out ) override;

            void translateVariantBranch( std::string const& name,
                                         std::shared_ptr<Tydal::Grammar::VariantType const> variant,
                                         std::shared_ptr<Tydal::Grammar::VariantCaseEntry const> branch,
                                         std::ostream& out );
            void translateRecordVariant( std::string const& name,
                                         std::shared_ptr<Tydal::Grammar::RecordType const> recordType,
                                         std::ostream& out );
            void translateFields( std::string const& name,
                                       std::shared_ptr<Tydal::Grammar::RecordType const> recordType,
                                       std::ostream& out );
            void translateVariantBranches( std::string const& name,
                                           std::shared_ptr<Tydal::Grammar::RecordType const> recordType,
                                           std::ostream& out );
            void translateSimpleRecord( std::string const& name,
                                        std::shared_ptr<Tydal::Grammar::RecordType const> recordType,
                                        std::ostream& out );
            void translateSubRecords( std::string const& name,
                                      std::shared_ptr<Tydal::Grammar::RecordType const> recordType,
                                      std::ostream& out );

            void printField( std::ostream& out,
                             Tydal::Grammar::RecordType::ConstIterator::value_type const& field );

            void
            tydalTypeToScala( std::shared_ptr<Tydal::Grammar::BaseType const> type,
                              std::string const& fieldName,
                              std::ostream& out );

            void pushEnclosingRecordName( std::string const& recordName );
            void popEnclosingRecordName();
            std::vector<std::string> const& getEnclosingRecordNames() const;
            std::string getRecordNames() const;

            std::vector<std::string> m_enclosingRecordNames;

    };

}  // end of namespace OutputTranslator

#endif
///@}


