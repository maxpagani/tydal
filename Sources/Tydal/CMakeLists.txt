add_subdirectory( Errors )
add_subdirectory( Grammar )

target_sources( tydal
    PRIVATE
        BaseTokenizer.cc
        BaseTokenizer.hh
        ErrorFormatterTerse.cc
        ErrorFormatterTerse.hh
        LexParser.cc
        LexParser.hh
        Parser.cc
        Parser.hh
        Token.hh
        TokenIterator.cc
        TokenIterator.hh
        Tokenizer.cc
        Tokenizer.hh
)
