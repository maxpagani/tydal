/**
 * @addtogroup Group
 * @{
 * @file Tydal/Grammar/Type.cc
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-10-24
 *
 */

#include "Tydal/Grammar/BaseType.hh"

namespace Tydal
{
    namespace Grammar
    {
        BaseType::BaseType( GenericParser::ReadingPosition const& position ) :
                  m_position( position )
        {
        }

    }  // end of namespace Grammar
}  // end of namespace Tydal

///@}


