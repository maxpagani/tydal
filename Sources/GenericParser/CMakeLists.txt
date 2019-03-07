cmake_minimum_required(VERSION 3.6)

target_sources( tydal
    PRIVATE
        GenericParser/ErrorFormatter.cc
        GenericParser/ErrorFormatter.hh
        GenericParser/ErrorLogger.cc
        GenericParser/ErrorLogger.hh
        GenericParser/lex.hh
        GenericParser/ReadingPosition.cc
        GenericParser/ReadingPosition.hh
    )