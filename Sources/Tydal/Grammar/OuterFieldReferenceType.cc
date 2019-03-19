/**
 * @file Tydal/Grammar/OuterFieldReferenceType.cc
 * @author MaxP
 *
 * @date 2016-11-27 14:30
 */

#include "Tydal/Grammar/OuterFieldReferenceType.hh"
#include "BaseType.hh"
#include <cassert>

namespace Tydal
{
    namespace Grammar
    {
        OuterFieldReferenceType::OuterFieldReferenceType( GenericParser::ReadingPosition const& position ) :
                                 BaseType{ position }
        {
        }
                                 
        bool OuterFieldReferenceType::isTypeCompleteImpl() const
        {
            return true;
        }
                
        std::string const& OuterFieldReferenceType::getTypeNameImpl() const
        {
            static std::string typeName{"Variant outer Type"};
            return typeName;
        }

        std::shared_ptr<BaseType const>
        OuterFieldReferenceType::mergeImpl( std::shared_ptr<BaseType const> other ) const
        {
            assert( false );
        }

    }
}