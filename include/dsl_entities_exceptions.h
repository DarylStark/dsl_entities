#ifndef __DSL_ENTITIES_EXCEPTIONS_H__
#define __DSL_ENTITIES_EXCEPTIONS_H__

#include <dsl_exceptions.h>
#include <exception>
#include <string>

namespace dsl
{
    namespace entities
    {
        namespace exceptions
        {
            // Base exception for DSL Entities
            class EntityException : public dsl::exceptions::DSLException
            {
            public:
                EntityException(const std::string &message);
            };

            // Exception for type errors
            class EntityIncompatibleType : public EntityException
            {
            public:
                EntityIncompatibleType(const std::string &message);
            };
        };
    };
};

#endif /* __ENTITIES_EXCEPTIONS_H__ */