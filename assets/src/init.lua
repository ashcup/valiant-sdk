local application   = require "valiant.core.application"
local console       = require "valiant.core.console"

-- Log a message.
console.Log("Hello, Valiant!")

application.SetTargetFPS(60)

-- Start the application.
application.Start(FLAG_WINDOW_HIGHDPI) -- TODO: BitOR with FLAG_VSYNC_HINT

-- Exit the application.
application.Exit(0)
