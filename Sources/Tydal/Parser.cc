/**
 * @file Tydal/Parser.cc
 * @author apagani
 * @date September 19, 2016 1:55 PM
 */

#include "Tydal/Parser.hh"
#include "GenericParser/ReadingPosition.hh"
#include "GenericParser/ErrorLogger.hh"
#include "Tydal/Grammar/Program.hh"
#include "Tydal/Grammar/SimpleType.hh"
#include "Tydal/Grammar/RecordType.hh"
#include "Tydal/Grammar/ArrayType.hh"
#include "Tydal/Grammar/StringType.hh"
#include "Tydal/Grammar/EnumType.hh"
#include "Tydal/Errors/SymbolExpected.hh"
#include "Tydal/Errors/ColonExpected.hh"
#include "ErrorFormatterTerse.hh"
#include "Tokenizer.hh"
#include "Tydal/Errors/RightBananaExpected.hh"
#include "Tydal/Errors/TypeExpected.hh"
#include "Tydal/Errors/InvalidVariantType.hh"
#include "Tydal/Errors/InvalidLiteral.hh"
#include "Tydal/Errors/UnexpectedEndOfFile.hh"
#include "Tydal/Grammar/ReferenceType.hh"
#include "Tydal/Grammar/OuterFieldReferenceType.hh"
#include "Tydal/Grammar/VariantType.hh"
#include <memory>
#include <cassert>

/*
     * EnumItem ::= \identifier
     * EnumItems ::= \empty | EnumItem ( [","] EnumItem )*
     * EnumType ::= "Enum" EnumItems "End"
     * TypeReference ::= \identifier
     * StringType ::= EnumType | RegexpType | TypeReference
     * SimpleType ::= "Int" | "Boolean" | "Float" | "String" [ "(" StringType ")"]
     * RecordField ::= ["opt"] \identifier ":" CompleteOrPartialType
     * RecordField ::= "opt" "Group" RecordFields "End"
     * RecordField ::= "Variant" \identifier : BasicType ("Case" (\identifier | \stringLiteral | \intLiteral ) : RecordFields )*
     * RecordFields ::= \empty | RecordField ( [";"] RecordField )*
     * RecordType ::= "Record" RecordFields "End"
     * PartialRecordType ::= "Partial" RecordType
     * ArrayType ::= "Array" "[" Type "]"
     * AggregateType ::= RecordType | ArrayType
     * CompleteType ::= SimpleType | AggregateType | EnumType | TypeReference
     * PartialType ::= "Partial"  ( RecordType | EnumType )
     * CompleteOrPartialType ::= CompleteType | PartialType
     * TypeAlias ::= "Type" TypeName : CompleteOrPartialType
     *
     * TydalProgram ::= TypeAlias*
     */

/** Quite oddly this is not defined in the standard library */
#if 0
namespace std
{
    template<typename T, typename... Args>
    std::shared_ptr<T> make_shared(Args&&... args)
    {
        return std::shared_ptr<T>(new T(std::forward<Args>(args)...));
    }
}
#endif

namespace Tydal
{
    using GenericParser::ReadingPosition;
    using namespace Grammar;

    namespace
    {
        std::string
        toString( boost::iterator_range<const char*> const& token )
        {
            return std::string( token.begin(), token.end() );
        }

        std::string
        toString( token_type const& token )
        {
            auto const& range = token.value();
            return toString( range );
        }

        class Parser
        {
            public:
                Parser( TokenIterator begin,
                        TokenIterator end,
                        GenericParser::ErrorLogger& logger);
                Parser( Parser const& ) = delete;
                Parser& operator=(Parser const&) = delete;
                ~Parser() = default;

                /**
                 * Performs the parsing of the program.
                 */
                Program parse();

            private:
                typedef GenericParser::lex::token_def<token_type> Token;
                token_type const& current() const;
                void seek( Token const& token );

                std::shared_ptr<StringType const>
                parseString( GenericParser::ReadingPosition const& position );

                std::shared_ptr<RecordType const>
                parseRecord( GenericParser::ReadingPosition const& position,
                             Partiality partiality );

                std::shared_ptr<ArrayType const>
                parseArray(GenericParser::ReadingPosition const& position);

                std::shared_ptr<EnumType const>
                parseEnum( GenericParser::ReadingPosition const& position,
                           Partiality partiality );

