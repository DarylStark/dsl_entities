#ifndef __DSL_ENTITY_MANAGER_H__
#define __DSL_ENTITY_MANAGER_H__

#include <unordered_map>
#include "dsl_entity.h"

namespace dsl
{
    namespace entities
    {
        // Export a global object for entities
        extern std::unordered_map<std::string, Entity> gem_n;
    }
};

#endif /* __ENTITY_MANAGER_H__ */