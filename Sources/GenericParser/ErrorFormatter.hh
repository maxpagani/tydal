/**
 * @addtogroup Group
 * @{
 * @file GenericParser/ErrorFormatter.hh
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 27/05/2010
 *
 */


#if !defined( GENERICPARSER_ERRORFORMATTER_HH )
#define GENERICPARSER_ERRORFORMATTER_HH

#include <string>
#include "GenericParser/ReadingPosition.hh"

namespace GenericParser
{
    /**
     * The base class for error formatting classes.
     * 
     *
     */

    class ErrorFormatter
    {
        public:
            ErrorFormatter();
            virtual ~ErrorFormatter();

            std::string format( ReadingPosition const& position,
                                std::string const& message ) const;

        private:
            virtual std::string
            formatMessageImpl( ReadingPosition const& position,
                               std::string const& message ) const = 0;

    };
}

#endif
///@}


