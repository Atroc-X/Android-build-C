LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := your_script
LOCAL_SRC_FILES := your_script.cpp
LOCAL_LDLIBS    := -llog -lm
include $(BUILD_EXECUTABLE)
