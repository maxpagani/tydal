/**
 * @addtogroup Tydal/Errors
 * @{
 * @file Tydal/Errors/TypeExpected.cc
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-11-04
 *
 */

#include "Tydal/Errors/TypeExpected.hh"

namespace Tydal
{
    namespace Errors
    {
        TypeExpected::TypeExpected( GenericParser::ReadingPosition const& position,
                                        std::string const& found ) :
                        BasicError{ position, "" },
                        m_tokenFound{ found }
        {
        }
        

    }  // end of namespace Errors
}   // end of namespace Tydal
///@}


