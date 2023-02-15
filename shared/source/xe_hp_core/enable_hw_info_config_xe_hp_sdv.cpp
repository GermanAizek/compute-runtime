/*
 * Copyright (C) 2021-2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "shared/source/os_interface/hw_info_config.h"
#include "shared/source/os_interface/product_helper_hw.h"
#include "shared/source/xe_hp_core/hw_cmds.h"

namespace NEO {

static EnableProductProductHelper<IGFX_XE_HP_SDV> enableXEHP;

} // namespace NEO
