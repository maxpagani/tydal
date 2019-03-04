/**
 * @file VariantType.hh
 * @author Max
 *
 * @date 2016-11-24 22:32
 */

#if !defined( TYDAL_GRAMMAR_VARIANTFIELD_HH )
#define TYDAL_GRAMMAR_VARIANTFIELD_HH

#include "Tydal/Grammar/BaseType.hh"
#include "GenericParser/ReadingPosition.hh"
#include "Tydal/Grammar/VariantCaseEntry.hh"
#include <vector>

namespace Tydal
{
    namespace Grammar
    {
        class VariantType : public BaseType
        {
            private:
                typedef std::vector<std::shared_ptr<VariantCaseEntry const>> CaseSetType;
            public:
                /**
                 * Build a variant type. The variant is a collection of records
                 * that are mutually exclusively selected according to a single
                 * field value. This field is common in every record.
                 * 
                 * @param position the position in the source file.
                 * @param fieldName the name of the discriminant field. This is
                 *                  part of the type because is involved in 
                 *                  field merging.
                 * @param fieldType the type of the discriminant field.
                 */
                
                VariantType( GenericParser::ReadingPosition const& position,
                              std::string const& fieldName,
                              std::shared_ptr<BaseType const> fieldType );
                VariantType( VariantType const& ) = default;
                virtual ~VariantType() = default;

                void addCase( std::shared_ptr<VariantCaseEntry const> caseEntry );

                typedef CaseSetType::const_iterator ConstIterator;
                ConstIterator begin() const;
                ConstIterator end() const;

                std::string const& getFieldName() const;
                
                std::shared_ptr<BaseType const> getFieldType() const;
            private:
                std::string const& m_symbol;
                std::shared_ptr<BaseType const> m_type;
                CaseSetType m_cases;
                
                virtual bool isTypeCompleteImpl() const;
                
                virtual std::string const& getTypeNameImpl() const;

                virtual std::shared_ptr<BaseType const>
                mergeImpl( std::shared_ptr<BaseType const> other ) const;
        };

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::: inline methods :::
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        inline void 
        VariantType::addCase( std::shared_ptr<VariantCaseEntry const> caseEntry )
        {
            m_cases.push_back( caseEntry );
        }

        inline VariantType::ConstIterator VariantType::begin() const
        {
            return m_cases.begin();
        }
        
        inline VariantType::ConstIterator VariantType::end() const
        {
            return m_cases.end();
        }

        inline std::string const& VariantType::getFieldName() const
        {
            return m_symbol;
        }

        inline std::shared_ptr<BaseType const> VariantType::getFieldType() const
        {
            return m_type;
        }

    }
}

#endif /* TYDAL_GRAMMAR_VARIANTFIELD_HH */

