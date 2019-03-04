/**
 * @addtogroup Group
 * @{
 * @file OutputTranslator/Java.cc
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-10-18
 *
 */

#include <OutputTranslator/Java.hh>
#include <iostream>

namespace OutputTranslator
{
    using namespace Tydal::Grammar;

    void
    Java::translateRecord( std::string const& name,
                           std::shared_ptr<RecordType const> recordType,
                           std::ostream& out )
    {
    }

    void
    Java::translateEnum( std::string const& name,
                         std::shared_ptr<EnumType const> enumType,
                         std::ostream& out )
    {
    }

    void
    Java::translateString( std::string const& name,
                           std::shared_ptr<StringType const> stringType,
                           std::ostream& out )
    {
    }

    void
    Java::translateSimpleType( std::string const& name,
                               std::shared_ptr<SimpleType const> simpleType,
                               std::ostream& out )
    {
    }

    void
    Java::translateArray( std::string const& name,
                          std::shared_ptr<ArrayType const> arrayType,
                          std::ostream& out )
    {
    }


}  // end of namespace OutputTranslator
///@}


