/** 
 * @file Tydal/Tokenizer.hh
 * @author apagani
 *
 * @date September 15, 2016, 3:27 PM
 */

#if !defined( TYDALTOKENIZER_HH ) 
#define TYDALTOKENIZER_HH

#include "LexParser.hh"
#include "Tydal/Token.hh"
#include "Tydal/BaseTokenizer.hh"

namespace Tydal
{
    typedef GenericParser::lex::lexertl::actor_lexer<token_type> lexer_type;

    typedef BaseTokenizer<lexer_type> Tokenizer;
}
#endif /* TYDALTOKENIZER_HH */

