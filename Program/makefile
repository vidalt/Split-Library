all : split

CCC = g++
CCFLAGS = -O3
LIBS= -lm
TARGETDIR=.
CPPFLAGS += \
         -I.

        
OBJS2 = \
        $(TARGETDIR)/commandline.o \
	    $(TARGETDIR)/main.o \
        $(TARGETDIR)/Pb_Data.o \
        $(TARGETDIR)/Split_Bellman.o \
        $(TARGETDIR)/Split_Bellman_Bounded.o \
        $(TARGETDIR)/Split_Bellman_Soft.o \
        $(TARGETDIR)/Split_Linear.o \
        $(TARGETDIR)/Split_Linear_Bounded.o \
        $(TARGETDIR)/Split_Linear_Soft.o

$(TARGETDIR)/split: $(OBJS2)
	$(CCC)  $(CCFLAGS) -o $(TARGETDIR)/split $(OBJS2)

$(TARGETDIR)/commandline.o:
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c commandline.cpp -o $(TARGETDIR)/commandline.o
	
$(TARGETDIR)/main.o:
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c main.cpp -o $(TARGETDIR)/main.o

$(TARGETDIR)/Pb_Data.o: Pb_Data.h Pb_Data.cpp
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c Pb_Data.cpp -o $(TARGETDIR)/Pb_Data.o

$(TARGETDIR)/Split_Bellman.o: Split_Bellman.h Split_Bellman.cpp
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c Split_Bellman.cpp -o $(TARGETDIR)/Split_Bellman.o

$(TARGETDIR)/Split_Bellman_Bounded.o: Split_Bellman_Bounded.h Split_Bellman_Bounded.cpp
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c Split_Bellman_Bounded.cpp -o $(TARGETDIR)/Split_Bellman_Bounded.o

$(TARGETDIR)/Split_Bellman_Soft.o: Split_Bellman_Soft.h Split_Bellman_Soft.cpp
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c Split_Bellman_Soft.cpp -o $(TARGETDIR)/Split_Bellman_Soft.o

$(TARGETDIR)/Split_Linear.o: Split_Linear.h Split_Linear.cpp
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c Split_Linear.cpp -o $(TARGETDIR)/Split_Linear.o

$(TARGETDIR)/Split_Linear_Bounded.o: Split_Linear_Bounded.h Split_Linear_Bounded.cpp
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c Split_Linear_Bounded.cpp -o $(TARGETDIR)/Split_Linear_Bounded.o

$(TARGETDIR)/Split_Linear_Soft.o: Split_Linear_Soft.h Split_Linear_Soft.cpp
	$(CCC) $(CCFLAGS) $(CPPFLAGS) -c Split_Linear_Soft.cpp -o $(TARGETDIR)/Split_Linear_Soft.o

clean:
	 $(RM) \
	 $(TARGETDIR)/split \
     $(TARGETDIR)/commandline.o \
	 $(TARGETDIR)/main.o \
     $(TARGETDIR)/Pb_Data.o \
     $(TARGETDIR)/Split_Bellman.o \
     $(TARGETDIR)/Split_Bellman_Bounded.o \
     $(TARGETDIR)/Split_Bellman_Soft.o \
     $(TARGETDIR)/Split_Linear.o \
     $(TARGETDIR)/Split_Linear_Bounded.o \
     $(TARGETDIR)/Split_Linear_Soft.o

