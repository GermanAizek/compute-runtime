/*
 * Copyright (C) 2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "opencl/test/unit_test/fixtures/platform_fixture.h"
#include "test.h"

using namespace NEO;

struct XeHpcCorePlatformCaps : public PlatformFixture, public ::testing::Test {
    void SetUp() override {
        PlatformFixture::SetUp();
    }

    void TearDown() override {
        PlatformFixture::TearDown();
    }
};

PVCTEST_F(XeHpcCorePlatformCaps, givenPvcSkusThenItSupportFP64) {
    const auto &caps = pPlatform->getPlatformInfo();

    EXPECT_NE(std::string::npos, caps.extensions.find(std::string("cl_khr_fp64")));
}