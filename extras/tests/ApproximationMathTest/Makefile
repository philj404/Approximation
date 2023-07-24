# See https://github.com/bxparks/EpoxyDuino for documentation about this
# Makefile to compile and run Arduino programs natively on Linux or MacOS.
#
APP_NAME := ApproximationMathTest
ARDUINO_LIBS := AUnit Approximation
# add compiler options with EXTRA_CXXFLAGS and EXTRA_CFLAGS
EXTRA_CXXFLAGS += -Werror
EXTRA_CFLAGS += -Werror

include ../../../../EpoxyDuino/EpoxyDuino.mk

# Visual Studio Code debug
# Additional hints for Visual Studio Code debug
# for "make debug"
#
debug: EXTRA_CXXFLAGS += -DDEBUG -g
debug: EXTRA_CFLAGS += -DDEBUG -g
debug: all
