#include "dsl_entity.h"

namespace dsl
{
    namespace entities
    {
        EntityEvent EntityEvent::create_entity_event(const Entity &entity, const EntitySubscription &subscription, bool value_changed)
        {
            return EntityEvent({entity, subscription, value_changed});
        }
    };
};