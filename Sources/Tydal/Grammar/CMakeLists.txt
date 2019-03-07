cmake_minimum_required(VERSION 3.6)

target_sources( tydal
    PRIVATE
        Tydal/Grammar/AnonymousRecord.cc
        Tydal/Grammar/AnonymousRecord.hh
        Tydal/Grammar/ArrayType.cc
        Tydal/Grammar/ArrayType.hh
        Tydal/Grammar/BaseType.cc
        Tydal/Grammar/BaseType.hh
        Tydal/Grammar/EnumLabel.cc
        Tydal/Grammar/EnumLabel.hh
        Tydal/Grammar/EnumType.cc
        Tydal/Grammar/EnumType.hh
        Tydal/Grammar/OuterFieldReferenceType.cc
        Tydal/Grammar/OuterFieldReferenceType.hh
        Tydal/Grammar/Partiality.hh
        Tydal/Grammar/Program.cc
        Tydal/Grammar/Program.hh
        Tydal/Grammar/RecordField.cc
        Tydal/Grammar/RecordField.hh
        Tydal/Grammar/RecordType.cc
        Tydal/Grammar/RecordType.hh
        Tydal/Grammar/ReferenceType.cc
        Tydal/Grammar/ReferenceType.hh
        Tydal/Grammar/SimpleType.cc
        Tydal/Grammar/SimpleType.hh
        Tydal/Grammar/StringType.cc
        Tydal/Grammar/StringType.hh
        Tydal/Grammar/VariantCaseEntry.cc
        Tydal/Grammar/VariantCaseEntry.hh
        Tydal/Grammar/VariantType.cc
        Tydal/Grammar/VariantType.hh
)