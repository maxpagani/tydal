/**
 * @addtogroup Tydal/Errors
 * @{
 * @file Tydal/Errors/SymbolExpected.hh
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-11-04
 *
 */


#if !defined( TYDAL_ERRORS_SYMBOLEXPECTED_HH )
#define TYDAL_ERRORS_SYMBOLEXPECTED_HH

#include "Tydal/Errors/BasicError.hh"

namespace Tydal
{
    namespace Errors
    {

        /** SymbolExpected
         *
         * 
         *
         */

        class SymbolExpected : public BasicError
        {
            public:
                SymbolExpected( GenericParser::ReadingPosition const& position,
                                std::string const& tokenFound );
                ~SymbolExpected() = default;
            private:
                std::string m_tokenFound;
        };

    }  // end of namespace Errors
}

#endif
///@}


