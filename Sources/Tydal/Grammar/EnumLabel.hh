/**
 * @file EnumLabel.h
 * @author apagani
 * @date 3 novembre 2016, 8.43
 */

#if !defined( TYDAL_GRAMMAR_ENUMLABEL_HH )
#define TYDAL_GRAMMAR_ENUMLABEL_HH

#include "GenericParser/ReadingPosition.hh"

namespace Tydal
{
    namespace Grammar
    {
        class EnumLabel 
        {
            public:
                EnumLabel( GenericParser::ReadingPosition const& position,
                           std::string const& label );
                EnumLabel(const EnumLabel& orig) = default;
                ~EnumLabel() = default;

                GenericParser::ReadingPosition const&
                getPosition() const;

                std::string const&
                getLabelName() const;
            private:
                GenericParser::ReadingPosition m_position;
                std::string m_label;
        };
        
        bool operator==( EnumLabel const& a, EnumLabel const& b );
        bool operator<( EnumLabel const& a, EnumLabel const& b );
        // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        // ::::::::::::::::::::::::::::::::::::::::::::::::: inline methods :::
        // ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

        inline GenericParser::ReadingPosition const&
        EnumLabel::getPosition() const
        {
            return m_position;
        }

        inline std::string const&
        EnumLabel::getLabelName() const
        {
            return m_label;
        }

        inline bool operator==( EnumLabel const& a, EnumLabel const& b )
        {
            return a.getLabelName() == b.getLabelName();
        }

        inline bool operator<( EnumLabel const& a, EnumLabel const& b )
        {
            return a.getLabelName() < b.getLabelName();
        }

    }
}



#endif /* TYDAL_GRAMMAR_ENUMLABEL_HH */
