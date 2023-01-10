#include "dsl_entity_manager.h"

namespace dsl
{
    namespace entities
    {
        // Global object to globablly manage NumericEntities
        std::unordered_map<std::string, Entity> gem;

        // Function to register a Entity to the global entity manager
        register_return_type register_entity(std::string name, Entity entity)
        {
            const auto [it, success] = gem.insert({name, entity});
            return {success, get_entity(name)};
        }

        Entity &get_entity(std::string name, bool reg /* = true */)
        {
            if (reg)
                return gem[name];
            return gem.at(name);
        }

        // Function to remove a Entity from the global entity manager
        bool remove_entity(std::string name)
        {
            return gem.erase(name) > 0;
        }
    };
};