/*
 * Copyright (C) 2021 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#pragma once
#include "shared/source/helpers/non_copyable_or_moveable.h"

#include "sysman/diagnostics/diagnostics_imp.h"
#include "sysman/diagnostics/os_diagnostics.h"
#include "sysman/linux/os_sysman_imp.h"

namespace L0 {

class LinuxDiagnosticsImp : public OsDiagnostics, NEO::NonCopyableOrMovableClass {
  public:
    void osGetDiagProperties(zes_diag_properties_t *pProperties) override;
    ze_result_t osGetDiagTests(uint32_t *pCount, zes_diag_test_t *pTests) override;
    ze_result_t osRunDiagTests(uint32_t start, uint32_t end, zes_diag_result_t *pResult) override;
    ze_result_t osRunDiagTestsinFW(zes_diag_result_t *pResult);
    ze_result_t osWarmReset();
    LinuxDiagnosticsImp() = default;
    LinuxDiagnosticsImp(OsSysman *pOsSysman, const std::string &diagTests, ze_bool_t onSubdevice, uint32_t subdeviceId);
    ~LinuxDiagnosticsImp() override = default;
    std::string osDiagType = "unknown";

  protected:
    FirmwareUtil *pFwInterface = nullptr;
    SysfsAccess *pSysfsAccess = nullptr;
    FsAccess *pFsAccess = nullptr;
    ProcfsAccess *pProcfsAccess = nullptr;
    decltype(&NEO::SysCalls::open) openFunction = NEO::SysCalls::open;
    decltype(&NEO::SysCalls::close) closeFunction = NEO::SysCalls::close;
    decltype(&NEO::SysCalls::pread) preadFunction = NEO::SysCalls::pread;
    decltype(&NEO::SysCalls::pwrite) pwriteFunction = NEO::SysCalls::pwrite;

  private:
    static const std::string quiescentGpuFile;
    bool isSubdevice = false;
    uint32_t subdeviceId = 0;
    static const std::string invalidateLmemFile;
    static const std::string deviceDir;
};

} // namespace L0
