/**
 * @file main.cc
 * @author apagani
 * @date 15, 2016, 3:26 PM
 */

#include <fstream>
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <vector>
#include <algorithm>
#include <functional>
#include "GenericParser/ErrorFormatter.hh"
#include "Tydal/Tokenizer.hh"
#include "Tydal/Grammar/Program.hh"
#include "Tydal/Parser.hh"
#include "OutputTranslator/Tydal.hh"
#include "OutputTranslator/Factory.hh"
#include "Tydal/ErrorFormatterTerse.hh"
#include "GenericParser/ErrorLogger.hh"

namespace
{
    template<typename Iter,typename T, typename S>
    int
    parseStringToTokens( Iter begin, Iter end, T delim, std::vector<S>& result )
    {
        result.clear();
        Iter last = begin;
        while( begin != end )
        {
            if( *begin == delim )
            {
                result.push_back( S( last, begin ) );
                last = begin+1;
            }
            ++begin;
        }
        if( last != end )
        {
            result.push_back( S( last, end ) );
        }
        return result.size();
    }
}

namespace
{

    using Tydal::Grammar::Program;

    void
    usage( char const* argv0 )
    {
        std::cout <<"Usage:\n"
                    "  " << argv0 << " <file>\n";
    }

}


int main( int argc, char** argv )
{
    if( argc != 2 )
    {
        usage( argv[0] != nullptr ? argv[0] : "" );
        return EXIT_FAILURE;
    }
    std::ifstream in( argv[1] );
    if( !in )
    {
        std::cerr << "Can't open file '" << argv[1] << "'\n";
        return EXIT_FAILURE;
    }
    try
    {
        std::istreambuf_iterator<char> endOfInput;
        std::istreambuf_iterator<char> scan( in );
        std::string file( scan, endOfInput );

        Tydal::Grammar::Program program = Tydal::parse( file, argv[1] );
        OutputTranslator::Factory::getTranslatorFor( OutputTranslator::Factory::SCALA ).print( program, std::cout );
    }
    catch( boost::lexer::runtime_error const& e )
    {
        std::cerr << "lexer fatal: " << e.what() << "\n";
    }
    in.close();

    return EXIT_SUCCESS;
}