                std::shared_ptr<BaseType const>
                parseType(GenericParser::ReadingPosition const& position);

                bool isLiteralOfType( token_type token,
                                      std::shared_ptr<BaseType const> type );
                bool parseToken( Token const& token );
                std::string parseSymbol();
                void parseCompleteOrPartialType();
                std::shared_ptr<RecordField const> parseRecordField();

                std::shared_ptr<BaseType const> parseVariantType();

                std::shared_ptr<VariantCaseEntry const>
                parseVariantCase( std::shared_ptr<BaseType const> fieldType );

                std::shared_ptr<RecordField const>
                parseVariant( RecordField::Optionality optionality );

                void log( std::ostringstream const& msg );
                void log( std::string const& msg );

                int m_errorsCount = 0;
                TokenIterator m_begin;
                TokenIterator m_end;
                TokenIterator m_scan;
                Tokenizer const& m_tokenizer;
                Program m_program;
                GenericParser::ErrorLogger& m_log;
        };

        inline void Parser::log( std::ostringstream const& msg )
        {
            log( msg.str() );
        }

        void Parser::log( std::string const& msg )
        {
            m_log.log( m_scan.getPosition(), msg );
            ++m_errorsCount;
        }

        /**
         * Gives the token at the reading position.
         *
         * @return the current token.
         * @throw Errors::UnexpectedEndOfFile if the input is over.
         */
        token_type const& Parser::current() const
        {
            if( m_scan == m_end )
            {
                throw Errors::UnexpectedEndOfFile( m_scan.getPosition() );
            }
            return *m_scan;
        }

        Parser::Parser(TokenIterator begin, TokenIterator end, GenericParser::ErrorLogger& logger) :
                m_begin{begin},
                m_end{ end },
                m_scan{ begin },
                m_tokenizer{begin.getTokenizer()},
                m_log{logger}
        {
        }

#define TOKEN_ID(X) (m_tokenizer.X.id())
#define SCAN_IS(X)  (current() == TOKEN_ID(X))
#define SCAN_IS_NOT(X)  (!SCAN_IS(X))

        bool Parser::isLiteralOfType( token_type token,
                                      std::shared_ptr<BaseType const> type )
        {
            if( token.id() == TOKEN_ID(LITERAL_INT))
            {
                auto charType = std::dynamic_pointer_cast<SimpleType const>(type);
                return charType != nullptr && charType->getType() == SimpleType::INT;
            }
            else if( token.id() == TOKEN_ID( LITERAL_STRING))
            {
                auto stringType = std::dynamic_pointer_cast<StringType const>(type);
                return stringType != nullptr;
            }
            else if( token.id() == TOKEN_ID( LITERAL_BOOLEAN ))
            {
                auto boolType = std::dynamic_pointer_cast<SimpleType const>(type);
                return boolType != nullptr && boolType->getType() == SimpleType::BOOL;
            }
            else if( token.id() == TOKEN_ID(SYMBOL))
            {
                auto enumType = std::dynamic_pointer_cast<EnumType const>(type);
                return enumType != nullptr && enumType->hasLabel( toString(token));
            }
            return false;
        }

        /**
         * Moves the reading position ahead until the given token is found.
         *
         * @param token the token to look for.
         */
        void Parser::seek( Token const& token )
        {
            while( m_scan != m_end && (*m_scan).id() != token.id() )
            {
                ++m_scan;
            }
        }


        /**
         * Parse the type part of a variant.
         *
         * @return the type of this variant.
         */
        std::shared_ptr<BaseType const>
        Parser::parseVariantType()
        {
            auto position = m_scan.getPosition();
            if( SCAN_IS( TYPE_ENUM ))
            {
                ++m_scan;
                return parseEnum( position, Partiality::COMPLETE );
            }
            else if( SCAN_IS( TYPE_STRING ))
            {
                ++m_scan;
                return parseString( position );
            }
            else if( SCAN_IS( TYPE_INT ))
            {
                ++m_scan;
                return std::make_shared<SimpleType>( position, SimpleType::INT );
            }
            else if( SCAN_IS( TYPE_BOOLEAN ))
            {
                ++m_scan;
                return std::make_shared<SimpleType>( position,
                                                     SimpleType::BOOL );
            }
            else if( SCAN_IS( SYMBOL ))
            {
                // lookup will happen in the second pass, for now let's just
                // pretend this is correct.
                std::string name = toString( current() );
                ++m_scan;
                return std::make_shared<ReferenceType>( position, name );
            }
            else if( SCAN_IS( CARET ))
            {
                // lookup in this record and check if a field with the same
                // name is available
                ++m_scan;
                return std::make_shared<OuterFieldReferenceType>( position );
            }
            else
            {
                throw Errors::InvalidVariantType( position, toString( current() ));
            }
        }

