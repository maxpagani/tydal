/**
 * @file Tydal/Errors/InvalidVariantType.hh
 * @author MaxP
 *
 * @date 2016-11-27 15:00
 */

#if !defined( TYDAL_ERRORS_INVALIDVARIANT_TYPE_HH )
#define TYDAL_ERRORS_INVALIDVARIANT_TYPE_HH

#include "Tydal/Errors/BasicError.hh"

namespace Tydal
{
    namespace Errors
    {
        class InvalidVariantType : public BasicError
        {
            public:
                InvalidVariantType( GenericParser::ReadingPosition const& position,
                                    std::string const& type );
                virtual ~InvalidVariantType() = default;
            private:
        };
    }
}

#endif /* TYDAL_ERRORS_INVALIDVARIANT_TYPE_HH */

