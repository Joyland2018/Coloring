LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                                      ../../Classes/AppDelegate.cpp \
                                      ../../Classes/LogoScene.cpp \
                                      ../../Classes/GameManager.cpp \
                                      ../../Classes/HelloWorldScene.cpp \
                                      ../../Classes/BuyPage.cpp \
                                      ../../Classes/DinoColor/SelectAnimalScene.cpp \
                                      ../../Classes/DinoColor/ColorManager.cpp \
                                      ../../Classes/DinoColor/ColorCanvasView.cpp \
                                      ../../Classes/DinoColor/ChooseColorLayer.cpp \
                                      ../../Classes/DinoColor/SelectBrushLayer.cpp \
                                      ../../Classes/DinoColor/ColorSprite/ColorSprite.cpp \


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
                    $(LOCAL_PATH)/../../Classes/DinoColor \


LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

APP_ALLOW_MISSING_DEPS :=true
LOCAL_ALLOW_UNDEFINED_SYMBOLS := true

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path,$(LOCAL_PATH))

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
