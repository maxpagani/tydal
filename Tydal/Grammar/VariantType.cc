/**
 * @file VariantType.cc
 * @author Max
 *
 * @date 2016-11-24 22:32
 */

#include "Tydal/Grammar/VariantType.hh"
#include <cassert>

namespace Tydal
{
    namespace Grammar
    {

        VariantType::VariantType( GenericParser::ReadingPosition const& position,
                                  std::string const& symbol,
                                  std::shared_ptr<BaseType const> type ) :
                     BaseType{ position },
                     m_symbol{ symbol },
                     m_type{ type }
        {
        }

        bool VariantType::isTypeCompleteImpl() const
        {
            return true;
        }

        std::string const& VariantType::getTypeNameImpl() const
        {
            static std::string typeName{ "Variant" };
            return typeName;
        }

        std::shared_ptr<BaseType const>
        VariantType::mergeImpl( std::shared_ptr<BaseType const> other ) const
        {
            auto otherVariant = std::dynamic_pointer_cast<VariantType const>( other );
            
            assert( otherVariant );
            assert( getFieldName() == otherVariant->getFieldName() );
            assert( getFieldType() == otherVariant->getFieldType() );
            auto result = std::make_shared<VariantType>( *this );
            for( auto& caseEntry : *otherVariant )
            {
                result->addCase( caseEntry );
            }
            return result;
        }

    }
}

