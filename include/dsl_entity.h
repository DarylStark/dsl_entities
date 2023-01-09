#ifndef __DSL_ENTITY_H__
#define __DSL_ENTITY_H__

#include <functional>
#include <list>
#include <string>
#include <variant>
#include <thread>
#include <memory>

#include "dsl_entities_exceptions.h"
#include <dsl_types_event.h>

namespace dsl
{
    namespace entities
    {
        class Entity;
        struct EntitySubscription;
        struct EntityEvent;

        // Typedef for the callback method
        typedef std::function<void(const EntityEvent &)> entity_callback_type;

        // Class to define a Entity Subscription
        struct EntitySubscription : public dsl::types::Subscription<entity_callback_type>
        {
            // Factory methods for this class
            static EntitySubscription make_entity_subscription(entity_callback_type callback, std::string identifier, bool run_always = false);
            static EntitySubscription make_threaded_entity_subscription(entity_callback_type callback, std::string identifier, bool run_always = false);

            // Operators
            bool operator==(const EntitySubscription &other) const;

            // EntitySubscription-only variables
            bool run_always = false;
        };

        // The Entity class defines entities in a Observer-pattern
        class Entity
        {

        public:
            // Types
            typedef std::variant<
                bool,
                int,
                unsigned int,
                float>
                EntityType;

            // Enum with the types; should match the order of the `variant` in the line
            // above this.
            enum EntityTypeName
            {
                Bool,
                Integer,
                UnsignedInteger,
                Float
            };

        private:
            std::list<EntitySubscription> __subscriptions;

        protected:
            EntityType _value;

        public:
            // Factory methods for this class
            static Entity make_entity(EntityType value);

            // Constructors
            explicit Entity(EntityType value);
            Entity();

            // Copy constructor can be default
            Entity(const Entity &) = default;

            // Methods to subscribe and unsubscribe
            void subscribe(EntitySubscription subscription);
            void unsubscribe(const std::string &identifier);
            void unsubscribe_all();

            // Methods to publish to the subscribers
            void publish(bool value_changed) const;

            // Method to set the value
            Entity &set(EntityType value);

            // Methods to get the value and the valuetype
            EntityType get() const;
            EntityTypeName get_type() const;

            // Overloading operators
            Entity &operator=(EntityType value);
            Entity operator++(int);
            Entity operator++();
            Entity operator--(int);
            Entity operator--();
            bool operator!() const;

            // Operator for type casting
            operator bool() const;
            operator int() const;
            operator unsigned int() const;
            operator float() const;
        };

        // The EntityEvent class can be used by callbacks to identify the event that
        // happend.
        struct EntityEvent : public dsl::types::Event<Entity, EntitySubscription>
        {
            // Factory methods
            static EntityEvent create_entity_event(const Entity &entity, const EntitySubscription &subscription, bool value_changed);

            // EntityEvent-only variables
            bool changed;
        };
    };
};

#endif // __DSL_ENTITY_H__