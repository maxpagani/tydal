/**
 * @addtogroup Tydal/Errors
 * @{
 * @file Tydal/Errors/TypeExpected.hh
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-11-04
 *
 */


#if !defined( TYDAL_ERRORS_TYPEEXPECTED_HH )
#define TYDAL_ERRORS_TYPEEXPECTED_HH

#include "Tydal/Errors/BasicError.hh"

namespace Tydal
{
    namespace Errors
    {

        /** TypeExpected
         *
         * 
         *
         */

        class TypeExpected : public BasicError
        {
            public:
                TypeExpected( GenericParser::ReadingPosition const& position,
                                std::string const& tokenFound );
                ~TypeExpected() = default;
            private:
                std::string m_tokenFound;
        };

    }  // end of namespace Errors
}

#endif
///@}


