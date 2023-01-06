#include "dsl_entity.h"

namespace dsl
{
    namespace entities
    {
        EntitySubscription EntitySubscription::create_entity_subscription(entity_callback_type callback, std::string identifier, bool run_always /*= false */)
        {
            EntitySubscription obj;
            obj.callback = callback;
            obj.identifier = identifier;
            obj.run_always = run_always;
            obj.run_as_thread = false;
            return obj;
        }

        EntitySubscription EntitySubscription::create_threaded_entity_subscription(entity_callback_type callback, std::string identifier, bool run_always /*= false */)
        {
            EntitySubscription obj = EntitySubscription::create_entity_subscription(callback, identifier, run_always);
            obj.run_as_thread = true;
            return obj;
        }

        bool EntitySubscription::operator==(const EntitySubscription &other) const
        {
            return this->identifier == other.identifier;
        }
    };
};