#----------------------------------------------------------------------------------
# File:            libs\jni\Android.mk
# Samples Version: Android NVIDIA samples 2
# Email:           tegradev@nvidia.com
# Forum:           http://developer.nvidia.com/tegra/forums/tegra-forums/android-development
#
# Copyright 2009-2010 NVIDIA® Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
#----------------------------------------------------------------------------------

include $(CLEAR_VARS)

LOCAL_PATH := nv_thread
LOCAL_MODULE := nvthread
LOCAL_SRC_FILES := nv_thread.c
LOCAL_C_INCLUDES := ../../jni/nv

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_PATH := nv_sound
LOCAL_MODULE := nvsound
LOCAL_SRC_FILES := nv_sound.cpp
LOCAL_C_INCLUDES := ../../jni/nv

include $(BUILD_STATIC_LIBRARY)

