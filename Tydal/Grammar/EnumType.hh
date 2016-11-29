/**
 * @file Tydal/Grammar/EnumType.hh
 * @author Massimiliano Pagani
 *
 * @date 2016-10-30, 02:43
 */

#if !defined( TYDAL_GRAMMAR_ENUMTYPE_HH )
#define TYDAL_GRAMMAR_ENUMTYPE_HH

#include "Tydal/Grammar/BaseType.hh"
#include "Tydal/Grammar/EnumLabel.hh"
#include "Tydal/Grammar/Partiality.hh"
#include <set>
#include <string>

namespace Tydal
{
    namespace Grammar
    {
        class EnumType : public BaseType
        {
            private:
                typedef std::set<EnumLabel> Labels;

            public:
                EnumType( GenericParser::ReadingPosition const& position,
                          Partiality completeOrPartial );
                EnumType( EnumType const& ) = default;
                virtual ~EnumType() = default;

                typedef Labels::const_iterator ConstIterator;
                ConstIterator begin() const;
                ConstIterator end() const;

                void addLabel( EnumLabel const& label );
                void addLabel( EnumLabel&& label );

                bool hasLabel( std::string const& label ) const;
            private:
                Labels m_labels;
                bool m_isComplete;

                virtual bool isTypeCompleteImpl() const noexcept;
                virtual std::string const& getTypeNameImpl() const;

                virtual std::shared_ptr<BaseType const>
                mergeImpl( std::shared_ptr<BaseType const> other ) const;
        };

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::: inline methods :::
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

        inline EnumType::ConstIterator EnumType::begin() const
        {
            return m_labels.begin();
        }

        inline EnumType::ConstIterator EnumType::end() const
        {
            return m_labels.end();
        }
    }
}

#endif /* TYDAL_GRAMMAR_ENUMTYPE_HH */

