/**
 * @file Tydal/Grammar/VariantCaseEntry.cc
 * @author MaxP
 *
 * @date 2016-11-27 15:08
 */

#include "Tydal/Grammar/VariantCaseEntry.hh"

namespace Tydal
{
    namespace Grammar
    {
        VariantCaseEntry::VariantCaseEntry( std::string const& literal,
                                            GenericParser::ReadingPosition const& position,
                                            std::shared_ptr<RecordType const> fields ) :
                              m_position{ position },
                              m_caseValue{ literal },
                              m_fields{ fields }
        {
        }

    }
}