/**
 * @addtogroup Tydal
 * @{
 * @file Tydal/Grammar/Program.hh
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-10-13
 *
 */

#if !defined( TYDAL_GRAMMAR_PROGRAM_HH )
#define TYDAL_GRAMMAR_PROGRAM_HH

#include <memory>
#include <map>
#include <vector>
#include "Tydal/Grammar/BaseType.hh"

namespace Tydal
{
    namespace Grammar
    {
        /** Program class identifies an entire Tydal program.
         *
         *
         *
         */
        class Program
        {
            public:
                typedef std::pair<std::string,
                                  std::shared_ptr<BaseType const>> TypeDefinition;
            private:
                /**
                 * One structure is for table lookup (TypeDefinitionMap, while
                 * the other is for definition sequence. This may go pearshaped
                 * when partial types are used.
                 */
                typedef std::vector<TypeDefinition> TypeDefinitionSequence;
                typedef TypeDefinitionSequence::size_type IndexType;
                typedef std::map<std::string,IndexType> TypeDefinitionMap;
            public:
                Program() = default;
                Program( Program const& ) = default;
                Program( Program&& ) = default;
                ~Program();

                /**
                 * Clears and resets the current program.
                 */
                void clear();

                /**
                 * Adds a type to the collection.
                 *
                 * @param name the name of the type.
                 * @param type the type to add. Note the argument is moved into
                 *             the program.
                 */
                bool addType( std::string const& name,
                              std::shared_ptr<BaseType const> type );

                /**
                 * Merge a partial type. If an existing partial type with the
                 * same name is found, then the two are merged, otherwise a new
                 * partial type is created with the content of the parameter.
                 *
                 * @param name the name of the type.
                 * @param type the partial type to merge. Note the argument is
                 *             moved into the program.
                 */
                bool mergePartialType( std::string const& name,
                                       std::shared_ptr<BaseType const> type );

                typedef TypeDefinitionSequence::const_iterator ConstIterator;

                ConstIterator begin() const;
                ConstIterator end() const;

            private:
                TypeDefinitionMap m_types;
                TypeDefinitionSequence m_sequence;
        };

        // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
        // :::::::::::::::::::::::::::::::::::::::::::::::: inline methods :::
        // :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

        inline Program::ConstIterator Program::begin() const
        {
            return m_sequence.begin();
        }

        inline Program::ConstIterator Program::end() const
        {
            return m_sequence.end();
        }

        inline void Program::clear()
        {
            m_types.clear();
            m_sequence.clear();
        }
    }  // end of namespace Grammar
}

#endif
///@}


