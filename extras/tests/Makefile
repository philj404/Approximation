tests:
	set -e; \
	for i in *Test/Makefile; do \
		echo '==== Making:' $$(dirname $$i); \
		make -C $$(dirname $$i) -j; \
	done

runtests:
	set -e; \
	for i in *Test/Makefile; do \
		echo '==== Running:' $$(dirname $$i); \
		make -C $$(dirname $$i) run; \
	done

clean:
	set -e; \
	for i in *Test/Makefile; do \
		echo '==== Cleaning:' $$(dirname $$i); \
		make -C $$(dirname $$i) clean; \
	done

debug:
	set -e; \
	for i in *Test/Makefile; do \
		echo '==== Debug build:' $$(dirname $$i); \
		make -C $$(dirname $$i) debug; \
	done
