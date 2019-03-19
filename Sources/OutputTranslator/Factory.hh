/**
 * @file OutputTranslator/Factory.hh
 * @author Massimiliano Pagani
 *
 * @date 2016-10-22 16:12:18
 */

#if !defined( OUTPUTTRANSLATOR_FACTORY_HH )
#define OUTPUTTRANSLATOR_FACTORY_HH

#include "OutputTranslator/Base.hh"

namespace OutputTranslator
{
    class Factory
    {
        public:
            Factory() = delete;
            ~Factory() = delete;

            enum LanguageType
            {
                JAVA,
                C_PLUS_PLUS,
                SCALA,
                TYDAL
            };

            static Base& getTranslatorFor( LanguageType type );

        private:
    };
}

#endif /* OUTPUTTRANSLATOR_FACTORY_HH */

