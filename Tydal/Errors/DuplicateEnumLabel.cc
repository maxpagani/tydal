/**
 * @addtogroup Tydal/Errors
 * @{
 * @file Tydal/Errors/DuplicateEnumLabel.cc
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-11-02
 *
 */

#include "Tydal/Errors/DuplicateEnumLabel.hh"

namespace Tydal
{
    namespace Errors
    {
        DuplicateEnumLabel::DuplicateEnumLabel(
            GenericParser::ReadingPosition const& position,
            GenericParser::ReadingPosition const& otherLabelPosition
        ) :
            BasicError{ position, "" },
            m_otherLabelPosition{ otherLabelPosition }
        {
        }

    }
}

///@}


