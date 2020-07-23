/**
 * @addtogroup GenericParser
 * @{
 * @file GenericParser/ErrorLogger.cc
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 27/05/2010
 *
 */

#include "GenericParser/ErrorLogger.hh"

namespace GenericParser
{

    ErrorLogger::ErrorLogger( ErrorFormatter* formatter, std::ostream& out ) :
                 formatter_( formatter ),
                 out_( out )
    {
    }

    ErrorLogger::~ErrorLogger()
    {
    }

    void
    ErrorLogger::log( ReadingPosition const& position,
                      std::string const& message )
    {
        std::string logRecord = formatter_->format( position, message );
        out_ << logRecord << '\n';
    }

}

///@}


