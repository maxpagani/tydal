/**
 * @addtogroup Group
 * @{
 * @file Tydal/Token.hh
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 27/05/2010
 *
 */


#if !defined( TYDAL_TOKEN_HH )
#define TYDAL_TOKEN_HH

#include "GenericParser/lex.hh"
#include <string>

namespace Tydal
{
    typedef GenericParser::lex::lexertl::token< char const*,
                                                boost::mpl::vector0<>,
                                                boost::mpl::false_> token_type;
}

#endif
///@}


