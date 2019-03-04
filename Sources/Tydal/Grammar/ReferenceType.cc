/**
 * @file Tydal/Grammar/ReferenceType.cc
 * @author %<%USER%>%
 *
 * @date %<%DATE%>%, %<%TIME%>%
 */

#include "Tydal/Grammar/ReferenceType.hh"
#include <cassert>

namespace Tydal
{
    namespace Grammar
    {
        ReferenceType::ReferenceType( GenericParser::ReadingPosition const& position,
                                      std::string const& typeReferenceName ) :
                       BaseType( position ),
                       m_typeReferenceName{ typeReferenceName },
                       m_typeDescription{ "Reference to <>" }
        {
        }
        
        void 
        ReferenceType::bindTo( std::shared_ptr<BaseType const> realType )
        {
            m_boundType = realType;
            m_typeDescription =  std::string{"Reference to "} +
                                 realType->getTypeName();
        }

        bool ReferenceType::isTypeCompleteImpl() const
        {
            return true;
        }
        
        std::string const& ReferenceType::getTypeNameImpl() const
        {
            return m_typeDescription;
        }

        std::shared_ptr<BaseType const>
        ReferenceType::mergeImpl( std::shared_ptr<BaseType const> other ) const
        {
            assert( false );
        }

    }
}