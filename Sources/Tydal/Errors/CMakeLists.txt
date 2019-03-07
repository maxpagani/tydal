cmake_minimum_required(VERSION 3.6)

target_sources( tydal
    PRIVATE
        Tydal/Errors/BasicError.cc
        Tydal/Errors/BasicError.hh
        Tydal/Errors/CantMergeCompleteType.cc
        Tydal/Errors/CantMergeCompleteType.hh
        Tydal/Errors/CantMergeDifferentTypes.cc
        Tydal/Errors/CantMergeDifferentTypes.hh
        Tydal/Errors/CantMergeDuplicateEnumLabels.cc
        Tydal/Errors/CantMergeDuplicateEnumLabels.hh
        Tydal/Errors/CantMergeDuplicateRecordFields.cc
        Tydal/Errors/CantMergeDuplicateRecordFields.hh
        Tydal/Errors/ColonExpected.cc
        Tydal/Errors/ColonExpected.hh
        Tydal/Errors/DuplicatedRecordField.cc
        Tydal/Errors/DuplicatedRecordField.hh
        Tydal/Errors/DuplicateEnumLabel.cc
        Tydal/Errors/DuplicateEnumLabel.hh
        Tydal/Errors/InvalidLiteral.cc
        Tydal/Errors/InvalidLiteral.hh
        Tydal/Errors/InvalidVariantType.cc
        Tydal/Errors/InvalidVariantType.hh
        Tydal/Errors/RightBananaExpected.cc
        Tydal/Errors/RightBananaExpected.hh
        Tydal/Errors/SymbolExpected.cc
        Tydal/Errors/SymbolExpected.hh
        Tydal/Errors/TypeExpected.cc
        Tydal/Errors/TypeExpected.hh
)