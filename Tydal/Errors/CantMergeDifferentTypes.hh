/**
 * @addtogroup Tydal/Errors
 * @{
 * @file Tydal/Errors/CantMergeDifferentTypes.hh
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-11-02
 *
 */


#if !defined( TYDAL_ERRORS_CANTMERGEDIFFERENTTYPES_HH )
#define TYDAL_ERRORS_CANTMERGEDIFFERENTTYPES_HH

#include "Tydal/Errors/BasicError.hh"

namespace Tydal
{
    namespace Errors
    {

        /** CantMergeDifferentTypes
         *
         * 
         *
         */

        class CantMergeDifferentTypes : public BasicError
        {
            public:
                CantMergeDifferentTypes( GenericParser::ReadingPosition const& positionTypeA,
                                         std::string const& typeNameA,
                                         GenericParser::ReadingPosition const& positionTypeB,
                                         std::string const& typeNameB );
                virtual ~CantMergeDifferentTypes() = default;
            private:
                std::string m_typeNameA;
                GenericParser::ReadingPosition m_positionTypeB;
                std::string m_typeNameB;
        };
    }
}

#endif
///@}


