/*
 * Tiny Vector Matrix Library
 * Dense Vector Matrix Libary of Tiny size using Expression Templates
 *
 * Copyright (C) 2001 - 2007 Olaf Petzold <opetzold@users.sourceforge.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * $Id: VectorBinaryFunctions.h,v 1.17 2007-06-23 15:58:58 opetzold Exp $
 */

#ifndef TVMET_VECTOR_BINARY_FUNCTIONS_H
#define TVMET_VECTOR_BINARY_FUNCTIONS_H

#include <gpumatrix/NumericTraits.h>
#include <gpumatrix/Extremum.h>

namespace gpumatrix {


/*********************************************************
 * PART I: DECLARATION
 *********************************************************/

/*
 * binary_function(Vector<T1>, Vector<T1>)
 * binary_function(Vector<T>, XprVector<E>)
 * binary_function(XprVector<E>, Vector<T>)
 */
#define TVMET_DECLARE_MACRO(NAME)				\
template<class T1, class T2, std::size_t Sz>			\
inline								\
XprVector<							\
  XprBinOp<							\
    Fcnl_##NAME<T1, T2>,					\
    XprVector<VectorConstReference<T1>>,				\
    XprVector<VectorConstReference<T2>>				\
  >								\
>								\
NAME(const Vector<T1>& lhs, 				\
     const Vector<T2>& rhs) TVMET_CXX_ALWAYS_INLINE;	\
								\
template<class E, class T, std::size_t Sz>			\
inline								\
XprVector<							\
  XprBinOp<							\
    Fcnl_##NAME<typename E::value_type, T>,			\
    XprVector<VectorConstReference<T>>,				\
    XprVector<E>						\
  >								\
>								\
NAME(const XprVector<E>& lhs, 				\
     const Vector<T>& rhs) TVMET_CXX_ALWAYS_INLINE;		\
								\
template<class E, class T, std::size_t Sz>			\
inline								\
XprVector<							\
  XprBinOp<							\
    Fcnl_##NAME<T, typename E::value_type>,			\
    XprVector<VectorConstReference<T>>,				\
    XprVector<E>						\
  >								\
>								\
NAME(const Vector<T>& lhs, 					\
     const XprVector<E>& rhs) TVMET_CXX_ALWAYS_INLINE;

TVMET_DECLARE_MACRO(atan2)
TVMET_DECLARE_MACRO(drem)
TVMET_DECLARE_MACRO(fmod)
TVMET_DECLARE_MACRO(hypot)
TVMET_DECLARE_MACRO(jn)
TVMET_DECLARE_MACRO(yn)
TVMET_DECLARE_MACRO(pow)
#if defined(TVMET_HAVE_COMPLEX)
TVMET_DECLARE_MACRO(polar)
#endif

#undef TVMET_DECLARE_MACRO


/*
 * binary_function(Vector<T>, POD)
 */
#define TVMET_DECLARE_MACRO(NAME, TP)				\
template<class T, std::size_t Sz>				\
inline								\
XprVector<							\
  XprBinOp<							\
    Fcnl_##NAME<T, TP >,					\
    XprVector<VectorConstReference<T>>,				\
    XprLiteral< TP >						\
  >								\
>								\
NAME(const Vector<T>& lhs, TP rhs) TVMET_CXX_ALWAYS_INLINE;

TVMET_DECLARE_MACRO(atan2, int)
TVMET_DECLARE_MACRO(drem, int)
TVMET_DECLARE_MACRO(fmod, int)
TVMET_DECLARE_MACRO(hypot, int)
TVMET_DECLARE_MACRO(jn, int)
TVMET_DECLARE_MACRO(yn, int)
TVMET_DECLARE_MACRO(pow, int)

#if defined(TVMET_HAVE_LONG_LONG)
TVMET_DECLARE_MACRO(atan2, long long int)
TVMET_DECLARE_MACRO(drem, long long int)
TVMET_DECLARE_MACRO(fmod, long long int)
TVMET_DECLARE_MACRO(hypot, long long int)
TVMET_DECLARE_MACRO(jn, long long int)
TVMET_DECLARE_MACRO(yn, long long int)
TVMET_DECLARE_MACRO(pow, long long int)
#endif // defined(TVMET_HAVE_LONG_LONG)

TVMET_DECLARE_MACRO(atan2, float)
TVMET_DECLARE_MACRO(drem, float)
TVMET_DECLARE_MACRO(fmod, float)
TVMET_DECLARE_MACRO(hypot, float)
TVMET_DECLARE_MACRO(jn, float)
TVMET_DECLARE_MACRO(yn, float)
TVMET_DECLARE_MACRO(pow, float)

TVMET_DECLARE_MACRO(atan2, double)
TVMET_DECLARE_MACRO(drem, double)
TVMET_DECLARE_MACRO(fmod, double)
TVMET_DECLARE_MACRO(hypot, double)
TVMET_DECLARE_MACRO(jn, double)
TVMET_DECLARE_MACRO(yn, double)
TVMET_DECLARE_MACRO(pow, double)

#if defined(TVMET_HAVE_LONG_DOUBLE)
TVMET_DECLARE_MACRO(atan2, long double)
TVMET_DECLARE_MACRO(drem, long double)
TVMET_DECLARE_MACRO(fmod, long double)
TVMET_DECLARE_MACRO(hypot, long double)
TVMET_DECLARE_MACRO(jn, long double)
TVMET_DECLARE_MACRO(yn, long double)
TVMET_DECLARE_MACRO(pow, long double)
#endif // defined(TVMET_HAVE_LONG_DOUBLE)

#undef TVMET_DECLARE_MACRO


/*
 * complex support
 */

#if defined(TVMET_HAVE_COMPLEX) && defined(TVMET_HAVE_COMPLEX_MATH1)
template<class T, std::size_t Sz>
XprVector<
  XprBinOp<
    Fcnl_pow<T, std::complex<T> >,
    XprVector<VectorConstReference<T>>,
    XprLiteral< std::complex<T> >
  >
>
pow(const Vector<T>& lhs,
    const std::complex<T>& rhs) TVMET_CXX_ALWAYS_INLINE;


template<class T, std::size_t Sz>
XprVector<
  XprBinOp<
    Fcnl_pow<std::complex<T>, std::complex<T> >,
    VectorConstReference<std::complex<T>>,
    XprLiteral< std::complex<T> >
  >
>
pow(const Vector<std::complex<T>>& lhs,
    const std::complex<T>& rhs) TVMET_CXX_ALWAYS_INLINE;


template<class T, std::size_t Sz>
XprVector<
  XprBinOp<
    Fcnl_pow<std::complex<T>, T>,
    VectorConstReference<std::complex<T>>,
    XprLiteral<T>
  >
>
pow(const Vector<std::complex<T>>& lhs,
    const T& rhs) TVMET_CXX_ALWAYS_INLINE;


template<class T, std::size_t Sz>
XprVector<
  XprBinOp<
    Fcnl_pow<std::complex<T>, int>,
    VectorConstReference<std::complex<T>>,
    XprLiteral<int>
  >
>
pow(const Vector<std::complex<T>>& lhs,
    int rhs) TVMET_CXX_ALWAYS_INLINE;


template<class T, std::size_t Sz>
XprVector<
  XprBinOp<
    Fcnl_polar<T, T>,
    XprVector<VectorConstReference<T>>,
    XprLiteral<T>
  >
>
polar(const Vector<T>& lhs, const T& rhs) TVMET_CXX_ALWAYS_INLINE;

#endif // defined(TVMET_HAVE_COMPLEX) && defined(TVMET_HAVE_COMPLEX_MATH1)

#if defined(TVMET_HAVE_COMPLEX) && defined(TVMET_HAVE_COMPLEX_MATH2)
// to be written (atan2)
#endif // defined(TVMET_HAVE_COMPLEX) && defined(TVMET_HAVE_COMPLEX_MATH2)


/*********************************************************
 * PART II: IMPLEMENTATION
 *********************************************************/

/*
 * binary_function(Vector<T1>, Vector<T1>)
 * binary_function(Vector<T>, XprVector<E>)
 * binary_function(XprVector<E>, Vector<T>)
 */
#define TVMET_IMPLEMENT_MACRO(NAME)					\
template<class T1, class T2, std::size_t Sz>				\
inline									\
XprVector<								\
  XprBinOp<								\
    Fcnl_##NAME<T1, T2>,						\
    XprVector<VectorConstReference<T1>>,					\
    XprVector<VectorConstReference<T2>>					\
  >									\
>									\
NAME(const Vector<T1>& lhs, const Vector<T2>& rhs) {		\
  typedef XprBinOp <							\
    Fcnl_##NAME<T1, T2>,						\
    XprVector<VectorConstReference<T1>>,					\
    XprVector<VectorConstReference<T2>>					\
  >							expr_type;	\
  return XprVector<expr_type>(					\
    expr_type(lhs.as_expr(), rhs.as_expr()));			\
}									\
									\
template<class E, class T, std::size_t Sz>				\
inline									\
XprVector<								\
  XprBinOp<								\
    Fcnl_##NAME<typename E::value_type, T>,				\
    XprVector<VectorConstReference<T>>,					\
    XprVector<E>							\
  >									\
>									\
NAME(const XprVector<E>& lhs, const Vector<T>& rhs) {		\
  typedef XprBinOp<							\
    Fcnl_##NAME<typename E::value_type, T>,				\
    XprVector<E>,							\
    XprVector<VectorConstReference<T>>						\
  > 							 expr_type;	\
  return XprVector<expr_type>(					\
    expr_type(lhs, rhs.as_expr()));					\
}									\
									\
template<class E, class T, std::size_t Sz>				\
inline									\
XprVector<								\
  XprBinOp<								\
    Fcnl_##NAME<T, typename E::value_type>,				\
    XprVector<VectorConstReference<T>>,					\
    XprVector<E>							\
  >									\
>									\
NAME(const Vector<T>& lhs, const XprVector<E>& rhs) {		\
  typedef XprBinOp<							\
    Fcnl_##NAME<T, typename E::value_type>,				\
    XprVector<VectorConstReference<T>>,					\
    XprVector<E>							\
  > 						 	expr_type;	\
  return XprVector<expr_type>(					\
    expr_type(lhs.as_expr(), rhs));					\
}

TVMET_IMPLEMENT_MACRO(atan2)
TVMET_IMPLEMENT_MACRO(drem)
TVMET_IMPLEMENT_MACRO(fmod)
TVMET_IMPLEMENT_MACRO(hypot)
TVMET_IMPLEMENT_MACRO(jn)
TVMET_IMPLEMENT_MACRO(yn)
TVMET_IMPLEMENT_MACRO(pow)
#if defined(TVMET_HAVE_COMPLEX)
TVMET_IMPLEMENT_MACRO(polar)
#endif

#undef TVMET_IMPLEMENT_MACRO


/*
 * binary_function(Vector<T>, POD)
 */
#define TVMET_IMPLEMENT_MACRO(NAME, TP)					\
template<class T, std::size_t Sz>					\
inline									\
XprVector<								\
  XprBinOp<								\
    Fcnl_##NAME<T, TP >,						\
    XprVector<VectorConstReference<T>>,					\
    XprLiteral< TP >							\
  >									\
>									\
NAME(const Vector<T>& lhs, TP rhs) {				\
  typedef XprBinOp<							\
    Fcnl_##NAME<T, TP >,						\
    XprVector<VectorConstReference<T>>,					\
    XprLiteral< TP >							\
  >							expr_type;	\
  return XprVector<expr_type>(					\
    expr_type(lhs.as_expr(), XprLiteral< TP >(rhs)));			\
}

TVMET_IMPLEMENT_MACRO(atan2, int)
TVMET_IMPLEMENT_MACRO(drem, int)
TVMET_IMPLEMENT_MACRO(fmod, int)
TVMET_IMPLEMENT_MACRO(hypot, int)
TVMET_IMPLEMENT_MACRO(jn, int)
TVMET_IMPLEMENT_MACRO(yn, int)
TVMET_IMPLEMENT_MACRO(pow, int)

#if defined(TVMET_HAVE_LONG_LONG)
TVMET_IMPLEMENT_MACRO(atan2, long long int)
TVMET_IMPLEMENT_MACRO(drem, long long int)
TVMET_IMPLEMENT_MACRO(fmod, long long int)
TVMET_IMPLEMENT_MACRO(hypot, long long int)
TVMET_IMPLEMENT_MACRO(jn, long long int)
TVMET_IMPLEMENT_MACRO(yn, long long int)
TVMET_IMPLEMENT_MACRO(pow, long long int)
#endif // defined(TVMET_HAVE_LONG_LONG)

TVMET_IMPLEMENT_MACRO(atan2, float)
TVMET_IMPLEMENT_MACRO(drem, float)
TVMET_IMPLEMENT_MACRO(fmod, float)
TVMET_IMPLEMENT_MACRO(hypot, float)
TVMET_IMPLEMENT_MACRO(jn, float)
TVMET_IMPLEMENT_MACRO(yn, float)
TVMET_IMPLEMENT_MACRO(pow, float)

TVMET_IMPLEMENT_MACRO(atan2, double)
TVMET_IMPLEMENT_MACRO(drem, double)
TVMET_IMPLEMENT_MACRO(fmod, double)
TVMET_IMPLEMENT_MACRO(hypot, double)
TVMET_IMPLEMENT_MACRO(jn, double)
TVMET_IMPLEMENT_MACRO(yn, double)
TVMET_IMPLEMENT_MACRO(pow, double)

#if defined(TVMET_HAVE_LONG_DOUBLE)
TVMET_IMPLEMENT_MACRO(atan2, long double)
TVMET_IMPLEMENT_MACRO(drem, long double)
TVMET_IMPLEMENT_MACRO(fmod, long double)
TVMET_IMPLEMENT_MACRO(hypot, long double)
TVMET_IMPLEMENT_MACRO(jn, long double)
TVMET_IMPLEMENT_MACRO(yn, long double)
TVMET_IMPLEMENT_MACRO(pow, long double)
#endif // defined(TVMET_HAVE_LONG_DOUBLE)

#undef TVMET_IMPLEMENT_MACRO


/*
 * complex support
 */

#if defined(TVMET_HAVE_COMPLEX) && defined(TVMET_HAVE_COMPLEX_MATH1)
/**
 * \fn pow(const Vector<T>& lhs, const std::complex<T>& rhs)
 * \ingroup _binary_function
 */
template<class T, std::size_t Sz>
inline
XprVector<
  XprBinOp<
    Fcnl_pow<T, std::complex<T> >,
    XprVector<VectorConstReference<T>>,
    XprLiteral< std::complex<T> >
  >
>
pow(const Vector<T>& lhs, const std::complex<T>& rhs) {
  typedef XprBinOp<
    Fcnl_pow<T, std::complex<T> >,
    XprVector<VectorConstReference<T>>,
    XprLiteral< std::complex<T> >
  >							expr_type;
  return XprVector<expr_type>(
      expr_type(lhs.as_expr(), XprLiteral< std::complex<T> >(rhs)));
}


/**
 * \fn pow(const Vector<std::complex<T>>& lhs, const std::complex<T>& rhs)
 * \ingroup _binary_function
 */
template<class T, std::size_t Sz>
inline
XprVector<
  XprBinOp<
    Fcnl_pow<std::complex<T>, std::complex<T> >,
    VectorConstReference<std::complex<T>>,
    XprLiteral< std::complex<T> >
  >
>
pow(const Vector<std::complex<T>>& lhs, const std::complex<T>& rhs) {
  typedef XprBinOp<
    Fcnl_pow<std::complex<T>, std::complex<T> >,
    VectorConstReference<std::complex<T>>,
    XprLiteral< std::complex<T> >
  >							expr_type;
  return XprVector<expr_type>(
      expr_type(lhs.as_expr(), XprLiteral< std::complex<T> >(rhs)));
}


/**
 * \fn pow(const Vector<std::complex<T>>& lhs, const T& rhs)
 * \ingroup _binary_function
 */
template<class T, std::size_t Sz>
inline
XprVector<
  XprBinOp<
    Fcnl_pow<std::complex<T>, T>,
    VectorConstReference<std::complex<T>>,
    XprLiteral<T>
  >
>
pow(const Vector<std::complex<T>>& lhs, const T& rhs) {
  typedef XprBinOp<
    Fcnl_pow<std::complex<T>, T>,
    VectorConstReference<std::complex<T>>,
    XprLiteral<T>
  >							expr_type;
  return XprVector<expr_type>(
      expr_type(lhs.as_expr(), XprLiteral<T>(rhs)));
}


/**
 * \fn pow(const Vector<std::complex<T>>& lhs, int rhs)
 * \ingroup _binary_function
 */
template<class T, std::size_t Sz>
inline
XprVector<
  XprBinOp<
    Fcnl_pow<std::complex<T>, int>,
    VectorConstReference<std::complex<T>>,
    XprLiteral<int>
  >
>
pow(const Vector<std::complex<T>>& lhs, int rhs) {
  typedef XprBinOp<
    Fcnl_pow<std::complex<T>, int>,
    VectorConstReference<std::complex<T>>,
    XprLiteral<int>
  >							expr_type;
  return XprVector<expr_type>(
      expr_type(lhs.as_expr(), XprLiteral<int>(rhs)));
}


/**
 * \fn polar(const Vector<T>& lhs, const T& rhs)
 * \ingroup _binary_function
 */
template<class T, std::size_t Sz>
inline
XprVector<
  XprBinOp<
    Fcnl_polar<T, T>,
    XprVector<VectorConstReference<T>>,
    XprLiteral<T>
  >
>
polar(const Vector<T>& lhs, const T& rhs) {
  typedef XprBinOp<
    Fcnl_polar<T, T>,
    XprVector<VectorConstReference<T>>,
    XprLiteral<T>
  >							expr_type;
  return XprVector<expr_type>(
      expr_type(lhs.as_expr(), XprLiteral<T>(rhs)));
}
#endif // defined(TVMET_HAVE_COMPLEX) && defined(TVMET_HAVE_COMPLEX_MATH1)

#if defined(TVMET_HAVE_COMPLEX) && defined(TVMET_HAVE_COMPLEX_MATH2)
// to be written (atan2)
#endif // defined(TVMET_HAVE_COMPLEX) && defined(TVMET_HAVE_COMPLEX_MATH2)


} // namespace gpumatrix

#endif // TVMET_VECTOR_BINARY_FUNCTIONS_H

// Local Variables:
// mode:C++
// tab-width:8
// End:
