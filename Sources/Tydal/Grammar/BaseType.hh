/**
 * @addtogroup Group
 * @{
 * @file Tydal/Grammar/Type.hh
 * @author Massimiliano Pagani
 * @version 1.0
 * @date 2016-10-24
 *
 */


#if !defined( TYDAL_GRAMMAR_TYPE_HH )
#define TYDAL_GRAMMAR_TYPE_HH

#include <string>
#include <memory>
#include "GenericParser/ReadingPosition.hh"

namespace Tydal
{
    namespace Grammar
    {

        /**
         * Type is the base class for all different types.
         *
         * A type has a name to identify it.
         *
         *
         */

        class BaseType
        {
            public:
                explicit BaseType( GenericParser::ReadingPosition const& position );
                virtual ~BaseType() = default;
                BaseType( BaseType const& copy ) = default;
                BaseType( BaseType&& copy ) = default;
                BaseType& operator=( BaseType const& copy ) = default;

                GenericParser::ReadingPosition const& getPosition() const;
                std::string const& getTypeName() const;

                bool isComplete() const;
                bool isPartial() const;

                std::shared_ptr<BaseType const>
                merge( std::shared_ptr<BaseType const> other ) const;
            private:
                GenericParser::ReadingPosition m_position;

                virtual bool isTypeCompleteImpl() const = 0;
                virtual std::string const& getTypeNameImpl() const = 0;

                /**
                 * Heirs must implement this method for merging this type with
                 * another one and return the resulting type.
                 * 
                 * The business logic will call this only for mergeable types.
                 *
                 * @param other the type to merge with.
                 * @return the merged type or an invalid pointer.
                 */
                virtual std::shared_ptr<BaseType const>
                mergeImpl( std::shared_ptr<BaseType const> other ) const = 0;
        };

// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::: inline methods :::
// :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

        inline GenericParser::ReadingPosition const&
        BaseType::getPosition() const
        {
            return m_position;
        }

        inline bool
        BaseType::isComplete() const
        {
            return isTypeCompleteImpl();
        }

        inline bool
        BaseType::isPartial() const
        {
            return !isComplete();
        }

        inline std::shared_ptr<BaseType const>
        BaseType::merge( std::shared_ptr<BaseType const> other ) const
        {
            return mergeImpl( other );
        }

        inline std::string const&
        BaseType::getTypeName() const
        {
            return getTypeNameImpl();
        }

    }  // end of namespace Grammar
}

#endif
///@}