        std::shared_ptr<VariantCaseEntry const>
        Parser::parseVariantCase( std::shared_ptr<BaseType const> type )
        {
            assert( SCAN_IS( KEYWORD_CASE ));
            auto position = m_scan.getPosition();
            ++m_scan;
            std::string literal = toString( current() );
            if( !isLiteralOfType( current(), type ))
            {
                throw Errors::InvalidLiteral( position,
                                              literal,
                                              type->getTypeName() );
            }
            ++m_scan;
            if( SCAN_IS( SEPARATOR_COLON ))
            {
                ++m_scan;
            }
            auto record = std::make_shared<RecordType>( position,
                                                        Partiality::COMPLETE );
            while( SCAN_IS_NOT( KEYWORD_CASE ) && SCAN_IS_NOT( KEYWORD_END ) )
            {
                auto field = parseRecordField();
                record->addField( field );
            }
            return std::make_shared<VariantCaseEntry>( literal,
                                                       position,
                                                       record );
        }

        std::shared_ptr<RecordField const>
        Parser::parseVariant( RecordField::Optionality optionality )
        {
            assert( SCAN_IS( KEYWORD_VARIANT ));
            auto position = m_scan.getPosition();
            ++m_scan;
            std::string name = parseSymbol();
            if( SCAN_IS_NOT( SEPARATOR_COLON ) )
            {
                throw Errors::ColonExpected(m_scan.getPosition(), toString( current() ));
            }
            ++m_scan;
            auto symbolType = parseVariantType();
            auto variant = std::make_shared<VariantType>( position, name, symbolType );
            while( SCAN_IS_NOT( KEYWORD_END ))
            {
                auto caseEntry = parseVariantCase( symbolType );
                variant->addCase( caseEntry );
            }
            ++m_scan; // we found it, it's our.
            auto record = std::make_shared<RecordField>( name,
                                                         position,
                                                         variant,
                                                         optionality );
            return record;
        }

        std::shared_ptr<RecordField const> Parser::parseRecordField()
        {
            auto currentPosition = m_scan.getPosition();
            RecordField::Optionality optionality = RecordField::REQUIRED;
            if( SCAN_IS( KEYWORD_OPT ))
            {
                optionality = RecordField::OPTIONAL;
                ++m_scan;
            }
            if( SCAN_IS( KEYWORD_VARIANT) )
            {
                auto field = parseVariant( optionality );
                return field;
            }
            if( SCAN_IS_NOT( SYMBOL ))
            {
                throw Errors::SymbolExpected( currentPosition, toString( current() ) );
            }
            std::string symbolName = toString( current() );
            ++m_scan;
            if( SCAN_IS_NOT( SEPARATOR_COLON ) )
            {
                throw Errors::ColonExpected(m_scan.getPosition(), toString( current() ));
            }
            ++m_scan;
            auto fieldType = parseType( m_scan.getPosition() );
            auto field = std::make_shared<RecordField>( symbolName,
                                                        currentPosition,
                                                        fieldType,
                                                        optionality );
            return field;
        }


        std::shared_ptr<RecordType const>
        Parser::parseRecord( GenericParser::ReadingPosition const& position,
                             Partiality partiality )
        {
            std::shared_ptr<RecordType> record = std::make_shared<RecordType>( position, partiality );
            while( SCAN_IS_NOT( KEYWORD_END ) )
            {
                std::shared_ptr<RecordField const> field = parseRecordField();
                record->addField( field );
            }
            ++m_scan;   // skip the End
            return record;
        }

