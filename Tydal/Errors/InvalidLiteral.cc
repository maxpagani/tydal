/**
 * @file Tydal/Errors/InvalidLiteral.hh
 * @author MaxP
 *
 * @date 2016-11-27 21:08
 */

#include "Tydal/Errors/InvalidLiteral.hh"
#include <sstream>

namespace Tydal
{
    namespace Errors
    {
        namespace
        {
            std::string
            errorText( std::string const& literal, std::string const& typeName )
            {
                std::ostringstream msg;
                msg << "'" << literal << "' is not a valid literal for type '"
                    << typeName << "'";
                return msg.str();
            }
        }

        InvalidLiteral::InvalidLiteral( GenericParser::ReadingPosition const& position,
                                        std::string const& literal,
                                        std::string const& typeName) :
                        BasicError{ position, errorText( literal, typeName ) }
        {
        }
    }
}

