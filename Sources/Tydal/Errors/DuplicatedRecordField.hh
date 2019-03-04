/**
 * @addtogroup Tydal/Errors
 * @{
 * @file Tydal/Errors/DuplicatedRecordField.hh
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-11-04
 *
 */

#if !defined( TYDAL_ERRORS_DUPLICATEDRECORDFIELD_HH )
#define TYDAL_ERRORS_DUPLICATEDRECORDFIELD_HH

#include "Tydal/Errors/BasicError.hh"

namespace Tydal
{
    namespace Errors
    {

        /** DuplicatedRecordField
         *
         * 
         *
         */

        class DuplicatedRecordField : public BasicError
        {
            public:
                DuplicatedRecordField( GenericParser::ReadingPosition const& position,
                                       std::string const& fieldName,
                                       GenericParser::ReadingPosition const& otherPosition );
                ~DuplicatedRecordField() = default;
            private:
                std::string m_fieldName;
                GenericParser::ReadingPosition m_otherPosition;
        };

    }  // end of namespace Errors
}  // end of namespace Tydal
#endif
///@}


