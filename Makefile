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
#all: run test

# example for typical makefile usage
#CoinFlipper.cpp: 
#    gcc -o ./target/CoinFlipper.out ./src/main/CoinFlipper.cpp

run:
	make -C extras/tests

test: run
	make -C extras/tests runtests

clean:
	make -C extras/tests clean

debug:
	make -C extras/tests debug


#$(NAME)-$(VERSION).zip:
#	git archive HEAD --prefix=$(@:.zip=)/ --format=zip -o $@

#tag:
#	git tag $(VERSION)