        std::shared_ptr<ArrayType const>
        Parser::parseArray( GenericParser::ReadingPosition const& position )
        {
            if( SCAN_IS_NOT( OPEN_SQUARE_PAREN ))
            {
                std::ostringstream msg;
                msg << "expecting: '[', found: '" << toString( current() )
                    << "'";
                log( msg );
            }
            ++m_scan;
            std::shared_ptr<BaseType const> itemType = parseType( m_scan.getPosition() );
            if( SCAN_IS_NOT( CLOSE_SQUARE_PAREN ))
            {
                std::ostringstream msg;
                msg << "expecting: ']', found: '" << toString( current() )
                    << "'";
                log( msg );
            }
            ++m_scan;
            return std::make_shared<ArrayType>( position, itemType );
        }

        std::shared_ptr<EnumType const>
        Parser::parseEnum( GenericParser::ReadingPosition const& position,
                           Partiality partiality )
        {
            std::shared_ptr<EnumType> enumType = std::make_shared<EnumType>( position, partiality );
            while( SCAN_IS_NOT( KEYWORD_END ))
            {
                if( SCAN_IS(SYMBOL) )
                {
                    EnumLabel label( m_scan.getPosition(), toString( current() ) );
                    enumType->addLabel( std::move(label) );
                    ++m_scan;
                    if( SCAN_IS(SEPARATOR_COMMA) )
                    {
                        ++m_scan;
                    }
                }
                else
                {
                    std::ostringstream msg;
                    msg << "expecting enum label, '" << toString( current() )
                        << "' found";
                    log( msg );
                    seek(m_tokenizer.KEYWORD_END);
                }
            }
            ++m_scan;
            return enumType;
        }


        std::shared_ptr<StringType const>
        Parser::parseString( GenericParser::ReadingPosition const& position )
        {
            if( SCAN_IS_NOT(OPEN_PAREN) )
            {
                return std::make_shared<StringType>( position, "" );
            }

            // we have a string template.
            std::shared_ptr<StringType const> stringType;
            ++m_scan;
            if( SCAN_IS(TYPE_ENUM) )
            {
                ++m_scan;
                std::shared_ptr<EnumType const> enumTemplate = parseEnum( m_scan.getPosition(), Partiality::COMPLETE );
                stringType = std::make_shared<StringType const>( position, enumTemplate );
            }
            else if( SCAN_IS(SYMBOL))
            {
                std::string typeTemplate = toString( current() );
                stringType = std::make_shared<StringType const>( position, typeTemplate );
                ++m_scan;
            }
            else
            {
                std::ostringstream msg;
                msg << "expecting a template name or an enumeration, '"
                    << toString( current() ) << "' found";
                log( msg );
                seek( m_tokenizer.CLOSE_PAREN );
            }
            if( SCAN_IS_NOT( CLOSE_PAREN ))
            {
                throw Errors::RightBananaExpected( m_scan.getPosition(),
                                                   toString( current() ));
            }
            ++m_scan;
            return stringType;
        }

        std::string Parser::parseSymbol()
        {
            assert( SCAN_IS(SYMBOL) );
            std::string symbol = toString( current() );
            ++m_scan;
            return symbol;
        }

