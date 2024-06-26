// @(#)root/io:$Id$
// Author: Jakob Blomer

/*************************************************************************
 * Copyright (C) 1995-2018, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_RRawFileUnix
#define ROOT_RRawFileUnix

#include <ROOT/RRawFile.hxx>
#include <string_view>

#include <cstddef>
#include <cstdint>

namespace ROOT {
namespace Internal {

/**
 * \class RRawFileUnix RRawFileUnix.hxx
 * \ingroup IO
 *
 * The RRawFileUnix class uses POSIX calls to read from a mounted file system. Thus the path name can refer,
 * for instance, to a named pipe instead of a regular file.
 */
class RRawFileUnix : public RRawFile {
private:
   int fFileDes = -1;

protected:
   void OpenImpl() final;
   size_t ReadAtImpl(void *buffer, size_t nbytes, std::uint64_t offset) final;
   void ReadVImpl(RIOVec *ioVec, unsigned int nReq) final;
   std::uint64_t GetSizeImpl() final;

public:
   RRawFileUnix(std::string_view url, RRawFile::ROptions options);
   ~RRawFileUnix() override;
   std::unique_ptr<RRawFile> Clone() const final;
   int GetFd() const { return fFileDes; }
};

} // namespace Internal
} // namespace ROOT

#endif
