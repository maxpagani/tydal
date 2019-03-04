/**
 * @addtogroup Tydal/Errors
 * @{
 * @file Tydal/Errors/ColonExpected.cc
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-11-04
 *
 */

#include "Tydal/Errors/ColonExpected.hh"

namespace Tydal
{
    namespace Errors
    {
        ColonExpected::ColonExpected( GenericParser::ReadingPosition const& position,
                                        std::string const& found ) :
                        BasicError{ position, "" },
                        m_tokenFound{ found }
        {
        }
        

    }  // end of namespace Errors
}   // end of namespace Tydal
///@}


