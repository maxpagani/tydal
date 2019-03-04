/**
 * @addtogroup Tydal/Errors
 * @{
 * @file Tydal/Errors/DuplicateEnumLabel.hh
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-11-02
 *
 */


#if !defined( TYDAL_ERRORS_DUPLICATEENUMLABEL_HH )
#define TYDAL_ERRORS_DUPLICATEENUMLABEL_HH

#include "Tydal/Errors/BasicError.hh"

namespace Tydal
{
    namespace Errors
    {

        /** DuplicateEnumLabel
         *
         * 
         *
         */

        class DuplicateEnumLabel : public BasicError
        {
            public:
                DuplicateEnumLabel( GenericParser::ReadingPosition const& position,
                                    GenericParser::ReadingPosition const& completeTypePosition  );
                virtual ~DuplicateEnumLabel() = default;
            private:
                GenericParser::ReadingPosition m_otherLabelPosition;
        };
    }
}

#endif
///@}


