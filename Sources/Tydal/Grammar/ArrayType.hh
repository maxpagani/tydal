/**
 * @file Tydal/Grammar/ArrayType.hh
 * @author Massimiliano Pagani
 *
 * @date 2016-10-30, 02:25
 */

#if !defined( TYDAL_GRAMMAR_ARRAYTYPE_HH )
#define TYDAL_GRAMMAR_ARRAYTYPE_HH

#include "Tydal/Grammar/BaseType.hh"

namespace Tydal
{
    namespace Grammar
    {
        class ArrayType : public BaseType
        {
            public:
                ArrayType( GenericParser::ReadingPosition const& position,
                           std::shared_ptr<BaseType const> itemType );
                ArrayType( ArrayType const& ) = default;
                virtual ~ArrayType();

                std::shared_ptr<BaseType const> getItemType() const;
            private:
                std::shared_ptr<BaseType const> m_itemType;

                virtual bool isTypeCompleteImpl() const;
                virtual std::string const& getTypeNameImpl() const;

                virtual std::shared_ptr<BaseType const>
                mergeImpl( std::shared_ptr<BaseType const> other ) const;
        };

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::: inline methods :::
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

        inline std::shared_ptr<BaseType const> ArrayType::getItemType() const
        {
            return m_itemType;
        }

    }
}

#endif /* TYDAL_GRAMMAR_ARRAYTYPE_HH */

