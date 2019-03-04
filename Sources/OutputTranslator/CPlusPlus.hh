/**
 * @addtogroup Group
 * @{
 * @file OutputTranslator/CPlusPlus.hh
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-10-18
 *
 */


#if !defined( OUTPUTTRANSLATOR_CPLUSPLUS_HH )
#define OUTPUTTRANSLATOR_CPLUSPLUS_HH

#include "OutputTranslator/Base.hh"

namespace OutputTranslator
{
    class CPlusPlus : public Base
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
    };

}  // end of namespace OutputTranslator

#endif
///@}


