/**
 * @addtogroup Tydal/Errors
 * @{
 * @file Tydal/Errors/CantMergeDifferentTypes.cc
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-11-02
 *
 */

#include "Tydal/Errors/CantMergeDifferentTypes.hh"

namespace Tydal
{
    namespace Errors
    {
        CantMergeDifferentTypes::CantMergeDifferentTypes(
            GenericParser::ReadingPosition const& positionTypeA,
            std::string const& typeNameA,
            GenericParser::ReadingPosition const& positionTypeB,
            std::string const& typeNameB
        ) :
            BasicError( positionTypeA, "" ),
            m_typeNameA{ typeNameA },
            m_positionTypeB{ positionTypeB },
            m_typeNameB{ typeNameB }
        {
        }
        
    }
}

///@}


