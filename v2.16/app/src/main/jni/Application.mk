APP_STL := c++_static
NDK_TOOLCHAIN_VERSION = 4.9
APP_CPPFLAGS := -frtti -DCC_ENABLE_CHIPMUNK_INTEGRATION=1 -DCOCOS2D_DEBUG=1
APP_CPPFLAGS += -Wno-error=format-security
APP_CPPFLAGS += -std=c++11
APP_ABI := armeabi armeabi-v7a arm64-v8a
APP_OPIM := debug