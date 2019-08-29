/*
 * Copyright (C) 2017-2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include <core/helpers/aligned_memory.h>
#include <core/utilities/debug_settings_reader.h>
#include <runtime/compiler_interface/binary_cache.h>
#include <runtime/helpers/file_io.h>
#include <runtime/helpers/hash.h>
#include <runtime/helpers/hw_info.h>
#include <runtime/os_interface/ocl_reg_path.h>
#include <runtime/os_interface/os_inc_base.h>

#include "config.h"
#include "os_inc.h"

#include <cstring>
#include <iomanip>
#include <mutex>
#include <sstream>
#include <string>

namespace NEO {
std::mutex BinaryCache::cacheAccessMtx;
const std::string BinaryCache::getCachedFileName(const HardwareInfo &hwInfo, const ArrayRef<const char> input,
                                                 const ArrayRef<const char> options, const ArrayRef<const char> internalOptions) {
    Hash hash;

    hash.update("----", 4);
    hash.update(&*input.begin(), input.size());
    hash.update("----", 4);
    hash.update(&*options.begin(), options.size());
    hash.update("----", 4);
    hash.update(&*internalOptions.begin(), internalOptions.size());

    hash.update("----", 4);
    hash.update(reinterpret_cast<const char *>(&hwInfo.platform), sizeof(hwInfo.platform));
    hash.update("----", 4);
    hash.update(reinterpret_cast<const char *>(&hwInfo.featureTable), sizeof(hwInfo.featureTable));
    hash.update("----", 4);
    hash.update(reinterpret_cast<const char *>(&hwInfo.workaroundTable), sizeof(hwInfo.workaroundTable));

    auto res = hash.finish();
    std::stringstream stream;
    stream << std::setfill('0')
           << std::setw(sizeof(res) * 2)
           << std::hex
           << res;
    return stream.str();
}

BinaryCache::BinaryCache() {
    std::string keyName = oclRegPath;
    keyName += "cl_cache_dir";
    std::unique_ptr<SettingsReader> settingsReader(SettingsReader::createOsReader(false, keyName));
    clCacheLocation = settingsReader->getSetting(settingsReader->appSpecificLocation(keyName), static_cast<std::string>(CL_CACHE_LOCATION));
};

BinaryCache::~BinaryCache(){};

bool BinaryCache::cacheBinary(const std::string kernelFileHash, const char *pBinary, uint32_t binarySize) {
    if (pBinary == nullptr || binarySize == 0) {
        return false;
    }
    std::string filePath = clCacheLocation + PATH_SEPARATOR + kernelFileHash + ".cl_cache";
    std::lock_guard<std::mutex> lock(cacheAccessMtx);
    return 0 != writeDataToFile(filePath.c_str(), pBinary, binarySize);
}

std::unique_ptr<char[]> BinaryCache::loadCachedBinary(const std::string kernelFileHash, size_t &cachedBinarySize) {
    std::string filePath = clCacheLocation + PATH_SEPARATOR + kernelFileHash + ".cl_cache";

    std::lock_guard<std::mutex> lock(cacheAccessMtx);
    return loadDataFromFile(filePath.c_str(), cachedBinarySize);
}

} // namespace NEO
