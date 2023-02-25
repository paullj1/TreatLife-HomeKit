SUBDIRS := $(wildcard DS*) PP21KQ 

release:
	mkdir release
	for dir in $(SUBDIRS); do \
		cd $$dir; \
		$(MAKE); \
		cd ..; \
	done
	mv */*.bin release/
	gzip -k release/*.bin

debug:
	mkdir debug
	for dir in $(SUBDIRS); do \
		cd $$dir; \
		CFLAG='-D_DEBUG_TUYA' $(MAKE); \
		cd ..; \
	done
	mv */*.bin debug/
	gzip -k debug/*.bin

clean:
	for dir in $(SUBDIRS); do \
		cd $$dir; \
		$(MAKE) clean; \
		cd ..; \
	done
	rm -rf release debug

hashes:
	cd release; sha1sum *
	cd debug; sha1sum *
