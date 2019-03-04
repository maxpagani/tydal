/**
 * @file Tydal/Errors/InvalidLiteral.hh
 * @author MaxP
 *
 * @date 2016-11-27 21:08
 */

#if !defined( TYDAL_ERRORS_INVALIDLITERAL_HH )
#define TYDAL_ERRORS_INVALIDLITERAL_HH

#include "Tydal/Errors/BasicError.hh"
namespace Tydal
{
    namespace Errors
    {
        class InvalidLiteral : public BasicError
        {
            public:
                InvalidLiteral( GenericParser::ReadingPosition const& position,
                                std::string const& literal,
                                std::string const& typeName );
                virtual ~InvalidLiteral() = default;
            private:
                std::string m_literal;
                std::string m_typeName;
        };
    }
}


#endif /* TYDAL_ERRORS_INVALIDLITERAL_HH */

