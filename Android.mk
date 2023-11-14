LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := your_script
LOCAL_SRC_FILES := your_script.cpp
LOCAL_LDLIBS    := -llog
LOCAL_CPPFLAGS  := -std=c++11
LOCAL_CPP_FEATURES := rtti exceptions
LOCAL_STATIC_LIBRARIES := c++_static
include $(BUILD_EXECUTABLE)
