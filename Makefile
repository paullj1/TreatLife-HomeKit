SUBDIRS := $(wildcard DS*)

all: subdirs hashes
subdirs:
	for dir in $(SUBDIRS); do \
		cd $$dir; \
		$(MAKE); \
		cd ..; \
	done
	mv DS*/*.bin release/
	gzip -k release/*.bin

clean:
	for dir in $(SUBDIRS); do \
		cd $$dir; \
		$(MAKE) clean; \
		cd ..; \
	done
	rm release/*

hashes:
	cd release; sha1 *
