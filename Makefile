ifeq ($(OS),Windows_NT)
LIBRARY_EXT=dll
JAVA_INCLUDE=...
PLATFORM=win32
else
LIBRARY_EXT=so
JAVA_INCLUDE=/usr/lib/jvm/java-8-openjdk/include
PLATFORM=linux
endif

SWIG=swig
CPP=g++
COPTS=-fpic -fno-strict-aliasing

LIBRARY=Dessin
PROCESSING_CORE_JAR=/usr/share/processing/core/library/core.jar

SWIGDIR=src/swig
BUILDDIR=$(SWIGDIR)/build
LIBDIR=$(SWIGDIR)/lib
GENDIR=$(SWIGDIR)/gen
OBJDIR=$(SWIGDIR)/objs
SRCDIR=$(SWIGDIR)/src

SIMULATEUR=src/simulateur

.PHONY: all
all: $(LIBDIR)/$(LIBRARY).$(LIBRARY_EXT) $(LIBDIR)/$(LIBRARY).jar
	mkdir -p $(SIMULATEUR)/code
	cp $^ $(SIMULATEUR)/code

.PHONY: clean
clean:
	rm -rf "$(GENDIR)" "$(OBJDIR)" "$(LIBDIR)" "$(BUILDDIR)" \
		$(SWIGDIR)/$(LIBRARY)_wrap.*

$(SWIGDIR)/$(LIBRARY)_wrap.cxx: $(SWIGDIR)/$(LIBRARY).i
	mkdir -p $(GENDIR)
	$(SWIG) -java -c++ -outdir src/swig/gen "$^"

$(OBJDIR)/declarations.o: $(SRCDIR)/declarations.*
	mkdir -p $(OBJDIR)
	$(CPP) -c $(COPTS) $(SRCDIR)/declarations.cpp \
		-o "$@"

$(OBJDIR)/$(LIBRARY)_wrap.o: $(SWIGDIR)/$(LIBRARY)_wrap.cxx
	mkdir -p $(OBJDIR)
	$(CPP) -c $(COPTS) "$^" \
	    -I$(JAVA_INCLUDE) \
    	-I$(JAVA_INCLUDE)/$(PLATFORM) \
		-o "$@"

$(LIBDIR)/$(LIBRARY).$(LIBRARY_EXT): $(OBJDIR)/$(LIBRARY)_wrap.o $(OBJDIR)/declarations.o
	mkdir -p $(LIBDIR)
	$(CPP) -shared $^ -o "$@"

$(BUILDDIR)/$(LIBRARY).class: $(SWIGDIR)/$(LIBRARY)_wrap.cxx
	mkdir -p $(BUILDDIR)
	javac -d $(BUILDDIR) \
    	-cp $(PROCESSING_CORE_JAR) \
		$(GENDIR)/*.java

$(LIBDIR)/$(LIBRARY).jar: $(BUILDDIR)/$(LIBRARY).class
	mkdir -p $(LIBDIR)
	jar cvfm \
		"$@" \
		"$(SRCDIR)/MANIFEST.MF" \
		-C $(BUILDDIR) \
		.
