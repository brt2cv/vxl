#ifndef vnl_test_h_
#define vnl_test_h_

//
// Copyright (C) 1991 Texas Instruments Incorporated.
//
// Permission is granted to any individual or institution to use, copy, modify,
// and distribute this software, provided that this complete copyright and
// permission notice is maintained, intact, in all copies and supporting
// documentation.
//
// Texas Instruments Incorporated provides this software "as is" without
// express or implied warranty.
//
// .NAME vnl_test
// .HEADER vxl package
// .LIBRARY vnl
// .INCLUDE vnl/vnl_test.h
// .FILE vnl_test.cxx

#include <vcl/vcl_string.h>

void vnl_test_start(const char* name);
void vnl_test_begin(const char* msg);
void vnl_test_perform(int success);
int  vnl_test_summary();

void vnl_test_assert(const vcl_string& msg, bool expr);
void vnl_test_assert_near(const vcl_string& msg, double expr, double target = 0, double tol = 1e-12);

#define Assert vnl_test_assert
#define AssertNear vnl_test_assert_near

#define START(s) vnl_test_start(s);

#define TEST(s,p,v) 		\
 {				\
  vnl_test_begin(s);	\
  vnl_test_perform(p==v);	\
 }

#define TEST_RUN(s,x,p,v) 	\
 {				\
  x;				\
  vnl_test_begin(s);	\
  vnl_test_perform(p==v);	\
 }

#define SUMMARY() vnl_test_summary();

#define TESTMAIN(x) int main() { vnl_test_start(#x); x(); return vnl_test_summary(); }

#endif // vnl_test_h_
