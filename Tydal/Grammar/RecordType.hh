/**
 * @file Tydal/Grammar/RecordType.hh
 * @author Massimiliano Pagani
 *
 * @date 2016-10-30, 01:49
 */


#if !defined( TYDAL_GRAMMAR_RECORDTYPE_HH )
#define TYDAL_GRAMMAR_RECORDTYPE_HH

#include "Tydal/Grammar/BaseType.hh"
#include "Tydal/Grammar/RecordField.hh"
#include "Tydal/Grammar/Partiality.hh"
#include <memory>
#include <map>

namespace Tydal
{
    namespace Grammar
    {
        class RecordType : public BaseType
        {
            private:
                typedef std::map<std::string,std::shared_ptr<RecordField const>> FieldMap;
            public:
                RecordType( GenericParser::ReadingPosition const& position,
                            Partiality partiality );

                RecordType( RecordType const& orig) = default;
                virtual ~RecordType() = default;

                void addField( std::shared_ptr<RecordField const> field );

                typedef FieldMap::const_iterator ConstIterator;

                ConstIterator begin() const;
                ConstIterator end() const;
            private:
                FieldMap m_fields;
                bool m_isComplete;

                virtual bool isTypeCompleteImpl() const;
                virtual std::string const& getTypeNameImpl() const;
                virtual std::shared_ptr<BaseType const>
                mergeImpl( std::shared_ptr<BaseType const> other ) const;

        };

// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::: inline methods :::
// ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

        inline RecordType::ConstIterator RecordType::begin() const
        {
            return m_fields.begin();
        }

        inline RecordType::ConstIterator RecordType::end() const
        {
            return m_fields.end();
        }

        inline auto begin( RecordType const& record )
        {
            return record.begin();
        }

        inline auto end( RecordType const& record )
        {
            return record.end();
        }
    }
}


#endif /* TYDAL_GRAMMAR_RECORDTYPE_HH */

