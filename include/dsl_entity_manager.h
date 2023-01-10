#ifndef __DSL_ENTITY_MANAGER_H__
#define __DSL_ENTITY_MANAGER_H__

#include <unordered_map>
#include <utility>
#include "dsl_entity.h"

namespace dsl
{
    namespace entities
    {
        typedef std::pair<bool, Entity &> register_return_type;

        // Export a global object for entities
        extern std::unordered_map<std::string, Entity> gem;

        // Functions for the global entity manager
        register_return_type register_entity(std::string name, Entity entity);
        Entity &get_entity(std::string name, bool reg = true);
        bool remove_entity(std::string name);
    }
};

#endif /* __ENTITY_MANAGER_H__ */