#make sure to turn off debugging before shipping.
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libjniinterface
LOCAL_CFLAGS    := -Wall -g
LOCAL_LDFLAGS := -Wl,-Map,xxx.map
CORE_PREFIX := $(LOCAL_PATH)/../../core/
CORE_SOURCES := $(wildcard $(CORE_PREFIX)/*.cpp)
CORE_SOURCES += $(wildcard $(CORE_PREFIX)*/*.cpp)
CORE_SOURCES := $(CORE_SOURCES:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES := jniinterface.cpp os_calls.cpp $(CORE_SOURCES)
LOCAL_LDLIBS    := -llog -lGLESv2
LOCAL_C_INCLUDES := $(CORE_PREFIX) $(CORE_PREFIX)/entities $(CORE_PREFIX)/objLoader $(LOCAL_PATH)/nv $(LOCAL_PATH)/nv/nv_sound $(LOCAL_PATH)/nv/nv_thread $(LOCAL_PATH)/nv/nv_apk_file $(LOCAL_PATH)/nv/nv_file
LOCAL_STATIC_LIBRARIES := nvsound nvthread nvapkfile nvfile

include $(BUILD_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := nvthread
LOCAL_CFLAGS    := -Wall -g
LOCAL_LDFLAGS := -Wl,-Map,xxx.map
LOCAL_SRC_FILES := nv/nv_thread/nv_thread.c
LOCAL_C_INCLUDES := nv

include $(BUILD_STATIC_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := nvsound
LOCAL_CFLAGS    := -Wall -g
LOCAL_LDFLAGS := -Wl,-Map,xxx.map
LOCAL_SRC_FILES := nv/nv_sound/nv_sound.cpp
LOCAL_C_INCLUDES := nv
LOCAL_STATIC_LIBRARIES := nvthread

include $(BUILD_STATIC_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := nvapkfile
LOCAL_CFLAGS    := -Wall -g
LOCAL_LDFLAGS := -Wl,-Map,xxx.map
LOCAL_SRC_FILES := nv/nv_apk_file/nv_apk_file.c
LOCAL_C_INCLUDES := nv
LOCAL_STATIC_LIBRARIES := nvthread

include $(BUILD_STATIC_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE := nvfile
LOCAL_CFLAGS    := -Wall -g
LOCAL_LDFLAGS := -Wl,-Map,xxx.map
LOCAL_SRC_FILES := nv/nv_file/nv_file.c
LOCAL_C_INCLUDES := nv
LOCAL_STATIC_LIBRARIES := nvthread nvapkfile

include $(BUILD_STATIC_LIBRARY)
