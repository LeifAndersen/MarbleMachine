LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libjniinterface
LOCAL_CFLAGS    := -Wall
LOCAL_SRC_FILES := gl_code.cpp
LOCAL_LDLIBS    := -llog -lGLESv2

include $(BUILD_SHARED_LIBRARY)
