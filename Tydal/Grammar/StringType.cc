/**
 * @file Tydal/Grammar/StringType.cc
 * @author Massimiliano Pagani
 *
 * @date 2016-10-30, 02:41
 */

#include <memory>
#include "Tydal/Grammar/StringType.hh"
#include <cassert>

namespace Tydal
{
    namespace Grammar
    {
        StringType::StringType( GenericParser::ReadingPosition const& position,
                                std::string const& specification ) :
                BaseType{ position },
                m_specification{specification},
                m_specificationType{REFERENCE}
        {
        }

        StringType::StringType( GenericParser::ReadingPosition const& position,
                                std::shared_ptr<EnumType const> specification ) :
                BaseType{ position },
                m_enumSpecification{specification},
                m_specificationType{REFERENCE}
        {
        }

        StringType::~StringType()
        {
        }

        bool StringType::isTypeCompleteImpl() const
        {
            return true;
        }

        std::shared_ptr<BaseType const>
        StringType::mergeImpl( std::shared_ptr<BaseType const> other ) const
        {
            // sorry, you can't
            assert( false );
        }

        std::string const&
        StringType::getTypeNameImpl() const
        {
            static auto name = std::string( "String" );
            return name;
        }
    }
}

