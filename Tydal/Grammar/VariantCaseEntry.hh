/**
 * @file Tydal/Grammar/VariantCaseEntry.hh
 * @author MaxP
 *
 * @date 2016-11-25, 22:04
 */

#if !defined( TYDAL_GRAMMAR_VARIANTCASEENRY_HH )
#define TYDAL_GRAMMAR_VARIANTCASEENRY_HH

#include <memory>
#include <vector>
#include "Tydal/Grammar/RecordField.hh"
#include "RecordType.hh"

namespace Tydal
{
    namespace Grammar
    {
        class VariantCaseEntry
        {
            public:
                VariantCaseEntry( std::string const& literal,
                                  GenericParser::ReadingPosition const& position,
                                  std::shared_ptr<RecordType const> fields );
                virtual ~VariantCaseEntry() = default;

                std::string const& getCaseValue() const;

                typedef RecordType::ConstIterator ConstIterator;

                ConstIterator begin() const;
                ConstIterator end() const;
            private:
                GenericParser::ReadingPosition m_position;
                std::string m_caseValue;
                std::shared_ptr<RecordType const> m_fields;
        };

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::: inline methods :::
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

        inline std::string const&
        VariantCaseEntry::getCaseValue() const
        {
            return m_caseValue;
        }

        inline VariantCaseEntry::ConstIterator VariantCaseEntry::begin() const
        {
            return m_fields->begin();
        }

        inline VariantCaseEntry::ConstIterator VariantCaseEntry::end() const
        {
            return m_fields->end();
        }

    }
}

#endif /* TYDAL_GRAMMAR_VARIANTCASEENRY_HH */

