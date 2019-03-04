/**
 * @file SimpleType.hh
 * @author apagani
 * @date 26 ottobre 2016, 8.35
 */

#if !defined( TYDAL_GRAMMAR_SIMPLETYPE_HH )
#define TYDAL_GRAMMAR_SIMPLETYPE_HH

#include "Tydal/Grammar/BaseType.hh"

namespace Tydal
{
    namespace Grammar
    {
        class SimpleType : public BaseType
        {
            public:
                enum Type
                {
                    INT,
                    FLOAT,
                    BOOL
                };
                SimpleType( GenericParser::ReadingPosition const& position,
                            Type type );
                SimpleType( const SimpleType& orig ) = delete;
                SimpleType& operator=( SimpleType const& ) = delete;
                SimpleType& operator=( SimpleType&& ) = delete;

                virtual ~SimpleType() = default;
                Type getType() const;
            private:
                Type m_type;

                virtual bool isTypeCompleteImpl() const;

                virtual std::shared_ptr<BaseType const>
                mergeImpl( std::shared_ptr<BaseType const> other ) const;

                virtual std::string const& getTypeNameImpl() const;

        };

        // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::: inline :::
        // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

        inline SimpleType::Type SimpleType::getType() const
        {
            return m_type;
        }
    }
}

#endif /* TYDAL_GRAMMAR_SIMPLETYPE_HH */
