/**
 * @addtogroup Tydal/Errors
 * @{
 * @file Tydal/Errors/CantMergeDuplicateRecordFields.cc
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-11-02
 *
 */

#include "Tydal/Errors/CantMergeDuplicateRecordFields.hh"
#include <string>
#include "BasicError.hh"
#include "CantMergeDuplicateRecordFields.hh"


namespace Tydal
{
    namespace Errors
    {
        CantMergeDuplicateRecordFields::CantMergeDuplicateRecordFields(
            GenericParser::ReadingPosition const& position,
            std::string const& labelName,
            GenericParser::ReadingPosition const& otherPosition
        ) :
            BasicError{ position,
                        "can't merge record field '" + labelName +
                        "', already defined at line " +
                        std::to_string( otherPosition.getLineNumber() ) },
            m_completeTypePosition{ otherPosition },
            m_label{ labelName }
        {
        }

    }
}


///@}


