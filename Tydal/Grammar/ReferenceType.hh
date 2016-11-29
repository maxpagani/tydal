/**
 * @file Tydal/Grammar/ReferenceType.hh
 * @author MaxP
 *
 * @date 2016-11-26 22:19
 */

#if !defined( TYDAL_GRAMMAR_REFERENCETYPE_HH )
#define TYDAL_GRAMMAR_REFERENCETYPE_HH

#include "Tydal/Grammar/BaseType.hh"

namespace Tydal
{
    namespace Grammar
    {
        class ReferenceType : public BaseType
        {
            public:
                ReferenceType( GenericParser::ReadingPosition const& position,
                               std::string const& typeReferenceName );
                virtual ~ReferenceType() = default;

                std::string const& getTypeName() const;
                
                void bindTo( std::shared_ptr<BaseType const> realType );
                std::shared_ptr<BaseType const> getBoundType() const;
            private:
                std::string m_typeReferenceName;
                std::shared_ptr<BaseType const> m_boundType;
                std::string m_typeDescription;
                
                virtual bool isTypeCompleteImpl() const;
                virtual std::string const& getTypeNameImpl() const;

                virtual std::shared_ptr<BaseType const>
                mergeImpl( std::shared_ptr<BaseType const> other ) const;
        };

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::: inline methods :::
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

        inline std::string const&
        ReferenceType::getTypeName() const
        {
            return m_typeReferenceName;
        }
        
        inline std::shared_ptr<BaseType const> 
        ReferenceType::getBoundType() const
        {
            return m_boundType;
        }
    }
}

#endif /* TYDAL_GRAMMAR_REFERENCETYPE_HH */

