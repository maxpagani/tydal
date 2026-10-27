/**
 * @addtogroup Tydal/Errors
 * @{
 * @file Tydal/Errors/UnexpectedEndOfFile.hh
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2026-10-27
 *
 */


#if !defined( TYDAL_ERRORS_UNEXPECTEDENDOFFILE_HH )
#define TYDAL_ERRORS_UNEXPECTEDENDOFFILE_HH

#include "Tydal/Errors/BasicError.hh"

namespace Tydal
{
    namespace Errors
    {

        /** UnexpectedEndOfFile
         *
         * The input ended while the parser was still expecting tokens.
         *
         */

        class UnexpectedEndOfFile : public BasicError
        {
            public:
                explicit UnexpectedEndOfFile( GenericParser::ReadingPosition const& position );
                ~UnexpectedEndOfFile() = default;
        };

    }  // end of namespace Errors
}

#endif
///@}


