/**
 * @addtogroup Tydal/Errors
 * @{
 * @file Tydal/Errors/RightBananaExpected.hh
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-11-04
 *
 */


#if !defined( TYDAL_ERRORS_RIGHTBANANAEXPECTED_HH )
#define TYDAL_ERRORS_RIGHTBANANAEXPECTED_HH

#include "Tydal/Errors/BasicError.hh"

namespace Tydal
{
    namespace Errors
    {

        /** 
         * The closing parenthesis was expected, but something else was found.
         */

        class RightBananaExpected : public BasicError
        {
            public:
                RightBananaExpected(
                    GenericParser::ReadingPosition const& position,
                    std::string const& tokenFound
                );
                ~RightBananaExpected() = default;
            private:
                std::string m_tokenFound;
        };

    }  // end of namespace Errors
}

#endif
///@}


