/**
 * @addtogroup Tydal
 * @{
 * @file Tydal/Grammar/AnonymousRecord.hh
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-10-17
 *
 */


#if !defined( TYDAL_GRAMMAR_ANONYMOUSRECORD_HH )
#define TYDAL_GRAMMAR_ANONYMOUSRECORD_HH

namespace Tydal
{
    namespace Grammar
    {

        /** AnonymousRecord
         *
         * 
         *
         */

        class AnonymousRecord
        {
            public:
                AnonymousRecord() = default;
                ~AnonymousRecord() = default;
                AnonymousRecord( AnonymousRecord const& copy ) = default;
                AnonymousRecord( AnonymousRecord&& copy ) = default;
                AnonymousRecord& operator=( AnonymousRecord const& copy ) = default;
            private:
        };

    }  // end of namespace Grammar
}

#endif
///@}


