cmake_minimum_required(VERSION 3.0.0)

message("CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/ SRC_LIST)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/utility SRC_LIST)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/context SRC_LIST)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/device SRC_LIST)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/libBTC SRC_LIST)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/libBCH SRC_LIST)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/libETH SRC_LIST)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/token SRC_LIST)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/../deps SRC_LIST)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/../deps/bigint SRC_LIST)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/../deps/bitcoin SRC_LIST)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/../deps/bitcoinABC SRC_LIST)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/../deps/polarssl SRC_LIST)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../deps)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../deps/trezor-crypto/include)
if(IOS)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../deps/bleTransmit/ios)
elseif(ANDROID)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../deps/bleTransmit/android)
endif()
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../deps/bigint)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../deps/bitcoin)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../deps/bitcoinABC)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../deps/libbitcoin)


ADD_LIBRARY(JUB_SDK STATIC ${SRC_LIST})
#if(IOS)
ADD_DEFINITIONS(-DTARGET_OS_IPHONE)
#endif()

# test endian.h
find_path(ENDIAN_PATH endian.h)
find_path(SYS_ENDIAN_PATH sys/endian.h)

if(ENDIAN_PATH)
    message("ENDIAN_PATH = ${ENDIAN_PATH}")
    target_compile_definitions(JUB_SDK PRIVATE HAVE_ENDIAN_H=1)
elseif(SYS_ENDIAN_PATH)
    message("SYS_ENDIAN_PATH = ${SYS_ENDIAN_PATH}")
    target_compile_definitions(JUB_SDK PRIVATE HAVE_SYS_ENDIAN_H=1)
endif()

