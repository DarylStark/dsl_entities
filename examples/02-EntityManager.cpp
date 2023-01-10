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
    auto &wifi_connected = get_entity("wifi_connected");

    // Wifi connected! Update the Entity
    wifi_connected = true;
    delay(1000);

    // Wifi disconnected! Update the Entity
    wifi_connected = false;
    delay(1000);
}