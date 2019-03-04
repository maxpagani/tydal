/**
 * @file Tydal/TokenIterator.hh
 * @author apagani
 * @date 2016-09-28
 */

 #if !defined( TYDAL_TOKEN_ITERATOR_HH )
 #define TYDAL_TOKEN_ITERATOR_HH

#include "Tydal/Tokenizer.hh"
#include "GenericParser/ReadingPosition.hh"

 namespace Tydal
 {
    class TokenIterator
    {
        public:
            template<typename Iter>
            TokenIterator( Tokenizer& tokenizer,
                           std::string const& fileName,
                           Iter& begin,
                           Iter& end );

            TokenIterator( Tokenizer& tokenizer );

            /**
             * Assignment operator. Note that you can assign only among token
             * iterators of the same tokenizer.
             *
             * @param source the token iterator you want to copy from.
             * @return a reference to *this.
             */
            TokenIterator& operator=( TokenIterator const& source );

            token_type const& operator*() const;
            TokenIterator& operator++();

            bool isEof() const;
            GenericParser::ReadingPosition const& getPosition() const;

            Tokenizer const&
            getTokenizer() const;
        private:
            template<typename V>
            void updatePosition( V const& value );

            bool
            isBlank( lexer_type::iterator_type::value_type const& token ) const;

            void skipBlanks();

            friend bool operator==( TokenIterator const& a,
                                    TokenIterator const& b );

            lexer_type::iterator_type m_iter;
            lexer_type::iterator_type m_end;
            GenericParser::ReadingPosition m_position;
            Tokenizer& m_tokenizer;
    };

    bool operator!=( TokenIterator const& a, TokenIterator const& b );

    bool operator==( TokenIterator const& a, TokenIterator const& b );

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::: inline methods :::
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    inline token_type const& TokenIterator::operator*() const
    {
        return *m_iter;
    }

    inline bool operator==( TokenIterator const& a, TokenIterator const& b )
    {
        return a.m_iter == b.m_iter;
    }

    inline bool TokenIterator::isEof() const
    {
        return m_iter == m_end;
    }

    inline GenericParser::ReadingPosition const& TokenIterator::getPosition() const
    {
        return m_position;
    }

    inline Tokenizer const&
    TokenIterator::getTokenizer() const
    {
        return m_tokenizer;
    }

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::: template methods :::
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    template<typename Iter>
    TokenIterator::TokenIterator( Tokenizer& tokenizer,
                                  std::string const& fileName,
                                  Iter& begin,
                                  Iter& end ) :
                   m_iter{ tokenizer.begin( begin, end ) },
                   m_end{ tokenizer.end() },
                   m_position{ fileName },
                   m_tokenizer{tokenizer }
    {
        skipBlanks();
    }

    template<typename V>
    void TokenIterator::updatePosition( V const& value )
    {
        for( auto scan : value )
        {
            switch( scan )
            {
                case '\n':
                    m_position.newLine();
                    break;
                default:
                    m_position.moveColumn( 1 );
                    break;
            }
        }
    }

    inline bool operator!=( TokenIterator const& a, TokenIterator const& b )
    {
        return !(a == b);
    }
}

#endif