/**
 * @addtogroup Tydal/Errors
 * @{
 * @file Tydal/Errors/DuplicatedRecordField.cc
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-11-04
 *
 */

#include "Tydal/Errors/DuplicatedRecordField.hh"

namespace Tydal
{
    namespace Errors
    {

        DuplicatedRecordField::DuplicatedRecordField(
            const GenericParser::ReadingPosition& position,
            const std::string& fieldName, 
            const GenericParser::ReadingPosition& otherPosition
        ) :
            BasicError{position,""},
            m_fieldName{ fieldName },
            m_otherPosition{ otherPosition } 
        {
        }

    }  // end of namespace Errors
}  // end of namespace Tydal
///@}


