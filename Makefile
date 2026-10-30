TARGET = iphone:clang:latest:14.0
ARCHS = arm64 arm64e

include $(THEOS)/makefiles/common.mk

TOOL_NAME = oslog
oslog_FILES = main.mm
oslog_CFLAGS = -fobjc-arc
oslog_CODESIGN_FLAGS = -S

include $(THEOS_MAKE_PATH)/tool.mk
