/**
 * @addtogroup Tydal
 * @{
 * @file ErrorFormatterTerse.hh
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 27/05/2010
 *
 */


#if !defined( ERRORFORMATTERTERSE_HH )
#define ERRORFORMATTERTERSE_HH

#include "GenericParser/ErrorFormatter.hh"

/** ErrorFormatterTerse
 *
 * 
 *
 */

class ErrorFormatterTerse : public GenericParser::ErrorFormatter
{
    public:
        ErrorFormatterTerse() = default;
        virtual ~ErrorFormatterTerse() = default;
        ErrorFormatterTerse( ErrorFormatterTerse const& copy ) = delete;
        ErrorFormatterTerse& operator=( ErrorFormatterTerse const& copy ) = delete;

    private:

    std::string
        formatMessageImpl( GenericParser::ReadingPosition const& position,
                           std::string const& message ) const override;

};

#endif
///@}


