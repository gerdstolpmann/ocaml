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
	$(OCAMLOPT) $(incl) $(flags) -o server unix.cmxa nums.cmxa bigarray.cmxa str.cmxa threads.cmxa testing.cmx $(cmxa) server.ml main.ml


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
	rm -f main.ml
