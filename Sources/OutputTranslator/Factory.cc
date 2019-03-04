/**
 * @file OutputTranslator/Factory.cc
 * @author Massimiliano Pagani
 *
 * @date 2016-10-22 16:12:18
 */

#include "OutputTranslator/Factory.hh"
#include "OutputTranslator/Java.hh"
#include "OutputTranslator/CPlusPlus.hh"
#include "OutputTranslator/Scala.hh"
#include "OutputTranslator/Tydal.hh"
#include <cassert>

namespace OutputTranslator
{
    Base&
    Factory::getTranslatorFor( LanguageType type )
    {
        static Java java;
        static CPlusPlus cPlusPlus;
        static Scala scala;
        static Tydal tydal;

        switch( type )
        {
            case JAVA:
                return java;

            case C_PLUS_PLUS:
                return cPlusPlus;

            case SCALA:
                return scala;

            case TYDAL:
                return tydal;

            default:
                assert( false );
                return tydal;   // just to shut up the warning.
        }
    }


}