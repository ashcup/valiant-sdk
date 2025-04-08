-- This Source Code Form is subject to the terms of the Mozilla Public
-- License, v. 2.0. If a copy of the MPL was not distributed with this
-- file, You can obtain one at https://mozilla.org/MPL/2.0/.

-- Classes

local Event = class {
    name = "event"
}

local EventSystem = class {
    events = {}
}

-- Functions

function Event:__init(name)
    if type(name) ~= "string" then vstdlib_application_abort("Missing required parameter.") end
    local properties = {
        listeners = {},
        name = name
    }
    local instance = setmetatable(properties, Event)
    return instance
end

function Event:listen(eventHandler)
    table.insert(self.listeners, eventHandler)
end

function EventSystem:__init()
    self.events = {}
end

function EventSystem.getInstance()
    return eventSystem
end

function EventSystem:register(event)
    self.events[event.name] = event
end

-- Create the default event system.

-- Create the default events.
local drawEvent = Event.create "draw"
local startEvent = Event.create "start"
local stopEvent = Event.create "stop"
local tickEvent = Event.create "tick"

-- Register the default events.
local eventSystem = EventSystem.create()
-- setmetatable(eventSystem, EventSystem)
eventSystem:register(drawEvent)
eventSystem:register(startEvent)
eventSystem:register(stopEvent)
eventSystem:register(tickEvent)

-- Module exports

return {
    Event = Event,
    EventSystem = EventSystem
}
