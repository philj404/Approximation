# Makefile for unit test checks
#

# build tests
tests:
	set -e; \
	for i in *Test/Makefile; do \
		echo '==== Making:' $$(dirname $$i); \
		make -C $$(dirname $$i) -j; \
	done

# run all unit tests
runtests:
	set -e; \
	for i in *Test/Makefile; do \
		echo '==== Running:' $$(dirname $$i); \
		make -C $$(dirname $$i) run; \
	done

# remove generated output files
clean:
	set -e; \
	for i in *Test/Makefile; do \
		echo '==== Cleaning:' $$(dirname $$i); \
		make -C $$(dirname $$i) clean; \
	done

# build tests with debugger support
debug:
	set -e; \
	for i in *Test/Makefile; do \
		echo '==== Debug build:' $$(dirname $$i); \
		make -C $$(dirname $$i) debug; \
	done
