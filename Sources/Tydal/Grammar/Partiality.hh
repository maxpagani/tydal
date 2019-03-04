/**
 * @addtogroup Tydal/Grammar
 * @{
 * @file Tydal/Grammar/Partiality.hh
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-11-04
 *
 */


#if !defined( TYDAL_GRAMMAR_PARTIALITY_HH )
#define TYDAL_GRAMMAR_PARTIALITY_HH

namespace Tydal
{
    namespace Grammar
    {

        /** Partiality enumeration specifies whether a type is partial or
         * complete.
         *
         */

        enum class Partiality
        {
            PARTIAL,
            COMPLETE
        };

    }  // end of namespace Grammar
}   // end of namespace Tydal
#endif
///@}


