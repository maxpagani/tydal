/**
 * @file Tydal/TokenIterator.cc
 * @author apagani
 * @date 2016-09-28
 */

#include <Tydal/TokenIterator.hh>
#include <cassert>

namespace Tydal
{
    TokenIterator::TokenIterator( Tokenizer& tokenizer ) :
                   m_iter{ tokenizer.end() },
                   m_end{ tokenizer.end() },
                   m_position{""},
                   m_tokenizer{ tokenizer }
    {
    }

    TokenIterator&
    TokenIterator::operator=( const TokenIterator& source )
    {
        if( &source != this )
        {
            m_iter = source.m_iter;
            m_end = source.m_end;
            m_position = source.m_position;
            assert( &m_tokenizer == &source.m_tokenizer );
        }
        return *this;
    }

    bool
    TokenIterator::isBlank( lexer_type::iterator_type::value_type const& token ) const
    {
        return  token == m_tokenizer.BLANK.id() ||
                token == m_tokenizer.COMMENT.id() ||
                token == m_tokenizer.NEWLINE.id();
    }

    void
    TokenIterator::skipBlanks()
    {
        while( m_iter != m_end && isBlank( *m_iter ))
        {
            updatePosition( (*m_iter).value() );
            ++m_iter;
        }
    }


    TokenIterator& TokenIterator::operator++()
    {
        if( m_iter != m_end )
        {
            updatePosition( (*m_iter).value() );
            ++m_iter;
            skipBlanks();
        }
        return *this;
    }


}