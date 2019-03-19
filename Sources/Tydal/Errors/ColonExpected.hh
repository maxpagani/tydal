/**
 * @addtogroup Tydal/Errors
 * @{
 * @file Tydal/Errors/ColonExpected.hh
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-11-04
 *
 */


#if !defined( TYDAL_ERRORS_COLONEXPECTED_HH )
#define TYDAL_ERRORS_COLONEXPECTED_HH

#include "Tydal/Errors/BasicError.hh"

namespace Tydal
{
    namespace Errors
    {

        /** ColonExpected
         *
         * 
         *
         */

        class ColonExpected : public BasicError
        {
            public:
                ColonExpected( GenericParser::ReadingPosition const& position,
                                std::string const& tokenFound );
                ~ColonExpected() = default;
            private:
                std::string m_tokenFound;
        };

    }  // end of namespace Errors
}

#endif
///@}


