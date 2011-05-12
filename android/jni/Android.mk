LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libjniinterface
LOCAL_CFLAGS    := -Wall
LOCAL_SRC_FILES := jniinterface.cpp os_calls.cpp ../../core/main.cpp ../../core/game_state.cpp ../../core/physics.cpp ../../core/glview.cpp ../../core/entity.cpp
LOCAL_LDLIBS    := -llog -lGLESv2
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../core/ $(LOCAL_PATH)/nv $(LOCAL_PATH)/nv/nv_sound $(LOCAL_PATH)/nv/nv_thread
LOCAL_STATIC_LIBRARIES := nvsound nvthread

include $(BUILD_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := nvthread
LOCAL_SRC_FILES := nv/nv_thread/nv_thread.c
LOCAL_C_INCLUDES := nv

include $(BUILD_STATIC_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := nvsound
LOCAL_SRC_FILES := nv/nv_sound/nv_sound.cpp
LOCAL_C_INCLUDES := nv
LOCAL_STATIC_LIBRARIES := nvthread

include $(BUILD_STATIC_LIBRARY)

