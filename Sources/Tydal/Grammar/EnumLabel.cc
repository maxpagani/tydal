/**
 * @file EnumLabel.cc
 * @author apagani
 * @date 3 novembre 2016 8.43
 */

#include "Tydal/Grammar/EnumLabel.hh"

namespace Tydal
{
    namespace Grammar
    {
        EnumLabel::EnumLabel( GenericParser::ReadingPosition const& position,
                              std::string const& label ) :
                   m_position{ position },
                   m_label{ label }
        {
        }
    }
}


