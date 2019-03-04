/**
 * @file OutputTranslator/Base.cc
 * @author Massimiliano Pagani
 *
 * @date 2016-11-05 11:10:42
 */

#include "OutputTranslator/Base.hh"
#include <cassert>
#include <memory>
#include <iostream>

namespace OutputTranslator
{
    using namespace Tydal::Grammar;

    void Base::print( Tydal::Grammar::Program const& program,
                      std::ostream& out )
    {
        startTranslation( program, out );
        for( auto type : program )
        {
            auto recordType = std::dynamic_pointer_cast<RecordType const>(type.second);
            if( recordType )
            {
                translateRecord( type.first, recordType, out );
                continue;
            }
            auto enumType = std::dynamic_pointer_cast<EnumType const>(type.second);
            if( enumType )
            {
                translateEnum( type.first, enumType, out );
                continue;
            }
            auto arrayType = std::dynamic_pointer_cast<ArrayType const>(type.second);
            if( arrayType )
            {
                translateArray( type.first, arrayType, out );
                continue;
            }
            auto simpleType = std::dynamic_pointer_cast<SimpleType const>(type.second);
            if( simpleType )
            {
                translateSimpleType( type.first, simpleType, out );
                continue;
            }
            auto stringType = std::dynamic_pointer_cast<StringType const>(type.second);
            if( stringType )
            {
                translateString( type.first, stringType, out );
                continue;
            }
            // if I'm here there is an unknown type.
            assert(false);
        }
        endTranslation( program, out );
    }

    void Base::startTranslation( Program const&, std::ostream& )
    {
    }

    void Base::endTranslation( Program const&, std::ostream& )
    {
    }

    std::ostream& operator<<( std::ostream& out, IndentFiller filler )
    {
        for( int i=0; i<filler.m_margin; ++i )
        {
            out << ' ';
        }
        return out;
    }


}
