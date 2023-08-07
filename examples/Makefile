tests:
	set -e; \
	for i in */Makefile; do \
		echo '==== Making:' $$(dirname $$i); \
		make -C $$(dirname $$i) -j; \
	done

# Trying to run all the examples probably doesn't make much sense.
# It is hard to interpret arbitrary example results. Examples may not work
# in the Linux environment. Examples often never finish (by design).
#
#
# For repeatable, consistent detection of regressions, make unit tests:
#
# 1. Put the unit test in extras/tests/...
# 2. Use <AUnit.h> to cleanly detect regressions automatically
#
runtests:
	set -e; \
	for i in */Makefile; do \
		echo '==== SKIPPING:' $$(dirname $$i);\
	done
	#for i in */Makefile; do \
	#	echo '==== Running:' $$(dirname $$i); \
	#	make -C $$(dirname $$i) run; \
	#done

clean:
	set -e; \
	for i in */Makefile; do \
		echo '==== Cleaning:' $$(dirname $$i); \
		make -C $$(dirname $$i) clean; \
	done

debug:
	set -e; \
	for i in */Makefile; do \
		echo '==== Debug build:' $$(dirname $$i); \
		make -C $$(dirname $$i) debug; \
	done