        bool Parser::parseToken( Token const& token )
        {
            if( current() == token.id() )
            {
                ++m_scan;
                return true;
            }
            else
            {
                return false;
            }
        }

#define TOKEN_SWITCH    if( false )                                 \
                        {
#define CASE(X)         }                                           \
                        else if( current() == m_tokenizer.X.id() )  \
                        {
#define ELSE            }                                           \
                        else                                        \
                        {
#define END_SWITCH      }


        std::shared_ptr<BaseType const>
        Parser::parseType( GenericParser::ReadingPosition const& position )
        {
            TOKEN_SWITCH
                CASE(TYPE_RECORD)
                    ++m_scan;
                    return parseRecord( position, Partiality::COMPLETE );
                CASE(TYPE_ARRAY)
                    ++m_scan;
                    return parseArray( position );
                CASE(TYPE_BOOLEAN)
                    ++m_scan;
                    return std::make_shared<SimpleType>( position,
                                                         SimpleType::BOOL );
                CASE(TYPE_ENUM)
                    ++m_scan;
                    return parseEnum( position, Partiality::COMPLETE );
                CASE(TYPE_FLOAT)
                    ++m_scan;
                    return std::make_shared<SimpleType>( position,
                                                         SimpleType::FLOAT );
                CASE(TYPE_INT)
                    ++m_scan;
                    return std::make_shared<SimpleType>( position,
                                                         SimpleType::INT );
                CASE(TYPE_STRING)
                    ++m_scan;
                    return parseString( position );
            ELSE
                throw Errors::TypeExpected( m_scan.getPosition(), toString( current() ));
            END_SWITCH
        }

        void Parser::parseCompleteOrPartialType()
        {
            assert( SCAN_IS( KEYWORD_TYPE ) );
            auto position = m_scan.getPosition();
            assert( m_scan != m_end );
            ++m_scan;
            if( m_scan == m_end )
            {
                m_log.log( m_scan.getPosition(), "Unexpected end of file");
                ++m_errorsCount;
                return;
            }
            std::string typeName;
            if( !SCAN_IS( SYMBOL ))
            {
                std::ostringstream msg;
                msg << "Expecing symbol, found '" << toString( current() ) << "'";
                m_log.log( m_scan.getPosition(), msg.str() );
                ++m_errorsCount;
                typeName = "(unknown)";
            }
            else
            {
                typeName = parseSymbol();
            }
            if( !parseToken( m_tokenizer.SEPARATOR_COLON ) )
            {
                std::ostringstream msg;
                msg << "Expecing ':', found '" << toString( current() ) << "'";
                m_log.log( m_scan.getPosition(), msg.str() );
                ++m_errorsCount;
            }
            if( SCAN_IS( KEYWORD_PARTIAL ) )
            {
                ++m_scan;
                std::shared_ptr<BaseType const> partialType;
                TOKEN_SWITCH
                    CASE(TYPE_RECORD)
                        partialType = parseRecord( position, Partiality::PARTIAL );
                    CASE(TYPE_ENUM)
                        partialType = parseEnum( position, Partiality::PARTIAL );
                ELSE
                    std::ostringstream msg;
                    msg << "Only Record and Enum types can be partial";
                    m_log.log( m_scan.getPosition(), msg.str() );
                    ++m_errorsCount;
                END_SWITCH
                if( partialType )
                {
                    m_program.mergePartialType( typeName, partialType );
                }
            }
            else
            {
                std::shared_ptr<BaseType const> type = parseType( position );
                m_program.addType( typeName, type );
            }
        }

        Program
        Parser::parse()
        {
            m_errorsCount = 0;  // reset if you want to call this method
                                // again.
            m_scan = m_begin;
            m_program.clear();

            while( m_scan != m_end )
            {
                if( SCAN_IS( KEYWORD_TYPE ) )
                {
                    try
                    {
                        parseCompleteOrPartialType();
                    }
                    catch( Errors::BasicError const& error )
                    {
                        m_log.log( error.getPosition(), error.what() );
                        ++m_errorsCount;
                        seek( m_tokenizer.KEYWORD_TYPE );
                    }
                }
                else
                {
                    // error
                    std::ostringstream msg;
                    msg << "Unexpected token: '"
                        << toString( current() )
                        << "' (expecting keyword "
                        << m_tokenizer.KEYWORD_TYPE.definition() << ")";
                    log( msg );
                    seek( m_tokenizer.KEYWORD_TYPE );
                }
            }
            if( m_errorsCount == 0 )
            {
                return m_program;
            }
            else
            {
                // empty program is returned if one or more errors have been
                // encountered.
                return Program();
            }
        }
    }

    Program parse( TokenIterator begin,
                   TokenIterator end,
                   GenericParser::ErrorLogger& logger )
    {
        Parser parser( begin, end, logger );
        return parser.parse();
    }

    Program parse( std::string const& file,
                   std::string const& filename,
                   GenericParser::ErrorLogger& logger )
    {
        char const* textBegin = file.c_str();
        char const* textEnd = textBegin+file.size();
        Tydal::Tokenizer tokenizer;
        Tydal::lexer_type::iterator_type lexerBegin = tokenizer.begin( textBegin, textEnd );
        Tydal::lexer_type::iterator_type lexerEnd = tokenizer.end();

        Tydal::TokenIterator begin( tokenizer,
                                    filename,
                                    textBegin, // lexerBegin,
                                    textEnd ); // lexerEnd );
        Tydal::TokenIterator end(tokenizer);
        return Tydal::parse( begin, end, logger );
    }

    Program parse( std::string const& file, std::string const& filename )
    {
        ErrorFormatterTerse formatter;
        GenericParser::ErrorLogger logger( &formatter, std::cerr );
        return parse( file, filename, logger );
    }
}
