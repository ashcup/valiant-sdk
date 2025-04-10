-- This Source Code Form is subject to the terms of the Mozilla Public
-- License, v. 2.0. If a copy of the MPL was not distributed with this
-- file, You can obtain one at https://mozilla.org/MPL/2.0/.

local tableutils = require "valiant.core.tableutils"
local common = require "valiant.ui.common"
local d2d = require "valiant.ui.d2d"
local d3d = require "valiant.ui.d3d"
local window = require "valiant.ui.Window"

local draw = {
    common = common,
    d2d = d2d,
    d3d = d3d
}

tableutils.merge(draw, common)
tableutils.merge(draw, d2d)
tableutils.merge(draw, d3d)
tableutils.merge(draw, window)

return draw
