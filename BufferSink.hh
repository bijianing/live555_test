/**********
This library is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the
Free Software Foundation; either version 3 of the License, or (at your
option) any later version. (See <http://www.gnu.org/copyleft/lesser.html>.)

This library is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General Public License
along with this library; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
**********/
// "liveMedia"
// Copyright (c) 1996-2019 Live Networks, Inc.  All rights reserved.
// File Sinks
// C++ header

#ifndef _FILE_SINK_HH
#define _FILE_SINK_HH

#ifndef _MEDIA_SINK_HH
#include "MediaSink.hh"
#endif

class BufferSink: public MediaSink {
public:
  static BufferSink* createNew(UsageEnvironment& env,
				unsigned char * buffer,
				unsigned bufferSize);
  int getDataSize(void);


protected:
  BufferSink(UsageEnvironment& env, unsigned char *buffer, unsigned bufferSize);
      // called only by createNew()
  virtual ~BufferSink();

protected: // redefined virtual functions:
  virtual Boolean continuePlaying();

protected:
  static void afterGettingFrame(void* clientData, unsigned frameSize,
				unsigned numTruncatedBytes,
				struct timeval presentationTime,
				unsigned durationInMicroseconds);
  virtual void afterGettingFrame(unsigned frameSize,
				 unsigned numTruncatedBytes,
				 struct timeval presentationTime);

  unsigned char* fBuffer;
  unsigned fBufferSize;
  int fBufferIndex;
};

#endif
