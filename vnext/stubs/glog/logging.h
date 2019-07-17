// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// TODO: Use actual glog
// TODO: Using actual glog non-trivial as it uses Desktop only APIs
// TODO: Maybe implement glog header in terms of Windows'
// TraceLoggingProvider.h?

#pragma once
#include <iostream>

#define CHECK(b) !(b) && (std::abort(), true) && std::cerr
#define CHECK_GE(a, b) !(a >= b) && (std::abort(), true) && std::cerr
#define DCHECK(b) !(b) && (std::abort(), true) && std::cerr

#ifdef DEBUG
#define DCHECK_GT(v1, v2) CHECK((v1) > (v2))
#else
#define DCHECK_GT(v1, v2)
#endif

#ifdef DEBUG
#define DCHECK_LE(v1, v2) CHECK((v1) <= (v2))
#else
#define DCHECK_LE(v1, v2)
#endif

#ifdef DEBUG
#define DCHECK_GE(v1, v2) CHECK((v1) >= (v2))
#else
#define DCHECK_GE(v1, v2)
#endif

#ifdef DEBUG
#define DCHECK_EQ(v1, v2) CHECK((v1) == (v2))
#else
#define DCHECK_EQ(v1, v2)
#endif

#ifndef LOG

namespace GlogStub {

struct NullBuffer : public std::streambuf {
  // Put character on overflow.
  // It is called by other functions in streambuf.
  // By doing nothing in this function and not returning error, we effectively
  // implement a streambuf that does nothing and just 'eats' the input.
  int overflow(int c) override {
    return c;
  }
};

inline std::ostream &GetNullLog() noexcept {
  static NullBuffer nullBuffer;
  static std::ostream nullStream(&nullBuffer);
  return nullStream;
}

} // namespace GlogStub

#define LOG(b) GlogStub::GetNullLog()
#endif
