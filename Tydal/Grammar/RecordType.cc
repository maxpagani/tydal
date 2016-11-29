/**
 * @file Tydal/Grammar/RecordType.cc
 * @author Massimiliano Pagani
 *
 * @date 2016-10-30, 01:49
 */

#include "Tydal/Grammar/RecordType.hh"
#include <map>
#include "Tydal/Grammar/RecordField.hh"
#include "Tydal/Errors/DuplicatedRecordField.hh"
#include "Partiality.hh"
#include "Tydal/Errors/CantMergeCompleteType.hh"
#include "Tydal/Errors/CantMergeDifferentTypes.hh"
#include "Tydal/Errors/CantMergeDuplicateRecordFields.hh"
#include <cassert>

namespace Tydal
{
    namespace Grammar
    {
        RecordType::RecordType( GenericParser::ReadingPosition const& position,
                                Partiality partiality ) :
                    BaseType{ position },
                    m_isComplete{ partiality == Partiality::COMPLETE }

        {
        }

        void
        RecordType::addField( std::shared_ptr<RecordField const> field )
        {
            auto iter = m_fields.find( field->getName() );
            if( iter == m_fields.end() )
            {
                m_fields.insert( std::make_pair( field->getName(), field ));
            }
            else
            {
                throw Errors::DuplicatedRecordField( field->getPosition(),
                                                     field->getName(),
                                                     iter->second->getPosition() );
            }
        }

        std::string const&
        RecordType::getTypeNameImpl() const
        {
            static std::string recordName( "Record" );
            return recordName;
        }

        bool RecordType::isTypeCompleteImpl() const
        {
            return m_isComplete;
        }

        std::shared_ptr<BaseType const>
        RecordType::mergeImpl( std::shared_ptr<BaseType const> other ) const
        {
            if( m_isComplete || other->isComplete() )
            {
                throw Errors::CantMergeCompleteType( getPosition(), other->getPosition() );
            }
            auto otherRecord = std::dynamic_pointer_cast<RecordType const>(other);
            if( !otherRecord )
            {
                throw Errors::CantMergeDifferentTypes( getPosition(),
                                                       getTypeName(),
                                                       other->getPosition(),
                                                       other->getTypeName() );
            }
            std::shared_ptr<RecordType> newType = std::make_shared<RecordType>( *this );
            for( auto item : *otherRecord )
            {
                bool isInserted;
                std::tie(std::ignore, isInserted) = newType->m_fields.insert( item );
                if( !isInserted )
                {
                    throw Errors::CantMergeDuplicateRecordFields( getPosition(),
                                                                  item.first,
                                                                  item.second->getPosition() );
                }
            }
            return newType;
        }

    }
}
