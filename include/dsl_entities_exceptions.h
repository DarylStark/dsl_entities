#ifndef __DSL_ENTITIES_EXCEPTIONS_H__
#define __DSL_ENTITIES_EXCEPTIONS_H__

#include <exception>
#include <string>

namespace dsl
{
    namespace entities
    {
        namespace exceptions
        {
            // Base exception for DSL Entities
            class EntityException : public std::exception
            {
            };

            // Exception for type errors
            // TODO: Global DSL exception class
            // TODO: Place methods in Source File
            class EntityIncompatibleType : public EntityException
            {
            private:
                const std::string __message;

            public:
                EntityIncompatibleType(const std::string &message);
                const char *what() const noexcept override;
            };
        };
    };
};

#endif /* __ENTITIES_EXCEPTIONS_H__ */