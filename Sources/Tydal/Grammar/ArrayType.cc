/**
 * @file Tydal/Grammar/ArrayType.cc
 * @author Massimiliano Pagani
 *
 * @date 2016-10-30, 02:25
 */

#include <memory>
#include "Tydal/Grammar/ArrayType.hh"

namespace Tydal
{
    namespace Grammar
    {
        ArrayType::ArrayType( GenericParser::ReadingPosition const& position,
                              std::shared_ptr<BaseType const> itemType ) :
                BaseType{ position },
                m_itemType{itemType}
        {
        }

        ArrayType::~ArrayType()
        {
        }

        bool ArrayType::isTypeCompleteImpl() const
        {
            return true;
        }

        std::shared_ptr<BaseType const>
        ArrayType::mergeImpl( std::shared_ptr<BaseType const> other ) const
        {
            return std::unique_ptr<BaseType const>();
        }
        
        std::string const& 
        ArrayType::getTypeNameImpl() const
        {
            static std::string arrayName( "Array" );
            return arrayName;
        }

    }
}

