BASEDIR=..
include $(BASEDIR)/makefiles/Makefile.common

modules := $(shell cat $(BASEDIR)/modules | while read line; do basename "$$line"; done)
cmxa := $(modules:=.cmxa)

incl := $(shell while read line; do printf "%s" "-I $(BASEDIR)/"; dirname $$line; printf "%s" "-cclib -L$(BASEDIR)/"; dirname $$line; done < $(BASEDIR)/modules | sort | uniq)

flags := -I $(OTOPDIR)/otherlibs/$(UNIXLIBVAR)unix \
         -I $(OTOPDIR)/otherlibs/num \
         -I $(OTOPDIR)/otherlibs/bigarray \
         -I $(OTOPDIR)/otherlibs/str \
         -I $(OTOPDIR)/otherlibs/systhreads \
	 -thread \
	 -I $(BASEDIR)/lib

.PHONY: cross-compile
cross-compile: server.ml main.ml
	$(OCAMLOPT) $(incl) $(flags) -o testserver unix.cmxa nums.cmxa bigarray.cmxa str.cmxa threads.cmxa testing.cmx $(cmxa) server.ml main.ml
	$(OCAMLOPT) $(incl) $(flags) -output-obj -o testserver.o unix.cmxa nums.cmxa bigarray.cmxa str.cmxa threads.cmxa testing.cmx $(cmxa) server.ml main.ml
	$(OCAMLOPT) -c link.c
	rm -f libtestserver.a
	mkdir -p tmp_asmrun
	cp $(OTOPDIR)/asmrun/libasmrun.a .
	cp $(OTOPDIR)/otherlibs/num/libnums.a .
	cp $(OTOPDIR)/otherlibs/str/libcamlstr.a .
	cp $(OTOPDIR)/otherlibs/bigarray/libbigarray.a .
	cp $(OTOPDIR)/otherlibs/unix/libunix.a .
	cp $(OTOPDIR)/otherlibs/systhreads/libthreadsnat.a .
	cd tmp_asmrun; \
	for lib in libnums.a libcamlstr.a libunix.a libbigarray.a libthreadsnat.a libasmrun.a; do \
	    ar x ../$$lib; \
	        for mem in $$(ar t ../$$lib | grep -v '__.*'); do \
	             ar qc ../libtestserver.a $$mem; \
	        done; \
        done
	ar qc libtestserver.a testserver.o link.o
	ar qc libtestserver.a ../tests/basic-manyargs/manyargsprim.o
	ar qc libtestserver.a ../tests/lib-marshal/intextaux.o
	ar qc libtestserver.a ../tests/gc-roots/globrootsprim.o
	ranlib libtestserver.a
	rm -rf tmp_asmrun libasmrun.a libnums.a libcamlstr.a libbigarray.a libunix.a libthreadsnat.a


main.ml: $(BASEDIR)/modules
	rm -f main.ml
	while read line; do \
	  base=`basename $$line` ; \
	  ubase="Cross_$${base#cross_*}"; \
	  echo "include Server.Register($$ubase)" >>main.ml; \
	done < $(BASEDIR)/modules
	echo "let () = Server.run()" >>main.ml

.PHONY: clean
clean: defaultclean
	rm -f main.ml testserver

