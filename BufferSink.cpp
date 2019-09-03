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
// File sinks
// Implementation

#if (defined(__WIN32__) || defined(_WIN32)) && !defined(_WIN32_WCE)
#include <io.h>
#include <fcntl.h>
#endif
#include "BufferSink.hh"
#include "GroupsockHelper.hh"
#include "OutputFile.hh"

////////// BufferSink //////////

BufferSink::BufferSink(UsageEnvironment& env, unsigned char *buffer, unsigned bufferSize)
  : MediaSink(env), fBuffer(buffer), fBufferSize(bufferSize), fBufferIndex(0) {
}

BufferSink::~BufferSink() {
}

BufferSink* BufferSink::createNew(UsageEnvironment& env,
				unsigned char *buffer,
				unsigned bufferSize) {
  return new BufferSink(env, buffer, bufferSize);
}

Boolean BufferSink::continuePlaying() {
  if (fSource == NULL) return False;

  fSource->getNextFrame(fBuffer + fBufferIndex, fBufferSize,
			afterGettingFrame, this,
			onSourceClosure, this);

  return True;
}

void BufferSink::afterGettingFrame(void* clientData, unsigned frameSize,
				 unsigned numTruncatedBytes,
				 struct timeval /*presentationTime*/,
				 unsigned /*durationInMicroseconds*/) {
  BufferSink* sink = (BufferSink*)clientData;
  if (numTruncatedBytes > 0) {
    envir() << "BufferSink::afterGettingFrame(): The input frame data was too large for our buffer size ("
	    << fBufferSize << ").  "
            << numTruncatedBytes << " bytes of trailing data was dropped!  Correct this by increasing the \"bufferSize\" parameter in the \"createNew()\" call to at least "
            << fBufferSize + numTruncatedBytes << "\n";
  }

  fBufferIndex += frameSize;

}

int BufferSink::getDataSize(void)
{
  return fBufferIndex;
}
