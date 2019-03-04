/**
 * @addtogroup Tydal/Errors
 * @{
 * @file Tydal/Errors/CantMergeDuplicateRecordFields.hh
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-11-02
 *
 */


#if !defined( TYDAL_ERRORS_CANTMERGEDUPLICATERECORDFIELDS_HH)
#define TYDAL_ERRORS_CANTMERGEDUPLICATERECORDFIELDS_HH

#include "Tydal/Errors/BasicError.hh"

namespace Tydal
{
    namespace Errors
    {

        /** CantMergeDuplicateRecordFields
         *
         *
         *
         */

        class CantMergeDuplicateRecordFields : public BasicError
        {
            public:
                CantMergeDuplicateRecordFields( GenericParser::ReadingPosition const& position,
                                              std::string const& labelName,
                                              GenericParser::ReadingPosition const& otherPosition );
                virtual ~CantMergeDuplicateRecordFields() = default;
            private:
                GenericParser::ReadingPosition m_completeTypePosition;
                std::string m_label;
        };
    }
}

#endif
///@}


