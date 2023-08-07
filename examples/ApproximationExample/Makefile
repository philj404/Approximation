# See https://github.com/bxparks/EpoxyDuino for documentation about this
# Makefile to compile and run Arduino programs natively on Linux or MacOS.
#
APP_NAME := ApproximationExample
ARDUINO_LIBS := Approximation
EXTRA_CXXFLAGS += -Werror
EXTRA_CFLAGS += -Werror

include ../../../EpoxyDuino/EpoxyDuino.mk

# Additional hints for Visual Studio Code debug
# for "make debug"
debug: EXTRA_CXXFLAGS += -DDEBUG -g
debug: EXTRA_CFLAGS += -DDEBUG -g
debug: all

