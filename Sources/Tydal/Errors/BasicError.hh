/**
 * @addtogroup Tydal/Errors
 * @{
 * @file Tydal/Errors/BasicError.hh
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-11-02
 *
 */


#if !defined( TYDAL_ERRORS_BASICERROR_HH )
#define TYDAL_ERRORS_BASICERROR_HH

#include <stdexcept>
#include "GenericParser/ReadingPosition.hh"

namespace Tydal
{
    namespace Errors
    {
        /** BasicError
         *
         *
         *
         */

        class BasicError : public std::runtime_error
        {
            public:
                template<class T>
                BasicError( GenericParser::ReadingPosition const& position,
                            T text );
                virtual ~BasicError() = default;
                BasicError( BasicError const& copy ) = default;
                BasicError& operator=( BasicError const& copy ) = default;
            private:
                GenericParser::ReadingPosition m_position;
        };
                
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: templates :::
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        
        template<class T>
        BasicError::BasicError( GenericParser::ReadingPosition const& position,
                                T text ) :
                    std::runtime_error{ text },
                    m_position{ position }
        {
        }

    }
}

#endif
///@}


