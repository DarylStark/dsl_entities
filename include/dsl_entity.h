#ifndef __DSL_ENTITY_H__
#define __DSL_ENTITY_H__

#include <functional>
#include <list>
#include <string>
#include <variant>
#include <thread>
#include <memory>

#include "dsl_entities_exceptions.h"
#include <dsl_models_subscription.h>
#include <dsl_models_event.h>

namespace dsl
{
    namespace entities
    {
        class Entity;
        struct EntitySubscription;
        struct EntityEvent;

        // Typedef for the variant that we are going to use in the Entity
        typedef std::variant<
            bool,
            int,
            unsigned int,
            float>
            entity_value_type;

        // Typedef for the callback method
        typedef std::function<void(const EntityEvent &)> entity_callback_type;

        // Enum with the types; should match the order of the `variant` in the line
        // above this.
        enum entity_type_name
        {
            Bool,
            Integer,
            UnsignedInteger,
            Float
        };

        // Class to define a Entity Subscription
        struct EntitySubscription : public dsl::models::Subscription<entity_callback_type>
        {
            // Factory methods for this class
            static EntitySubscription create_entity_subscription(entity_callback_type callback, std::string identifier, bool run_always = false);
            static EntitySubscription create_threaded_entity_subscription(entity_callback_type callback, std::string identifier, bool run_always = false);

            // Operators
            bool operator==(const EntitySubscription &other) const;

            // EntitySubscription-only variables
            bool run_always = false;
        };

        // The Entity class defines entities in a Observer-pattern
        class Entity
        {
        private:
            std::list<EntitySubscription> __subscriptions;

        protected:
            entity_value_type _value;

        public:
            // Constructors
            explicit Entity(entity_value_type value);
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
            Entity &set(entity_value_type value);

            // Methods to get the value and the valuetype
            entity_value_type get() const;
            entity_type_name get_type() const;

            // Overloading operators
            Entity &operator=(entity_value_type value);
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
        struct EntityEvent : public dsl::models::Event<Entity, EntitySubscription>
        {
            // Factory methods
            static EntityEvent create_entity_event(const Entity &entity, const EntitySubscription &subscription, bool value_changed);

            // EntityEvent-only variables
            bool changed;
        };
    };
};

#endif // __DSL_ENTITY_H__