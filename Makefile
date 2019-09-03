TARG = bufferSinkTest
all : $(TARG)

LIVE555_DIR=../live555
LIBDIR=$(LIVE555_DIR)/liveMedia
CFLAGS=-I$(LIBDIR)/include -I$(LIVE555_DIR)/groupsock/include -I$(LIVE555_DIR)/UsageEnvironment/include -I$(LIVE555_DIR)/BasicUsageEnvironment/include

SRCS=$(TARG).cpp  BufferSink.cpp
$(TARG): $(SRCS) BufferSink.hh
	echo c++ $(CFLAGS) -L$(LIBDIR) -lliveMedia -o $@ $(SRCS)
	c++ $(CFLAGS) -L$(LIBDIR) -lliveMedia -o $@ $(SRCS)
