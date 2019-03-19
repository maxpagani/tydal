/**
 * @file SimpleType.cc
 * @author apagani
 * @date 26 ottobre 2016 8.35
 */

#include "Tydal/Grammar/SimpleType.hh"
#include <cassert>

namespace Tydal
{
    namespace Grammar
    {
        SimpleType::SimpleType( GenericParser::ReadingPosition const& position,
                                Type type ) :
                    BaseType{ position },
                    m_type{ type }
        {
        }

        std::string const&
        SimpleType::getTypeNameImpl() const
        {
            static std::string boolName( "Bool" );
            static std::string floatName( "Float" );
            static std::string intName( "Int" );
            static std::string noName;

            switch( m_type )
            {
                case BOOL:
                    return boolName;

                case FLOAT:
                    return floatName;

                case INT:
                    return intName;

                default:
                    assert( false );
                    return noName;
            }
        }

        bool
        SimpleType::isTypeCompleteImpl() const
        {
            return true;
        }

        std::shared_ptr<BaseType const>
        SimpleType::mergeImpl( std::shared_ptr<BaseType const> other ) const
        {
            // no way you can do it.
            assert( false );
        }


    }
}


