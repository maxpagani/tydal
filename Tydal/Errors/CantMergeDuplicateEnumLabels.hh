/**
 * @addtogroup Tydal/Errors
 * @{
 * @file Tydal/Errors/CantMergeDuplicateLabels.hh
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-11-02
 *
 */


#if !defined( TYDAL_ERRORS_CANTMERGEDUPLICATEENUMLABELS_HH)
#define TYDAL_ERRORS_CANTMERGEDUPLICATEENUMLABELS_HH

#include "Tydal/Errors/BasicError.hh"

namespace Tydal
{
    namespace Errors
    {

        /** CantMergeDuplicateLabels
         *
         * 
         *
         */

        class CantMergeDuplicateEnumLabels : public BasicError
        {
            public:
                CantMergeDuplicateEnumLabels( GenericParser::ReadingPosition const& position,
                                              std::string const& labelName,
                                              GenericParser::ReadingPosition const& otherPosition );
                virtual ~CantMergeDuplicateEnumLabels() = default;
            private:
                GenericParser::ReadingPosition m_completeTypePosition;
                std::string m_label;
        };
    }
}

#endif
///@}


