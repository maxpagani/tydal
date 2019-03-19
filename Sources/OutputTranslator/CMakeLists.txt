cmake_minimum_required(VERSION 3.6)

target_sources( tydal
    PRIVATE
        OutputTranslator/Base.cc
        OutputTranslator/Base.hh
        OutputTranslator/CPlusPlus.cc
        OutputTranslator/CPlusPlus.hh
        OutputTranslator/Factory.cc
        OutputTranslator/Factory.hh
        OutputTranslator/Java.cc
        OutputTranslator/Java.hh
        OutputTranslator/Scala.cc
        OutputTranslator/Scala.hh
        OutputTranslator/Tydal.cc
        OutputTranslator/Tydal.hh)