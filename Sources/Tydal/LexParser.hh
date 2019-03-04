/**
 * @addtogroup Group
 * @{
 * @file LexParser.hh
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016/09/15 
 *
 */


#if !defined( TYDAL_LEXPARSER_HH )
#define TYDAL_LEXPARSER_HH

#include <iostream>
#include <string>
#include <vector>

namespace Tydal
{
    /** Lexical Parser.
     * This class parses the input splitting into characters. Moreover the class
     * keeps track of the whole text so that lines can later be retrieved.
     *
     * Also the Lexical parser keeps track of the current line and column.
     */

    class LexParser
    {
        public:
            /**
             * Constructor.
             *
             * @param in the stream to parse.
             * @param fileName the file name of the stream.
             */
            LexParser( std::istream& in, std::string const& fileName );
            ~LexParser() = default;
            LexParser( LexParser const& copy ) = delete;
            LexParser& operator=( LexParser const& copy ) = delete;

            int getChar();
            int getLineNumber() const;
            int getColumnNumber() const;
            std::string const& getCurrentLineText() const;
            std::string const& getLineText( int line ) const;
            bool isEof() const;
            std::string const& getFileName() const;
        private:

            std::vector<std::string> text_;
            std::string fileName_;
            std::istream& in_;
    };
}

#endif
///@}


