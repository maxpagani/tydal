/**
 * @file Tydal/Errors/InvalidVariantType.hh
 * @author MaxP
 *
 * @date 2016-11-27 15:00
 */

#include "Tydal/Errors/InvalidVariantType.hh"
#include <sstream>

namespace Tydal
{
    namespace Errors
    {
        namespace
        {
            std::string
            errorMessage( std::string const& type )
            {
                std::ostringstream msg;
                msg << "Type: '" << type << "' cannot be used in a Variant";
                return msg.str();
            }
        }
        InvalidVariantType::InvalidVariantType( GenericParser::ReadingPosition const& position,
                                                std::string const& type ) :
                            BasicError{ position, errorMessage( type ) }
        {
        }
    }
}