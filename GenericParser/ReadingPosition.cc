/**
 * @addtogroup Group
 * @{
 * @file GenericParser/ReadingPosition.cc
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 27/05/2010
 *
 */

#include "GenericParser/ReadingPosition.hh"

namespace GenericParser
{
    ReadingPosition::ReadingPosition( std::string const& fileName,
                                      int line,
                                      int column ) :
                     fileName_( fileName ),
                     line_( line ),
                     column_( column )
    {
    }

    void
    ReadingPosition::swap( ReadingPosition& other )
    {
        fileName_.swap( other.fileName_ );
        std::swap( line_, other.line_ );
        std::swap( column_, other.column_ );
        std::swap( lineText_, other.lineText_ );
    }

    ReadingPosition& ReadingPosition::operator=( ReadingPosition const& copy )
    {
        ReadingPosition tmp( copy );
        swap( tmp );
        return *this;
    }

    std::string const& ReadingPosition::getFileName() const
    {
        return fileName_;
    }

    int ReadingPosition::getLineNumber() const
    {
        return line_;
    }

    int ReadingPosition::getColumnNumber() const
    {
        return column_;
    }

    std::string const& ReadingPosition::getLineText() const
    {
        return lineText_;
    }

    void
    ReadingPosition::newLine()
    {
        line_ += 1;
        column_ = 1;
        lineText_ = "";
    }

    void
    ReadingPosition::moveColumn( int offset )
    {
        column_ += offset;
    }

    void
    ReadingPosition::setCurrentLine( std::string const& currentLine )
    {
        lineText_ = currentLine;
    }
}

///@}


