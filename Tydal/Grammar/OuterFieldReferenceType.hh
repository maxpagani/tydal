/**
 * @file Tydal/Grammar/OuterFieldReferenceType.hh
 * @author MaxP
 *
 * @date 2016-11-27 14:30
 */

#if !defined( TYDAL_GRAMMAR_OUTERFIELDREFERENCETYPE_HH )
#define TYDAL_GRAMMAR_OUTERFIELDREFERENCETYPE_HH

#include "Tydal/Grammar/BaseType.hh"

namespace Tydal
{
    namespace Grammar
    {
        /**
         * This type specifies a reference to an outer field (i.e. a field in
         * an enclosing record) that has a given name.
         *
         * The main use of this is for variants.
         */
        class OuterFieldReferenceType : public BaseType
        {
            public:
                explicit OuterFieldReferenceType( GenericParser::ReadingPosition const& position );
                virtual ~OuterFieldReferenceType() = default;

                std::string const& getOuterFieldName() const;

            private:
                
                virtual bool isTypeCompleteImpl() const;
                
                virtual std::string const& getTypeNameImpl() const;

                virtual std::shared_ptr<BaseType const>
                mergeImpl( std::shared_ptr<BaseType const> other ) const;
        };
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::: inline methods :::
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

    }
}


#endif /* TYDAL_GRAMMAR_OUTERFIELDREFERENCETYPE_HH */

