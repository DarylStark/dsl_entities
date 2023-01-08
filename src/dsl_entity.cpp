#include "dsl_entity.h"

namespace dsl
{
    namespace entities
    {
        Entity::Entity(Entity::EntityType value) : _value(value) {}
        Entity::Entity() {}

        void Entity::subscribe(EntitySubscription subscription)
        {
            __subscriptions.push_back(subscription);
        }

        void Entity::unsubscribe(const std::string &identifier)
        {
            for (const auto &sub : __subscriptions)
                if (sub.identifier == identifier)
                    __subscriptions.remove(sub);
        }

        void Entity::unsubscribe_all()
        {
            __subscriptions.clear();
        }

        void Entity::publish(bool value_changed) const
        {
            for (const auto &sub : __subscriptions)
            {
                if ((sub.run_always && !value_changed) || (value_changed))
                {
                    EntityEvent e = EntityEvent::create_entity_event(
                        *this,
                        sub,
                        value_changed);

                    if (sub.run_as_thread)
                    {
                        // Start the function in it's own thread
                        std::thread thread(sub.callback, e);
                        thread.detach();
                    }
                    else
                    {
                        // Start the function in the current thread
                        sub.callback(e);
                    }
                }
            }
        }

        Entity &Entity::set(Entity::EntityType value)
        {
            bool changed = _value != value;
            _value = value;
            publish(changed);
            return *this;
        }

        // Methods to get the value and the valuetype
        Entity::EntityType Entity::get() const
        {
            return _value;
        }

        Entity::EntityTypeName Entity::get_type() const
        {
            return Entity::EntityTypeName(_value.index());
        }

        Entity &Entity::operator=(Entity::EntityType value)
        {
            return set(value);
        }

        Entity Entity::operator++(int)
        {
            Entity rv = Entity(_value);
            this->operator++();
            return rv;
        }

        Entity Entity::operator++()
        {
            switch (get_type())
            {
            case Integer:
                return *this = std::get<int>(_value) + 1;
            case UnsignedInteger:
                return *this = std::get<unsigned int>(_value) + 1;
            case Float:
                return *this = std::get<float>(_value) + 1;
            }

            throw dsl::entities::exceptions::EntityIncompatibleType("Operator `++` not possible for this Entity");
        }

        Entity Entity::operator--(int)
        {
            Entity rv = Entity(_value);
            this->operator--();
            return rv;
        }

        Entity Entity::operator--()
        {
            switch (get_type())
            {
            case Integer:
                return *this = std::get<int>(_value) - 1;
            case UnsignedInteger:
                return *this = std::get<unsigned int>(_value) - 1;
            case Float:
                return *this = std::get<float>(_value) - 1;
            }

            throw dsl::entities::exceptions::EntityIncompatibleType("Operator `--` not possible for this Entity");
        }

        bool Entity::operator!() const
        {
            if (get_type() == Bool)
            {
                return !std::get<bool>(_value);
            }
            throw dsl::entities::exceptions::EntityIncompatibleType("Cannot negate this Entity type");
        }

        Entity::operator bool() const
        {
            if (get_type() == Bool)
            {
                return std::get<bool>(_value);
            }
            throw dsl::entities::exceptions::EntityIncompatibleType("This Entity is not a bool");
        }

        Entity::operator int() const
        {
            if (get_type() == Integer)
            {
                return std::get<int>(_value);
            }
            throw dsl::entities::exceptions::EntityIncompatibleType("This Entity is not a int");
        }

        Entity::operator unsigned int() const
        {
            if (get_type() == UnsignedInteger)
            {
                return std::get<unsigned int>(_value);
            }
            throw dsl::entities::exceptions::EntityIncompatibleType("This Entity is not a unsigned int");
        }

        Entity::operator float() const
        {
            if (get_type() == Float)
            {
                return std::get<float>(_value);
            }
            throw dsl::entities::exceptions::EntityIncompatibleType("This Entity is not a float");
        }
    };
};
