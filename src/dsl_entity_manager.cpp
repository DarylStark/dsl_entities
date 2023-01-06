#include "dsl_entity_manager.h"

namespace dsl
{
    namespace entities
    {
        // Global object to globablly manage NumericEntities
        std::unordered_map<std::string, Entity> entities;
    };
};