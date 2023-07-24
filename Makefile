#
# Approximation library top-level Makefile
#
# Used by GitHub actions to build and test the library
#
# Also supports Visual Studio Code builds on Linux
# (includes builds for VS Code debugger support)
#
NAME := Approximation
VERSION := $(shell git describe --tags --always --dirty)

#.DEFAULT_GOAL := CoinFlipper.cpp

# FULL build and test from scratch
all: clean test

# Build tests
run:
	make -C extras/tests
	make -C examples

# Run tests
test: run
	make -C extras/tests runtests
	#make -C examples runtests

# Delete working/output files
clean:
	make -C extras/tests clean
	make -C examples clean

# Build tests compatible with debugger (gdb)
debug:
	echo Making DEBUG
	make -C extras/tests debug
	make -C examples debug

#
# VSCode "Debug" and "Release" configuration build support
#
# usage:  "make CONFIG=DEBUG" or "make CONFIG=RELEASE"
#

# "release" alias
release: run
	echo Making RELEASE

# collect configuration from command line ("RELEASE" if not set)
CONFIG ?= RELEASE

ifeq ($(CONFIG), DEBUG)

configuredBuild: debug

else

configuredBuild: release

endif

#$(NAME)-$(VERSION).zip:
#	git archive HEAD --prefix=$(@:.zip=)/ --format=zip -o $@

#tag:
#	git tag $(VERSION)

