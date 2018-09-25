/*
 * Copyright (C) 2018 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "runtime/memory_manager/os_agnostic_memory_manager.h"

namespace OCLRT {
GraphicsAllocation *OsAgnosticMemoryManager::allocateGraphicsMemoryInDevicePool(const AllocationData &allocationData, AllocationStatus &status) {
    return MemoryManager::allocateGraphicsMemoryInDevicePool(allocationData, status);
}

void MemoryAllocation::overrideMemoryPool(MemoryPool::Type pool) {
    this->memoryPool = pool;
}
} // namespace OCLRT
