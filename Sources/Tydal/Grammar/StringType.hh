/**
 * @file Tydal/Grammar/StringType.hh
 * @author Massimiliano Pagani
 *
 * @date 2016-10-30, 02:43
 */

#if !defined( TYDAL_GRAMMAR_STRINGTYPE_HH )
#define TYDAL_GRAMMAR_STRINGTYPE_HH

#include "Tydal/Grammar/BaseType.hh"
#include "EnumType.hh"
#include <cassert>

namespace Tydal
{
    namespace Grammar
    {
        class StringType : public BaseType
        {
            public:
                StringType( GenericParser::ReadingPosition const& position,
                            std::string const& specification );
                StringType( GenericParser::ReadingPosition const& position,
                            std::shared_ptr<EnumType const> specification );
                StringType( StringType const& ) = default;
                virtual ~StringType();

                enum SpecificationType
                {
                    NONE,
                    REFERENCE,
                    REGEXP,
                    ENUM,
                };
                
                std::string const& getSpecification() const;
                std::shared_ptr<EnumType const> getEnumSpecification() const;
                
                SpecificationType getSpecificationType() const;
                
            private:
                std::string m_specification;
                std::shared_ptr<EnumType const> m_enumSpecification;
                SpecificationType m_specificationType;
                
                virtual bool isTypeCompleteImpl() const;

                virtual std::shared_ptr<BaseType const>
                mergeImpl( std::shared_ptr<BaseType const> other ) const;

                virtual std::string const& getTypeNameImpl() const;
        };

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::: inline methods :::
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

        inline std::string const& StringType::getSpecification() const
        {
            assert( m_specificationType == REFERENCE );
            return m_specification;
        }

        inline std::shared_ptr<EnumType const>
        StringType::getEnumSpecification() const
        {
            assert( m_specificationType == ENUM );
            return m_enumSpecification;
        }
        
        inline StringType::SpecificationType StringType::getSpecificationType() const
        {
            return m_specificationType;
        }
    }
}

#endif /* TYDAL_GRAMMAR_ARRAYTYPE_HH */

