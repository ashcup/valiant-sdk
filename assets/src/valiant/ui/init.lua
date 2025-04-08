-- This Source Code Form is subject to the terms of the Mozilla Public
-- License, v. 2.0. If a copy of the MPL was not distributed with this
-- file, You can obtain one at https://mozilla.org/MPL/2.0/.

local tableutils = require "valiant.core.tableutils"

local ui = {}

ui = tableutils.merge(ui, require "valiant.ui.common")
ui = tableutils.merge(ui, require "valiant.ui.window")
ui = tableutils.merge(ui, require "valiant.ui.d2d")
ui = tableutils.merge(ui, require "valiant.ui.d3d")

return ui
