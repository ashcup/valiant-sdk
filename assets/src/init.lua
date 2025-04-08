-- This Source Code Form is subject to the terms of the Mozilla Public
-- License, v. 2.0. If a copy of the MPL was not distributed with this
-- file, You can obtain one at https://mozilla.org/MPL/2.0/.

local application   = require "valiant.core.application"
local console       = require "valiant.core.console"

-- Log a message.
console.Log("Hello, Valiant!")

application.SetTargetFPS(60)

-- Start the application.
-- Tell the application's window to use vsync and work on high DPI displays.
application.Start(FLAG_WINDOW_HIGHDPI) -- TODO: BitOR with FLAG_VSYNC_HINT

-- Exit the application.
application.Exit(0)
