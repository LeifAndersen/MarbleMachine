LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libjniinterface
LOCAL_CFLAGS    := -Wall
LOCAL_SRC_FILES := jniinterface.cpp ../../core/main.cpp ../../core/game_state.cpp ../../core/physics.cpp ../../core/glview.cpp
LOCAL_LDLIBS    := -llog -lGLESv2

include $(BUILD_SHARED_LIBRARY)
