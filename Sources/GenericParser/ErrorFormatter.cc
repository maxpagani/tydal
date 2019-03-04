/**
 * @addtogroup Group
 * @{
 * @file GenericParser/ErrorFormatter.cc
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 27/05/2010
 *
 */

#include "GenericParser/ErrorFormatter.hh"

namespace GenericParser
{
    ErrorFormatter::ErrorFormatter()
    {
    }

    ErrorFormatter::~ErrorFormatter()
    {
    }

    std::string
    ErrorFormatter::format( ReadingPosition const& position,
                            std::string const& message ) const
    {
        return formatMessageImpl( position, message );
    }
}

///@}


