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