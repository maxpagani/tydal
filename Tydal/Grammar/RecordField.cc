/**
 * @addtogroup Tydal/Grammar
 * @{
 * @file Tydal/Grammar/RecordField.cc
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-11-04
 *
 */

#include "Tydal/Grammar/RecordField.hh"

namespace Tydal
{
    namespace Grammar
    {
        RecordField::RecordField( std::string const& name,
                                  GenericParser::ReadingPosition const& position,
                                  std::shared_ptr<BaseType const> type,
                                  Optionality optionality ) :
                     m_name{ name },
                     m_position{ position },
                     m_type{ type },
                     m_optionality{ optionality }
        {
        }
    }  // end of namespace Grammar
}  // end of namespace Tydal
///@}


