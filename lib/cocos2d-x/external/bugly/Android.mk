LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := bugly_crashreport_cocos_static

LOCAL_MODULE_FILENAME := libcrashreport

LOCAL_CPP_EXTENSION := .mm .cpp .cc
LOCAL_CFLAGS += -x c++

LOCAL_SRC_FILES := CrashReport.mm 

LOCAL_C_INCLUDES := $(LOCAL_PATH)\
$(LOCAL_PATH)/../ \
$(LOCAL_PATH)/../../ \
$(LOCAL_PATH)/../../cocos2dx \
$(LOCAL_PATH)/../../cocos2dx/include \
$(LOCAL_PATH)/../../cocos2dx/platform/android \
$(LOCAL_PATH)/../../cocos2dx/kazmath/include \
$(LOCAL_PATH)/../../external

include $(BUILD_STATIC_LIBRARY)