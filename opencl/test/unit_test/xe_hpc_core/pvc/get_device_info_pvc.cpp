/*
 * Copyright (C) 2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "opencl/test/unit_test/fixtures/device_info_fixture.h"
#include "test.h"

using namespace NEO;

HWTEST_EXCLUDE_PRODUCT(GetDeviceInfoMemCapabilitiesTest, GivenValidParametersWhenGetDeviceInfoIsCalledForXE_HP_COREThenClSuccessIsReturned, IGFX_PVC);

PVCTEST_F(GetDeviceInfoMemCapabilitiesTest, GivenValidParametersWhenGetDeviceInfoIsCalledForPVCThenClSuccessIsReturned) {
    std::vector<TestParams> params = {
        {CL_DEVICE_HOST_MEM_CAPABILITIES_INTEL, CL_UNIFIED_SHARED_MEMORY_ACCESS_INTEL},
        {CL_DEVICE_DEVICE_MEM_CAPABILITIES_INTEL,
         (CL_UNIFIED_SHARED_MEMORY_ACCESS_INTEL | CL_UNIFIED_SHARED_MEMORY_ATOMIC_ACCESS_INTEL)},
        {CL_DEVICE_SINGLE_DEVICE_SHARED_MEM_CAPABILITIES_INTEL,
         (CL_UNIFIED_SHARED_MEMORY_ACCESS_INTEL | CL_UNIFIED_SHARED_MEMORY_ATOMIC_ACCESS_INTEL)},
        {CL_DEVICE_CROSS_DEVICE_SHARED_MEM_CAPABILITIES_INTEL,
         (CL_UNIFIED_SHARED_MEMORY_ACCESS_INTEL | CL_UNIFIED_SHARED_MEMORY_ATOMIC_ACCESS_INTEL)},
        {CL_DEVICE_SHARED_SYSTEM_MEM_CAPABILITIES_INTEL,
         0}};

    check(params);
}
