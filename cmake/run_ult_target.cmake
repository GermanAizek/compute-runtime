#
# Copyright (C) 2020-2022 Intel Corporation
#
# SPDX-License-Identifier: MIT
#

string(REPLACE "/" ";" unit_test_config ${unit_test_config})
list(GET unit_test_config 0 product)
list(GET unit_test_config 1 slices)
list(GET unit_test_config 2 subslices)
list(GET unit_test_config 3 eu_per_ss)
list(GET unit_test_config 4 revision_id)

add_custom_target(run_${product}_${revision_id}_unit_tests ALL DEPENDS unit_tests)
set_target_properties(run_${product}_${revision_id}_unit_tests PROPERTIES FOLDER "${PLATFORM_SPECIFIC_TEST_TARGETS_FOLDER}/${product}/${revision_id}")
if(NOT NEO_SKIP_SHARED_UNIT_TESTS)
  unset(GTEST_OUTPUT)
  if(DEFINED GTEST_OUTPUT_DIR)
    set(GTEST_OUTPUT "--gtest_output=json:${GTEST_OUTPUT_DIR}/shared_${product}_${revision_id}_unit_tests_results.json")
    message(STATUS "GTest output set to ${GTEST_OUTPUT}")
  endif()
  add_custom_command(
                     TARGET run_${product}_${revision_id}_unit_tests
                     POST_BUILD
                     COMMAND WORKING_DIRECTORY ${TargetDir}
                     COMMAND echo Running neo_shared_tests ${target} ${slices}x${subslices}x${eu_per_ss} in ${TargetDir}/${product}
                     COMMAND ${NEO_RUN_INTERCEPTOR_LIST} $<TARGET_FILE:neo_shared_tests> --product ${product} --slices ${slices} --subslices ${subslices} --eu_per_ss ${eu_per_ss} ${GTEST_EXCEPTION_OPTIONS} --gtest_repeat=${GTEST_REPEAT} ${GTEST_SHUFFLE} ${GTEST_OUTPUT} ${NEO_TESTS_LISTENER_OPTION} ${GTEST_FILTER_OPTION} --rev_id ${revision_id}
  )

endif()
if(NOT NEO_SKIP_OCL_UNIT_TESTS)
  unset(GTEST_OUTPUT)
  if(DEFINED GTEST_OUTPUT_DIR)
    set(GTEST_OUTPUT "--gtest_output=json:${GTEST_OUTPUT_DIR}/ocl_${product}_${revision_id}_unit_tests_results.json")
    message(STATUS "GTest output set to ${GTEST_OUTPUT}")
  endif()
  add_custom_command(
                     TARGET run_${product}_${revision_id}_unit_tests
                     POST_BUILD
                     COMMAND WORKING_DIRECTORY ${TargetDir}
                     COMMAND echo Running igdrcl_tests ${target} ${slices}x${subslices}x${eu_per_ss} in ${TargetDir}/${product}
                     COMMAND ${GTEST_ENV} ${NEO_RUN_INTERCEPTOR_LIST} $<TARGET_FILE:igdrcl_tests> --product ${product} --slices ${slices} --subslices ${subslices} --eu_per_ss ${eu_per_ss} ${GTEST_EXCEPTION_OPTIONS} --gtest_repeat=${GTEST_REPEAT} ${GTEST_SHUFFLE} ${GTEST_OUTPUT} ${NEO_TESTS_LISTENER_OPTION} ${GTEST_FILTER_OPTION} --rev_id ${revision_id}
  )

  if(WIN32 AND ${CMAKE_BUILD_TYPE} STREQUAL "Debug" AND "${IGDRCL_OPTION__BITS}" STREQUAL "64" AND APPVERIFIER_ALLOWED)
    unset(GTEST_OUTPUT)
    if(DEFINED GTEST_OUTPUT_DIR)
      set(GTEST_OUTPUT "--gtest_output=json:${GTEST_OUTPUT_DIR}/ocl_windows_${product}_${revision_id}_unit_tests_results.json")
      message(STATUS "GTest output set to ${GTEST_OUTPUT}")
    endif()
    add_custom_command(
                       TARGET run_${product}_${revision_id}_unit_tests
                       POST_BUILD
                       COMMAND WORKING_DIRECTORY ${TargetDir}
                       COMMAND echo Running igdrcl_tests with App Verifier
                       COMMAND ${NEO_SOURCE_DIR}/scripts/verify.bat $<TARGET_FILE:igdrcl_tests> --product ${product} --slices ${slices} --subslices ${subslices} --eu_per_ss ${eu_per_ss} ${GTEST_EXCEPTION_OPTIONS} ${GTEST_OUTPUT} ${NEO_TESTS_LISTENER_OPTION} ${GTEST_FILTER_OPTION} --rev_id ${revision_id}
                       COMMAND echo App Verifier returned: %errorLevel%
    )
  endif()
