/**
 * @addtogroup Group
 * @{
 * @file OutputTranslator/Tydal.cc
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-10-18
 *
 */

#include <OutputTranslator/Tydal.hh>
#include <iostream>

namespace OutputTranslator
{
    using namespace ::Tydal::Grammar;

    void
    Tydal::translateRecord( std::string const& name,
                            std::shared_ptr<RecordType const> recordType,
                            std::ostream& out )
    {
    }

    void
    Tydal::translateEnum( std::string const& name,
                          std::shared_ptr<EnumType const> enumType,
                          std::ostream& out )
    {
    }

    void
    Tydal::translateString( std::string const& name,
                            std::shared_ptr<StringType const> stringType,
                            std::ostream& out )
    {
    }

    void
    Tydal::translateSimpleType( std::string const& name,
                                std::shared_ptr<SimpleType const> simpleType,
                                std::ostream& out )
    {
    }

    void
    Tydal::translateArray( std::string const& name,
                           std::shared_ptr<ArrayType const> arrayType,
                           std::ostream& out )
    {
    }

}  // end of namespace OutputTranslator
///@}


