add_subdirectory( Errors )
add_subdirectory( Grammar )

target_sources( tydal
    PRIVATE
        Tydal/BaseTokenizer.cc
        Tydal/BaseTokenizer.hh
        Tydal/ErrorFormatterTerse.cc
        Tydal/ErrorFormatterTerse.hh
        Tydal/LexParser.cc
        Tydal/LexParser.hh
        Tydal/Parser.cc
        Tydal/Parser.hh
        Tydal/Token.hh
        Tydal/TokenIterator.cc
        Tydal/TokenIterator.hh
        Tydal/Tokenizer.cc
        Tydal/Tokenizer.hh )