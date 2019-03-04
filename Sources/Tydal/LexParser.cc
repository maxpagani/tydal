/**
 * @addtogroup Group
 * @{
 * @file LexParser.cc
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016/09/15
 *
 */

#include "Tydal/LexParser.hh"
#include <cassert>

namespace Tydal
{
    LexParser::LexParser( std::istream& in, std::string const& fileName ) :
               fileName_( fileName ),
               in_( in )
    {
        text_.push_back( "" );
    }

    int LexParser::getChar()
    {
        int c = in_.get();
        switch( c )
        {
            case '\n':
                text_.push_back( "" );
                break;
            case '\r':
                break;
            default:
                text_[ text_.size()-1 ].push_back( c );
                break;
        }
        return c;
    }

    bool LexParser::isEof() const
    {
        return in_.eof();
    }

    int LexParser::getLineNumber() const
    {
        return text_.size();
    }

    int LexParser::getColumnNumber() const
    {
        size_t lineNumber = text_.size();
        return text_[lineNumber-1].size();
    }

    std::string const&
    LexParser::getCurrentLineText() const
    {
        size_t lineNumber = text_.size();
        return text_[lineNumber-1];
    }

    std::string const& LexParser::getLineText( int line ) const
    {
        assert( line > 0 );
        assert( static_cast<size_t>(line) <= text_.size() );
        return text_[line];
    }

    std::string const& LexParser::getFileName() const
    {
        return fileName_;
    }

}
///@}


