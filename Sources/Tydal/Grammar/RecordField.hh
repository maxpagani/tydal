/**
 * @addtogroup Tydal/Grammar
 * @{
 * @file Tydal/Grammar/RecordField.hh
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-11-04
 *
 */


#if !defined( TYDAL_GRAMMAR_RECORDFIELD_HH )
#define TYDAL_GRAMMAR_RECORDFIELD_HH

#include "GenericParser/ReadingPosition.hh"
#include "Tydal/Grammar/BaseType.hh"

namespace Tydal
{
    namespace Grammar
    {

        /** RecordField
         *
         * 
         *
         */

        class RecordField
        {
            public:
                enum Optionality
                {
                    REQUIRED,
                    OPTIONAL
                };
                
                RecordField( std::string const& name,
                             GenericParser::ReadingPosition const& position,
                             std::shared_ptr<BaseType const> type,
                             Optionality optionality );
                ~RecordField() = default;
                
                std::string const& getName() const;
                GenericParser::ReadingPosition const& getPosition() const;
                std::shared_ptr<BaseType const> getType() const;
                bool isOptional() const;
            private:
                std::string m_name;
                GenericParser::ReadingPosition m_position;
                std::shared_ptr<BaseType const> m_type;
                Optionality m_optionality;
        };
        
        // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        // ::::::::::::::::::::::::::::::::::::::::::::::::: inline methods :::
        // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        
        inline std::string const& RecordField::getName() const
        {
            return m_name;
        }
        
        inline GenericParser::ReadingPosition
        const& RecordField::getPosition() const
        {
            return m_position;
        }
        
        inline std::shared_ptr<BaseType const> RecordField::getType() const
        {
            return m_type;
        }

        inline bool RecordField::isOptional() const
        {
            return m_optionality == OPTIONAL;
        }

    }  // end of namespace Grammar
}   // end of namespace Tydal
#endif
///@}


