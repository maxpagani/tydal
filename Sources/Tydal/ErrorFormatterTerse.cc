/**
 * @addtogroup Tydal
 * @{
 * @file ErrorFormatterTerse.cc
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 27/05/2010
 *
 */

#include "ErrorFormatterTerse.hh"
#include <sstream>

std::string
ErrorFormatterTerse::formatMessageImpl( GenericParser::ReadingPosition const& position,
                                        std::string const& message ) const
{
    std::ostringstream out;

    out << position.getFileName() << ':'
        << position.getLineNumber() << ':'
        << position.getColumnNumber() << ':'
        << " error: " << message;

    return out.str();
}


///@}


