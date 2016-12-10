/**
 * @addtogroup Group
 * @{
 * @file Tydal/Tokenizer.hh
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016/09/15
 *
 */

#if !defined( TYDAL_BASE_TOKENIZER_HH )
#define TYDAL_BASE_TOKENIZER_HH

#include "GenericParser/lex.hh"
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_statement.hpp>
#include <boost/spirit/include/phoenix_algorithm.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include "Tydal/Token.hh"

namespace Tydal
{
    template <typename Lexer>
    class BaseTokenizer : public GenericParser::lex::lexer<Lexer>
    {
        public:
            BaseTokenizer();
            virtual ~BaseTokenizer() = default;

            GenericParser::lex::token_def<token_type>
                BLANK,
                NEWLINE,                // \n
                INVALID_CHAR,           // \t
                COMMENT,                // //.*$ /*.**/ #.*$
                OPEN_PAREN,             // (
                CLOSE_PAREN,            // )
                OPEN_SQUARE_PAREN,      // [
                CLOSE_SQUARE_PAREN,     // ]
                CARET,                  // ^
                KEYWORD_TYPE,           // Type
                KEYWORD_PARTIAL,        // Partial
                KEYWORD_VARIANT,        // Variant
                KEYWORD_END,            // End
                KEYWORD_OPT,            // opt
                KEYWORD_CASE,           // Case
                TYPE_RECORD,            // Record
                TYPE_ARRAY,             // Array
                TYPE_STRING,            // String
                TYPE_ENUM,              // Enum
                TYPE_INT,               // Int
                TYPE_FLOAT,             // Float
                TYPE_BOOLEAN,           // Boolean

                KEYWORD_ELLIPSIS,       // ...

                LITERAL_INT,            // [0-9][0-9]*
                LITERAL_FLOAT,          // ....
                LITERAL_STRING,         // ".*"
                LITERAL_BOOLEAN,        // true or false
                SEPARATOR_SEMICOLON,    // ;
                SEPARATOR_COMMA,        // ,
                SEPARATOR_COLON,        // :
                SYMBOL /*, INVALID */;  // [a-zA-Z_][a-zA-Z_]*


            bool
            tokenIsNativeType( token_type const& token ) const;

            bool
            tokenIsTypeStart( token_type const& token ) const;

            bool
            tokenIsBlank( token_type const& token ) const;

        private:
    };

    template <typename Lexer>
    BaseTokenizer<Lexer>::BaseTokenizer() :
               BLANK(" +"),
               NEWLINE("\\n\\r|\\n|\\r\\n"),
               INVALID_CHAR("\t"),
               COMMENT("\"//\"[^\\n\\r]*|\\/\\*.*?\\*\\/|\"#\"[^\\n\\r]*"),
               OPEN_PAREN("\\("),
               CLOSE_PAREN("\\)"),
               OPEN_SQUARE_PAREN("\\["),
               CLOSE_SQUARE_PAREN("\\]"),
               CARET("^"),
               KEYWORD_TYPE("Type"),           // Type
               KEYWORD_PARTIAL("Partial"),
               KEYWORD_VARIANT("Variant"),
               KEYWORD_END("End"),
               KEYWORD_OPT("opt"),
               KEYWORD_CASE("Case"),
               TYPE_RECORD("Record"),
               TYPE_ARRAY("Array"),
               TYPE_STRING("String"),
               TYPE_ENUM("Enum"),
               TYPE_INT("Int"),
               TYPE_FLOAT("Float"),
               TYPE_BOOLEAN("Boolean|Bool"),
               KEYWORD_ELLIPSIS("\\.\\.\\."),
               LITERAL_INT("(0x[0-9a-fA-F]+|0[0-7]+|[0-9]+)[lLuU]?"),
               LITERAL_FLOAT("[+-]?[0-9]*\\.[0-9]+([eEgG][+-]?[0-9]*\\.[0-9]+)?"),
               LITERAL_STRING( "\\\"([^\\\\\\\"]|\\\\(x[0-9a-fA-F]{1,4}|[0-7]{1,3}|[bfnrt\\\"]))*\\\""),
               //LITERAL_STRING("\\\"([^\\\\]|\\\\(x[0-9a-fA-F]{1,4}|[0-7]{1,3}|[bfnrt\"\\/']))*\\\""),
               LITERAL_BOOLEAN("true|false"),
               SEPARATOR_SEMICOLON(";"),
               SEPARATOR_COMMA(","),
               SEPARATOR_COLON(":"),
               SYMBOL("[a-zA-Z_][a-zA-Z_0-9]*") /*,
               INVALID( ".*" ) */
    {
        using boost::spirit::lex::_start;
        using boost::spirit::lex::_end;
        using boost::phoenix::ref;
        // associate tokens with the lexer

        this->self = BLANK |
                     NEWLINE |
                     INVALID_CHAR |
                     COMMENT |
                     OPEN_PAREN |
                     CLOSE_PAREN |
                     OPEN_SQUARE_PAREN |
                     CLOSE_SQUARE_PAREN |
                     CARET |
                     KEYWORD_TYPE |
                     KEYWORD_PARTIAL |
                     KEYWORD_VARIANT |
                     KEYWORD_END |
                     KEYWORD_OPT |
                     KEYWORD_CASE |
                     TYPE_RECORD |
                     TYPE_ARRAY |
                     TYPE_STRING |
                     TYPE_ENUM |
                     TYPE_INT |
                     TYPE_FLOAT |
                     TYPE_BOOLEAN |
                     KEYWORD_ELLIPSIS |
                     LITERAL_INT |
                     LITERAL_FLOAT |
                     LITERAL_STRING |
                     LITERAL_BOOLEAN |
                     SEPARATOR_SEMICOLON |
                     SEPARATOR_COMMA |
                     SEPARATOR_COLON |
                     SYMBOL /*| INVALID */;
    //    this->self( "WS" ) = lex::token_def<>( "[ \\t\\n]+" );
    /*
        this->self =
                word [++ref(w), ref(c) += distance(_start, _end)]
                   | eol [++ref(c), ++ref(l)]
                   | any [++ref(c)]
                   ;
     */
    }

    template <typename Lexer> bool
    BaseTokenizer<Lexer>::tokenIsNativeType( token_type const& token ) const
    {
        return token == TYPE_FLOAT.id() ||
               token == TYPE_BOOLEAN.id() ||
               token == TYPE_INT.id() ||
               token == TYPE_STRING.id();
    }

    template<typename Lexer> bool
    BaseTokenizer<Lexer>::tokenIsTypeStart( token_type const& token ) const
    {
        return token == TYPE_ARRAY.id() ||
               token == TYPE_RECORD.id() ||
               token == TYPE_ENUM.id() ||
               token == SYMBOL.id() ||
               token == KEYWORD_TYPE.id() ||
               tokenIsNativeType( token );
    }

    template <typename Lexer> bool
    BaseTokenizer<Lexer>::tokenIsBlank( token_type const& token ) const
    {
        return token == NEWLINE.id() ||
               token == INVALID_CHAR.id() ||
               token == COMMENT.id() ||
               token == BLANK.id();
    }
}

#endif  /* TYDAL_BASE_TOKENIZER_HH */
