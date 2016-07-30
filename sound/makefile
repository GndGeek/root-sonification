###########################################################################
#
# 4/May/07: Defined some static rules to simplify handling and output --LF
#
###########################################################################

# Root variables
ROOTCFLAGS   := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --libs) 
#-lRooFit -lHtml -lMinuit -lg2c  
#FORTRANLIBS  := -L../lib/ -lctvmft -L/cern/pro/lib -lkernlib
#FORTRANLIBS  := -L../lib/ -L/cern/pro/lib -lkernlib -lpacklib

# Programs
CXX          = g++
CXXFLAGS     = -g -Wall -fPIC -Wno-deprecated -ggdb
FORTRANFLAGS = -g -Wall -fPIC -ggdb
LDFLAGS      = -g 
SOFLAGS      = -shared 

# Local Includes
INCDIR      = -Iaux
   

# Direct to make the directories with the sources:
VPATH  = ./lib / ./bin ./tools ./aux 

# Assign or Add variables
CXXFLAGS    += $(ROOTCFLAGS)
CXXFLAGS    += $(INCDIR)
LIBS        += $(ROOTLIBS)

# Vertexing objects
#CXXOBJS      = $(CXXSRCS:.cc=.o)
GARBAGE      = $(CXXOBJS) *~ lib/*.so lib/*.o ./*/*.o


############################################################################
# Build main.c compiling only the first prereq: ($<) means main.c
############################################################################
sound : sound.o

############################################################################
# General rules. The first two need not be specified due to implicit rules, 
# but redefined for the "echo"
############################################################################

# Generate the dicionaries for a give .cc

DICTDEP = %.hh %_LinkDef.hh

%_Dict.cc: %.hh %_LinkDef.hh
	@echo Generating dictionary $@
	@rootcint -f $@ -c $(INCDIR) $^ #testt_LinkDef.hh

%_Dict.o: %_Dict.cc %_Dict.h 
	@echo "compiling $<"
	@$(CXX) $(CXXFLAGS) -c $< 

%.o : %.cc %.h 
	@echo "compiling $<"
	@$(CXX) $(CXXFLAGS) -c $< 

%.o : %.cc 
	@echo "compiling $<"
	@$(CXX) $(CXXFLAGS) -c $< 

%.o : %.F 
	@echo "compiling $<"
	@$(CXX) $(FORTRANFLAGS) -c $< 

%.o : %.f 
	@echo "compiling $<"
	@$(CXX) $(FORTRANFLAGS) -c $< 

%    : %.o
	@echo "compiling and linking $@"
	@$(CXX) $(LDFLAGS) $^ \
	        $(FORTRANLIBS) $(ROOTLIBS)  -o $@
	@if [ `ls | grep "\.so"$ | wc -l` != 0 ]; then mv *.so lib/; fi
	@if [ `ls | grep "\.o"$  | wc -l` != 0 ]; then mv *.o  lib/; fi
	@cp $@ bin/

############################################################################
# Phony rules (no prerequisites)
############################################################################

.PHONY: clean cln print xemacs backup clnPM test 

test:
	@echo $(VTXOBJS)

clean :
	@rm -f $(GARBAGE)

cln :
	@rm -f *~ *.o */*~

clnPM :
	@rm -f usePM pairManager.o SingleElectron.o */*~

print :
	@echo compiler  : $(CXX)
	@echo c++ srcs  : $(CXXSRCS)
	@echo c++ flags : $(CXXFLAGS)
	@echo libs      : $(LIBS)
	@echo so flags  : $(SOFLAGS)
	@echo rootlibs  : $(ROOTLIBS)

X = xemacs -geometry 80x80+1034+0

x:
	@$X \${PWD}/tools/cuts_for_theWiki_v3_trigginspec.cc/htozz.cc &
