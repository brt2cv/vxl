//-*- c++ -*-------------------------------------------------------------------
#ifdef __GNUC__
#pragma implementation "vnl_unary_function.h"
#endif
//
// Class: UnaryFunction
// Author: Andrew W. Fitzgibbon, Oxford RRG
// Created: 28 Nov 98
// Modifications:
//   981128 AWF Initial version.
//
//-----------------------------------------------------------------------------

#include "vnl_unary_function.h"
#include "vnl_identity.h"
#include <vnl/vnl_vector.h>

template class vnl_unary_function<int,int>;
template class vnl_identity<int>;

template class vnl_unary_function<double, vnl_vector<double> >;
