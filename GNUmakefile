
name := crystal
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = ../geant4.9.4.p01
endif


ROOTCFLAGS = `root-config --cflags`
ROOTLIBS = `root-config --nonew --libs` 
CPPFLAGS += $(ROOTCFLAGS) 
EXTRALIBS +=  $(ROOTLIBS) 


.PHONY: all
all: lib bin

include $(G4INSTALL)/config/architecture.gmk
include $(G4INSTALL)/config/binmake.gmk

visclean:
	rm -f g4*.prim g4*.eps g4*.wrl *~
	rm -f .DAWN_*


