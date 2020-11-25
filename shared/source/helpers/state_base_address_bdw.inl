/*
 * Copyright (C) 2020 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "shared/source/helpers/state_base_address.h"

namespace NEO {

template <typename GfxFamily>
void StateBaseAddressHelper<GfxFamily>::appendStateBaseAddressParameters(
    STATE_BASE_ADDRESS *stateBaseAddress,
    const IndirectHeap *ssh,
    bool setGeneralStateBaseAddress,
    uint64_t indirectObjectHeapBaseAddress,
    GmmHelper *gmmHelper,
    bool isMultiOsContextCapable) {
    appendExtraCacheSettings(stateBaseAddress, gmmHelper);
}

} // namespace NEO
