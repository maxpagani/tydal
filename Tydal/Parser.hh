/**
 * @file Tydal/Parser.cc
 * @author apagani
 * @date September 19, 2016 1:55 PM
 */

#if !defined( TYDALPARSER_HH )
#define TYDALPARSER_HH

#include "Tydal/TokenIterator.hh"
#include "GenericParser/ErrorLogger.hh"
#include "Tydal/Grammar/Program.hh"
#include <string>

namespace Tydal
{
    Grammar::Program parse( TokenIterator begin,
                            TokenIterator end,
                            GenericParser::ErrorLogger& logger );

    Grammar::Program parse( std::string const& file,
                            std::string const& filename );

}

#endif /* TYDALPARSER_HH */

