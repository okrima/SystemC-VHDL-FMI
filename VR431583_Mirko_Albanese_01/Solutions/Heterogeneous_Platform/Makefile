SYSTEMC_AMS=$$SCAMS_HOME
SYSTEMC=$$SYSTEMC_HOME

PLATFORM= $(shell uname -s)
ARCH=$(shell getconf LONG_BIT)

ifeq ($(PLATFORM),Darwin)
SYSC_LIBDIR := $(SYSTEMC)/lib-macosx
SCAMS_LIBDIR := $(SYSTEMC_AMS)/lib-macosx
endif
ifeq ($(PLATFORM),Linux)
SYSC_LIBDIR := $(SYSTEMC)/lib-linux
SCAMS_LIBDIR := $(SYSTEMC_AMS)/lib-linux
endif

ifeq ($(ARCH),64)
SYSC_LIBDIR := $(SYSC_LIBDIR)64
SCAMS_LIBDIR := $(SCAMS_LIBDIR)64
endif

LIBS = $(SCAMS_LIBDIR)/libsystemc-ams.a \
	   $(SYSC_LIBDIR)/libsystemc.a \
	   -lpthread

INCDIR = -I./include/ -I. -I$(SYSTEMC)/include/ -I$(SYSTEMC_AMS)/include

CXX=g++
CFLAGS= -c
LD=g++

EXECUTABLE=./bin/main.x

all: $(EXECUTABLE)

clean:
	@echo Cleaning
	@rm -f obj/*.o *~
	@rm -f $(EXECUTABLE)

$(EXECUTABLE): obj/main.o obj/converter.o obj/controllore_TLM.o obj/xtea_RTL.o obj/valvola.o obj/serbatoio.o obj/transactor_RTL_AMS.o obj/transactor_AMS_RTL.o obj/transactor_RTL_TLM.o obj/transactor_TLM_RTL.o
	@ $(LD) -o $@ $(INCDIR) $^ $(LIBS)

obj/main.o: src/main.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<
	
obj/converter.o: src/converter.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/controllore_TLM.o: src/controllore_TLM.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/xtea_RTL.o: src/xtea_RTL.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/valvola.o: src/valvola.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<
	
obj/serbatoio.o: src/serbatoio.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/transactor_RTL_AMS.o: src/transactor_RTL_AMS.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/transactor_AMS_RTL.o: src/transactor_AMS_RTL.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

obj/transactor_RTL_TLM.o: src/transactor_RTL_TLM.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<
	
obj/transactor_TLM_RTL.o: src/transactor_TLM_RTL.cc
	@echo Building $@
	@ $(CXX) $(CFLAGS) -o $@ $(INCDIR) $<

.PHONY: all clean
