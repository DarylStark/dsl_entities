#include "dsl_entities_exceptions.h"

namespace dsl
{
    namespace entities
    {
        namespace exceptions
        {
            EntityException::EntityException(const std::string &message)
                : dsl::exceptions::DSLException(message)
            {
            }

            EntityIncompatibleType::EntityIncompatibleType(const std::string &message)
                : EntityException(message)
            {
            }
        };
    };
};