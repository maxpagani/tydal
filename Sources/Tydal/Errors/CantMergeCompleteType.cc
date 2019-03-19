/**
 * @addtogroup Tydal/Errors
 * @{
 * @file Tydal/Errors/CantMergeCompleteType.cc
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-11-02
 *
 */

#include "Tydal/Errors/CantMergeCompleteType.hh"

namespace Tydal
{
    namespace Errors
    {
        CantMergeCompleteType::CantMergeCompleteType(
            GenericParser::ReadingPosition const& position,
            GenericParser::ReadingPosition const& completeTypePosition
        ) :
            BasicError{ position, "" },
            m_completeTypePosition{ completeTypePosition }
        {
        }
        
    }
}


///@}


