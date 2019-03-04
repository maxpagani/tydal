/**
 * @addtogroup Tydal
 * @{
 * @file Tydal/Grammar/Program.cc
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-10-13
 *
 */

#include "Tydal/Grammar/Program.hh"
#include <Tydal/Grammar/AnonymousRecord.hh>
#include <Tydal/Grammar/EnumType.hh>
#include <algorithm>
#include <vector>

namespace Tydal
{
    namespace Grammar
    {
        Program::~Program()
        {
        }

        bool
        Program::addType( std::string const& name,
                          std::shared_ptr<BaseType const> type )
        {
            auto iter = m_types.find( name );
            if( iter != m_types.end() )
            {
                return false;
            }
            auto pair = std::make_pair( name,
                                        std::const_pointer_cast<BaseType>(type) );
            auto index = m_sequence.size();
            m_sequence.push_back( pair );
            m_types.insert( std::make_pair( name, index ));
            return true;
        }

        bool
        Program::mergePartialType( std::string const& name,
                                   std::shared_ptr<BaseType const> type )
        {
            auto iter = m_types.find( name );
            if( iter == m_types.end() )
            {
                addType( name, type );
            }
            else
            {
                auto index = iter->second;
                std::shared_ptr<BaseType const> existingType = m_sequence[index].second;
                TypeDefinition newDefinition = std::make_pair( name,
                                                    existingType->merge( type ) );
                m_sequence[index] = newDefinition;
            }
            return true;
        }

    }  // end of namespace Grammar
} // end of namespace Tydal
///@}


