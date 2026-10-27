/**
 * @addtogroup Tydal/Errors
 * @{
 * @file Tydal/Errors/UnexpectedEndOfFile.cc
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2026-10-27
 *
 */

#include "Tydal/Errors/UnexpectedEndOfFile.hh"

namespace Tydal
{
    namespace Errors
    {
        UnexpectedEndOfFile::UnexpectedEndOfFile( GenericParser::ReadingPosition const& position ) :
                        BasicError{ position, "unexpected end of file" }
        {
        }

    }  // end of namespace Errors
}   // end of namespace Tydal
///@}
