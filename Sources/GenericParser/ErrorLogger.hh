/**
 * @addtogroup GenericParser
 * @{
 * @file GenericParser/ErrorLogger.hh
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 27/05/2010
 *
 */

#if !defined( GENERICPARSER_ERRORLOGGER_HH )
#define GENERICPARSER_ERRORLOGGER_HH

#include "GenericParser/ErrorFormatter.hh"
#include "GenericParser/ReadingPosition.hh"
#include <iostream>

namespace GenericParser
{
    /** Error logging class. This class has the responsibility of reporting errors
     * in a properly formatted text.
     *
     */

    class ErrorLogger
    {
        public:
            ErrorLogger( ErrorFormatter* formatter, std::ostream& out );
            ~ErrorLogger();

            void log( ReadingPosition const& position,
                      std::string const& message );

        private:
            ErrorLogger( ErrorLogger const& copy );
            ErrorLogger& operator=( ErrorLogger const& copy );

            ErrorFormatter* formatter_;
            std::ostream& out_;
    };
}
#endif
///@}


