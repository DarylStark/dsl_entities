# DSL: Entities

This repository contains the code for the DSL Entities module. It has the following dependencies:

-   `dsl`; can be found on [DarylStark/dsl](https://github.com/DarylStark/dsl)

The Entities module is contained in the `dsl::entities` namespace and contains two subparts:

-   A `Entity` class in the `dsl_entity.h` header file to create `Entity` objects
-   A `gem` global object, defined in the `dsl_entity_manager.h` header file that can be used to manage global entities

## Entities

Entities are observer style objects. You can subscribe methods to the objects to get updates when they are changed. They are used by DSL to make variables more dynamic. For example, you can use a `Entity` object to keep track of the connection state for WiFi. If the state is set to `false`, you can make sure specific methods are called. The methods that you register for a `Entity` are either normal methods, ran in the normal application loop, or threaded methods, which get run in their own thread.

To create a `Entity` object, you initiate a object for the `Entity`. To make it easy, you can use the 

```c++
#include <Arduino.h>
#include "dsl_entity.h"

using namespace dsl::entities;

// Create the Entity object
Entity wifi_connected = Entity::make_entity(false);

// The callback for the object
void wifi_connection_change(const EntityEvent &e)
{
    if (static_cast<bool>(e.object))
    {
        Serial.println("Wifi is connected!");
        return;
    }
    Serial.println("Wifi is disconnected!");
    // Code to reconnect
}

void setup()
{
    Serial.begin(115200);

    // Subscribe a method to the `wifi_connected` object. This method gets
    // called anytime the `wifi_connected` Entity gets changed.
    wifi_connected.subscribe(
        EntitySubscription::make_entity_subscription(
            wifi_connection_change, "connection_change"));
}

void loop()
{
    // Wifi connected! Update the Entity
    wifi_connected = true;
    delay(1000);

    // Wifi disconnected! Update the Entity
    wifi_connected = false;
    delay(1000);
}
```

## Entity manager

You can also use the `gem` (Global Entity Manager) object to register entities that are usuable in every file in your application. This way, you can reuse created entities:

```c++
#include <Arduino.h>
#include <string>
#include <functional>
#include "dsl_entity_manager.h"

using namespace dsl::entities;

// The callback for the object
void wifi_connection_change(const EntityEvent &e)
{
    if (static_cast<bool>(e.object))
    {
        Serial.println("Wifi is connected!");
        return;
    }
    Serial.println("Wifi is disconnected!");
    // Code to reconnect
}

void setup()
{
    Serial.begin(115200);

    // Register a new entity
    auto x = register_entity(
        "wifi_connected",
        Entity::make_entity(false));
    
    // Get the Entity from the return value of the `register_entity` function
    auto &wifi_connected = x.second;

    // Subscribe a method to the `wifi_connected` object. This method gets
    // called anytime the `wifi_connected` Entity gets changed.
    wifi_connected.subscribe(
        EntitySubscription::make_entity_subscription(
            wifi_connection_change, "connecttion_change"));
}

void loop()
{
    // Get the entity
    auto& wifi_connected = get_entity("wifi_connected");

    // Wifi connected! Update the Entity
    wifi_connected = true;
    delay(1000);

    // Wifi disconnected! Update the Entity
    wifi_connected = false;
    delay(1000);
}
```

## When to use this

The `Entity` class and the global `gem` Entity Manager can be used for a whole lot of different features. One of the best features is to combine it with, for instance, sensor values. You can for instance create a binary sensor and connect a `Entity` in the `gem` that gets updated when the binary sensor gets `HIGH`. The application can connect to this `Entity` by subscribing to it.