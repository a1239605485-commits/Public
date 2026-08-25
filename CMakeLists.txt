cmake_minimum_required(VERSION 3.22.1)
project(HealthLock C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(HealthLock SHARED src/mod.c src/tef_api_imp.c)
target_include_directories(HealthLock PRIVATE include)

if(ANDROID)
  set(PLATFORM_NAME android)
  if(ANDROID_ABI STREQUAL "arm64-v8a")
    set(ARCH_NAME arm64)
  elseif(ANDROID_ABI STREQUAL "armeabi-v7a")
    set(ARCH_NAME arm)
  endif()
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(PLATFORM_NAME linux)
  set(ARCH_NAME x64)
endif()

set_target_properties(HealthLock PROPERTIES
  PREFIX "lib"
  OUTPUT_NAME "HealthLock.${PLATFORM_NAME}.${ARCH_NAME}"
  SUFFIX ".so"
)
