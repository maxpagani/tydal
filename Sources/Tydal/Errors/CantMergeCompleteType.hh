/**
 * @addtogroup Tydal/Errors
 * @{
 * @file Tydal/Errors/CantMergeCompleteType.hh
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-11-02
 *
 */


#if !defined( TYDAL_ERRORS_CANTMERGECOMPLETETYPE_HH )
#define TYDAL_ERRORS_CANTMERGECOMPLETETYPE_HH

#include "Tydal/Errors/BasicError.hh"

namespace Tydal
{
    namespace Errors
    {

        /** CantMergeCompleteType
         *
         * 
         *
         */

        class CantMergeCompleteType : public BasicError
        {
            public:
                CantMergeCompleteType( GenericParser::ReadingPosition const& position,
                                       GenericParser::ReadingPosition const& completeTypePosition  );
                virtual ~CantMergeCompleteType() = default;
            private:
                GenericParser::ReadingPosition m_completeTypePosition;
        };
    }
}

#endif
///@}


