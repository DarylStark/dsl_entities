#include "dsl_entity.h"

namespace dsl
{
    namespace entities
    {
        EntityEvent EntityEvent::make_entity_event(const Entity &entity, const EntitySubscription &subscription, bool value_changed)
        {
            return EntityEvent({entity, subscription, value_changed});
        }
    };
};