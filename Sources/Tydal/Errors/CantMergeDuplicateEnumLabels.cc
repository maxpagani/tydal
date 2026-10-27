/**
 * @addtogroup Tydal/Errors
 * @{
 * @file Tydal/Errors/CantMergeDuplicateLabels.cc
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-11-02
 *
 */

#include "Tydal/Errors/CantMergeDuplicateEnumLabels.hh"
#include <string>
#include "BasicError.hh"
#include "CantMergeDuplicateEnumLabels.hh"


namespace Tydal
{
    namespace Errors
    {
        CantMergeDuplicateEnumLabels::CantMergeDuplicateEnumLabels(
            GenericParser::ReadingPosition const& position,
            std::string const& labelName,
            GenericParser::ReadingPosition const& otherPosition
        ) :
            BasicError{ position,
                        "can't merge enum label '" + labelName +
                        "', already defined at line " +
                        std::to_string( otherPosition.getLineNumber() ) },
            m_completeTypePosition{ otherPosition },
            m_label{ labelName }
        {
        }
        
    }
}


///@}


