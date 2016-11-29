/**
 * @addtogroup OutputTranslator
 * @{
 * @file OutputTranslator/Base.hh
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-10-17
 *
 */

#if !defined( OUTPUTTRANSLATOR_BASE_HH )
#define OUTPUTTRANSLATOR_BASE_HH

#include <iosfwd>
#include "Tydal/Grammar/Program.hh"
#include "Tydal/Grammar/StringType.hh"
#include "Tydal/Grammar/ArrayType.hh"
#include "Tydal/Grammar/SimpleType.hh"
#include "Tydal/Grammar/EnumType.hh"
#include "Tydal/Grammar/RecordType.hh"
#include <cassert>

namespace OutputTranslator
{
    struct IndentFiller
    {
        int m_margin;
    };

    class Base
    {
        public:
            virtual ~Base() = default;

            /** print
             *
             * outputs a tydal program in a given language.
             *
             * @param out the output stream.
             * @param program the program to print.
             */
            void print( Tydal::Grammar::Program const& program, std::ostream& out );
        protected:
            IndentFiller margin() const;
            void indent();
            void outdent();
        private:
            virtual void startTranslation( Tydal::Grammar::Program const& program,
                                           std::ostream& out );
            virtual void endTranslation( Tydal::Grammar::Program const& program,
                                         std::ostream& out );
            virtual void translateRecord( std::string const& name,
                                          std::shared_ptr<Tydal::Grammar::RecordType const> recordType,
                                          std::ostream& out ) = 0;
            virtual void translateEnum( std::string const& name,
                                          std::shared_ptr<Tydal::Grammar::EnumType const> enumType,
                                          std::ostream& out ) = 0;
            virtual void translateString( std::string const& name,
                                          std::shared_ptr<Tydal::Grammar::StringType const> stringType,
                                          std::ostream& out ) = 0;
            virtual void translateSimpleType( std::string const& name,
                                          std::shared_ptr<Tydal::Grammar::SimpleType const> simpleType,
                                          std::ostream& out ) = 0;
            virtual void translateArray( std::string const& name,
                                         std::shared_ptr<Tydal::Grammar::ArrayType const> arrayType,
                                         std::ostream& out ) = 0;

            int m_indent = 0;
            int m_indentWidth = 4;
    };

    std::ostream& operator<<( std::ostream& out, IndentFiller filler );

    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // ::::::::::::::::::::::::::::::::::::::::::::::::::::: inline methods :::
    // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    inline void Base::indent()
    {
        m_indent += m_indentWidth;
    }

    inline void Base::outdent()
    {
        m_indent -= m_indentWidth;
        assert( m_indent >= 0 );
    }

    inline IndentFiller Base::margin() const
    {
        return IndentFiller{ m_indent };
    }

}  // end of namespace OutputTranslator

#endif
///@}


