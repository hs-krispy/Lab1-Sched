CXX				= g++
INC 			= -I${CURDIR}/include/
CXXFLAGS	= -g $(INC)

OBJS_LAB1 = lab1_sched.o lab1_sched_test.o
SRCS = $(OBJS_LAB1:.o=.cc)

TARGET_LAB1 = lab1_sched

.SUFFIXES : .cc .o

.cc.o:
	@echo "Compilingi lab1 scheduler simulator $< ..."
	$(CXX) -c $(CXXFLAGS) -o $@ $<

$(TARGET_LAB1) : $(OBJS_LAB1)
	$(CXX) -o $(TARGET_LAB1) $(OBJS_LAB1)

all : $(TARGET_LAB1)

clean : 
	@ehco "Cleaning lab1 scheduler simulator $< ..."
	rm -rf $(OBJS_LAB1) $(TARGET_LAB1)

new :
	$(MAKE) clean
	$(MAKE)



# CC = gcc
# INC = -I${CURDIR}/include/
# CFLAGS = -g $(INC)

# OBJS_LAB1 = lab1_sched.o lab1_sched_test.o 

# SRCS = $(OBJS_LAB1:.o=.c)

# TARGET_LAB1 = lab1_sched

# .SUFFIXES : .c .o

# .c.o:
# 	@echo "Compilingi lab1 scheduler simulator $< ..."
# 	$(CC) -c $(CFLAGS) -o $@ $<

# $(TARGET_LAB1) : $(OBJS_LAB1)
# 	$(CC) -o $(TARGET_LAB1) $(OBJS_LAB1)

# all : $(TARGET_LAB1)

# dep : 
# 	gccmaedep $(INC) $(SRCS)

# clean :
# 	@echo "Cleaning lab1 scheduler simulator $< ..."
# 	rm -rf $(OBJS_LAB1) $(TARGET_LAB1) 

# new :
# 	$(MAKE) clean
# 	$(MAKE)