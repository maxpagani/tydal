/**
 * @addtogroup Group
 * @{
 * @file GenericParser/ReadingPosition.hh
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 27/05/2010
 *
 */

#if !defined( GENERICPARSER_READINGPOSITION_HH )
#define GENERICPARSER_READINGPOSITION_HH

#include <string>

namespace GenericParser
{
    /** ReadingPosition
     *
     * 
     *
     */

    class ReadingPosition
    {
        public:
            ReadingPosition( std::string const& fileName ="",
                             int line = 1,
                             int column = 1 );
            ReadingPosition( ReadingPosition const& copy ) = default;
            ReadingPosition& operator=( ReadingPosition const& copy );

            void swap( ReadingPosition& other );

            ~ReadingPosition() = default;

            std::string const& getFileName() const;
            int getLineNumber() const;
            int getColumnNumber() const;
            std::string const& getLineText() const;

            void newLine();
            void moveColumn( int offset );
            void setCurrentLine( std::string const& currentLine );

        private:
            std::string fileName_;
            int line_;
            int column_;
            std::string lineText_;
    };
}

#endif
///@}


