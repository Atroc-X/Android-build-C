LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := your_script
LOCAL_SRC_FILES := your_script.cpp
LOCAL_LDLIBS    := -llog
LOCAL_CPPFLAGS  := -std=c++11 -frtti -fexceptions
LOCAL_C_INCLUDES := $(NDK_ROOT)/sources/cxx-stl/llvm-libc++/include
include $(BUILD_EXECUTABLE)
