#include "dsl_entities_exceptions.h"

namespace dsl
{
    namespace entities
    {
        namespace exceptions
        {
            EntityIncompatibleType::EntityIncompatibleType(const std::string &message)
                : __message(message)
            {
            }

            const char *EntityIncompatibleType::what() const noexcept
            {
                return __message.c_str();
            }
        };
    };
};