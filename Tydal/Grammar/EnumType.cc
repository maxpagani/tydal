/**
 * @file Tydal/Grammar/EnumType.cc
 * @author Massimiliano Pagani
 *
 * @date 2016-10-30, 02:41
 */

#include <memory>
#include <vector>
#include "Tydal/Grammar/EnumType.hh"
#include "Tydal/Errors/DuplicateEnumLabel.hh"
#include "Tydal/Errors/CantMergeCompleteType.hh"
#include "Tydal/Errors/CantMergeDifferentTypes.hh"
#include "Tydal/Errors/CantMergeDuplicateEnumLabels.hh"
#include <cassert>
#include <algorithm>

namespace Tydal
{
    namespace Grammar
    {
        EnumType::EnumType( GenericParser::ReadingPosition const& position,
                            Partiality completeOrPartial ) :
                BaseType{ position },
                m_isComplete{ completeOrPartial == Partiality::COMPLETE }
        {
        }

        void EnumType::addLabel( EnumLabel const& label )
        {
            EnumLabel copy(label);
            addLabel( std::move( copy ));
        }

        void EnumType::addLabel(EnumLabel&& label)
        {
            GenericParser::ReadingPosition position = label.getPosition();
            auto iter = m_labels.find( label );
            if( iter != m_labels.end() )
            {
                throw Errors::DuplicateEnumLabel( position, iter->getPosition());
            }
            bool success;
            std::tie( std::ignore, success ) = m_labels.insert( std::move( label ));
            assert( success );
        }

        bool EnumType::hasLabel( std::string const& label ) const
        {
            auto iter = std::find_if( begin(),
                                      end(),
                                      [&label]( EnumLabel const& i )
                                      {
                                          return i.getLabelName() == label;
                                      }
                                    );
            return iter != end();
        }

        bool EnumType::isTypeCompleteImpl() const noexcept
        {
            return m_isComplete;
        }


        std::shared_ptr<BaseType const>
        EnumType::mergeImpl( std::shared_ptr<BaseType const> other ) const
        {
            if( m_isComplete || other->isComplete() )
            {
                throw Errors::CantMergeCompleteType( getPosition(), other->getPosition() );
            }
            std::shared_ptr<EnumType const> otherEnum = std::dynamic_pointer_cast<EnumType const>(other);
            if( !otherEnum )
            {
                throw Errors::CantMergeDifferentTypes( getPosition(),
                                                       getTypeName(),
                                                       other->getPosition(),
                                                       other->getTypeName() );
            }
            std::shared_ptr<EnumType> newType = std::make_shared<EnumType>( *this );
            for( auto item : *otherEnum )
            {
                bool isInserted;
                std::tie(std::ignore, isInserted) = newType->m_labels.insert( item );
                if( !isInserted )
                {
                    throw Errors::CantMergeDuplicateEnumLabels( getPosition(),
                                                                item.getLabelName(),
                                                                item.getPosition() );
                }
            }
            return newType;
        }

        std::string const&
        EnumType::getTypeNameImpl() const
        {
            static std::string enumName( "Enum" );
            return enumName;
        }
    }
}