endif()

if(NOT NEO_SKIP_L0_UNIT_TESTS AND BUILD_WITH_L0)
  unset(GTEST_OUTPUT_CORE)
  if(DEFINED GTEST_OUTPUT_DIR)
    set(GTEST_OUTPUT_CORE "--gtest_output=json:${GTEST_OUTPUT_DIR}/ze_intel_gpu_core_${product}_${revision_id}_unit_tests_results.json")
    message(STATUS "GTest output core set to ${GTEST_OUTPUT_CORE}")
  endif()
  unset(GTEST_OUTPUT_TOOLS)
  if(DEFINED GTEST_OUTPUT_DIR)
    set(GTEST_OUTPUT_TOOLS "--gtest_output=json:${GTEST_OUTPUT_DIR}/ze_intel_gpu_tools_${product}_${revision_id}_unit_tests_results.json")
    message(STATUS "GTest output tools set to ${GTEST_OUTPUT_TOOLS}")
  endif()
  unset(GTEST_OUTPUT_EXP)
  if(DEFINED GTEST_OUTPUT_DIR)
    set(GTEST_OUTPUT_EXP "--gtest_output=json:${GTEST_OUTPUT_DIR}/ze_intel_gpu_exp_${product}_${revision_id}_unit_tests_results.json")
    message(STATUS "GTest output exp set to ${GTEST_OUTPUT_EXP}")
  endif()
  add_custom_command(
                     TARGET run_${product}_${revision_id}_unit_tests
                     POST_BUILD
                     COMMAND WORKING_DIRECTORY ${TargetDir}
                     COMMAND echo Running ze_intel_gpu_core_tests ${target} ${slices}x${subslices}x${eu_per_ss} in ${TargetDir}/${product}
                     COMMAND ${NEO_RUN_INTERCEPTOR_LIST} $<TARGET_FILE:ze_intel_gpu_core_tests> --product ${product} --slices ${slices} --subslices ${subslices} --eu_per_ss ${eu_per_ss} ${GTEST_EXCEPTION_OPTIONS} --gtest_repeat=${GTEST_REPEAT} ${GTEST_SHUFFLE} ${GTEST_OUTPUT_CORE} ${NEO_TESTS_LISTENER_OPTION} ${GTEST_FILTER_OPTION} --rev_id ${revision_id}
                     COMMAND echo Running ze_intel_gpu_tools_tests ${target} ${slices}x${subslices}x${eu_per_ss} in ${TargetDir}/${product}
                     COMMAND ${NEO_RUN_INTERCEPTOR_LIST} $<TARGET_FILE:ze_intel_gpu_tools_tests> --product ${product} --slices ${slices} --subslices ${subslices} --eu_per_ss ${eu_per_ss} ${GTEST_EXCEPTION_OPTIONS} --gtest_repeat=${GTEST_REPEAT} ${GTEST_SHUFFLE} ${GTEST_OUTPUT_TOOLS} ${NEO_TESTS_LISTENER_OPTION} ${GTEST_FILTER_OPTION} --rev_id ${revision_id}
                     COMMAND echo Running ze_intel_gpu_exp_tests ${target} ${slices}x${subslices}x${eu_per_ss} in ${TargetDir}/${product}
                     COMMAND ${NEO_RUN_INTERCEPTOR_LIST} $<TARGET_FILE:ze_intel_gpu_exp_tests> --product ${product} --slices ${slices} --subslices ${subslices} --eu_per_ss ${eu_per_ss} ${GTEST_EXCEPTION_OPTIONS} --gtest_repeat=${GTEST_REPEAT} ${GTEST_SHUFFLE} ${GTEST_OUTPUT_EXP} ${NEO_TESTS_LISTENER_OPTION} ${GTEST_FILTER_OPTION} --rev_id ${revision_id}
  )
endif()

add_dependencies(run_unit_tests run_${product}_${revision_id}_unit_tests)
