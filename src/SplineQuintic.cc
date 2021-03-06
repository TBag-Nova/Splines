/*--------------------------------------------------------------------------*\
 |                                                                          |
 |  Copyright (C) 2016                                                      |
 |                                                                          |
 |         , __                 , __                                        |
 |        /|/  \               /|/  \                                       |
 |         | __/ _   ,_         | __/ _   ,_                                | 
 |         |   \|/  /  |  |   | |   \|/  /  |  |   |                        |
 |         |(__/|__/   |_/ \_/|/|(__/|__/   |_/ \_/|/                       |
 |                           /|                   /|                        |
 |                           \|                   \|                        |
 |                                                                          |
 |      Enrico Bertolazzi                                                   |
 |      Dipartimento di Ingegneria Industriale                              |
 |      Universita` degli Studi di Trento                                   |
 |      email: enrico.bertolazzi@unitn.it                                   |
 |                                                                          |
\*--------------------------------------------------------------------------*/

#include "Splines.hh"
#include "SplinesUtils.hh"
#include <cmath>

/**
 * 
 */

namespace Splines {

  using namespace std; // load standard namspace

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  /*\
     Sistema lineare da risolvere

     D U
     L D U
       L D U
         L D U
           .....
              L D U
                L D U
                  L D

  \*/

  static
  void
  QuinticSpline_Yppp_continuous(
    real_type const X[],
    real_type const Y[],
    real_type const Yp[],
    real_type       Ypp[],
    integer         npts,
    bool            setbc
  ) {

    size_t n = size_t(npts > 0 ? npts-1 : 0);

    vector<real_type> buffer(3*(n+1));
    real_type * ptr = &buffer.front();
    real_type * L = ptr; ptr += npts;
    real_type * D = ptr; ptr += npts;
    real_type * U = ptr;
    real_type * Z = Ypp;

    size_t i;
    for ( i = 1; i < n; ++i ) {
      real_type hL  = X[i] - X[i-1];
      real_type hL2 = hL*hL;
      real_type hL3 = hL*hL2;
      real_type hR  = X[i+1] - X[i];
      real_type hR2 = hR*hR;
      real_type hR3 = hR*hR2;
      real_type DL  = 60*(Y[i]-Y[i-1])/hL3;
      real_type DR  = 60*(Y[i+1]-Y[i])/hR3;
      real_type DDL = (36*Yp[i]+24*Yp[i-1])/hL2;
      real_type DDR = (36*Yp[i]+24*Yp[i+1])/hR2;
      L[i] = -3/hL;
      D[i] = 9/hL+9/hR;
      U[i] = -3/hR;
      Z[i] = DR-DL+DDL-DDR;
    }
    L[0] = U[0] = 0; D[0] = 1;
    L[n] = U[n] = 0; D[n] = 1;
    if ( setbc ) {
      {
        real_type hL = X[1] - X[0];
        real_type hR = X[2] - X[1];
        real_type SL = (Y[1]-Y[0])/hL;
        real_type SR = (Y[2]-Y[1])/hR;
        real_type dp0 = Yp[1];
        real_type dpL = Yp[0];
        real_type dpR = Yp[2];
        Z[0] = second_deriv3p_L( SL, hL, SR, hR, dpL, dp0, dpR );
      }
      {
        real_type hL = X[n-1] - X[n-2];
        real_type hR = X[n] - X[n-1];
        real_type SL = (Y[n-1]-Y[n-2])/hL;
        real_type SR = (Y[n]-Y[n-1])/hR;
        real_type dp0 = Yp[n-1];
        real_type dpL = Yp[n-2];
        real_type dpR = Yp[n];
        Z[n] = second_deriv3p_R( SL, hL, SR, hR, dpL, dp0, dpR );
      }
    }

    i = 0;
    do {
      Z[i]   /= D[i];
      U[i]   /= D[i];
      D[i+1] -= L[i+1] * U[i];
      Z[i+1] -= L[i+1] * Z[i];
    } while ( ++i < n );

    Z[i] /= D[i];

    do {
      --i;
      Z[i] -= U[i] * Z[i+1];
    } while ( i > 0 );
  }

  static
  void
  QuinticSpline_Ypp_build(
    real_type const X[],
    real_type const Y[],
    real_type const Yp[],
    real_type       Ypp[],
    integer         npts
  ) {

    size_t n = size_t(npts > 0 ? npts-1 : 0);

    if ( n == 1 ) { Ypp[0] = Ypp[1] = 0; return; }

    {
      real_type hL = X[1] - X[0];
      real_type hR = X[2] - X[1];
      real_type SL = (Y[1] - Y[0])/hL;
      real_type SR = (Y[2] - Y[1])/hR;
      //Ypp[0] = (2*SL-SR)*al+SL*be;
      //Ypp[0] = second_deriv3p_L( SL, hL, SR, hR, Yp[0] );
      Ypp[0] = second_deriv3p_L( SL, hL, SR, hR, Yp[0], Yp[1], Yp[2] );
    }
    {
      real_type hL = X[n-1] - X[n-2];
      real_type hR = X[n] - X[n-1];
      real_type SL = (Y[n-1] - Y[n-2])/hL;
      real_type SR = (Y[n] - Y[n-1])/hR;
      //Ypp[n] = (2*SR-SL)*be+SR*al;
      //Ypp[n] = second_deriv3p_R( SL, hL, SR, hR, Yp[n] );
      Ypp[n] = second_deriv3p_R( SL, hL, SR, hR, Yp[n-2], Yp[n-1], Yp[n] );
    }

    size_t i;
    for ( i = 1; i < n; ++i ) {
      real_type hL = X[i] - X[i-1];
      real_type hR = X[i+1] - X[i];
      real_type SL = (Y[i] - Y[i-1])/hL;
      real_type SR = (Y[i+1] - Y[i])/hR;
      //Ypp[i] = second_deriv3p_C( SL, hL, SR, hR, Yp[i] );
      real_type ddC = second_deriv3p_C( SL, hL, SR, hR, Yp[i-1], Yp[i], Yp[i+1] );
      if ( i > 1 ) {
        real_type hLL = X[i-1] - X[i-2];
        real_type SLL = (Y[i-1] - Y[i-2])/hLL;
        //real_type dd  = second_deriv3p_R( SLL, hLL, SL, hR, Yp[i] );
        real_type ddL = second_deriv3p_R( SLL, hLL, SL, hR, Yp[i-2], Yp[i-1], Yp[i] );
        if      ( ddL * ddC < 0 ) ddC = 0;
        else if ( std::abs(ddL) < std::abs(ddC) ) ddC = ddL;
      }
      if ( i < n-1 ) {
        real_type hRR = X[i+2] - X[i+1];
        real_type SRR = (Y[i+2] - Y[i+1])/hRR;
        //real_type dd = second_deriv3p_L( SR, hR, SRR, hRR, Yp[i] );
        real_type ddR = second_deriv3p_L( SR, hR, SRR, hRR, Yp[i], Yp[i+1], Yp[i+2] );
        if      ( ddR * ddC < 0 ) ddC = 0;
        else if ( std::abs(ddR) < std::abs(ddC) ) ddC = ddR;
      }
      Ypp[i] = ddC;
    }
  }

  /*\
   |    ___        _       _   _      ____        _ _
   |   / _ \ _   _(_)_ __ | |_(_) ___/ ___| _ __ | (_)_ __   ___
   |  | | | | | | | | '_ \| __| |/ __\___ \| '_ \| | | '_ \ / _ \
   |  | |_| | |_| | | | | | |_| | (__ ___) | |_) | | | | | |  __/
   |   \__\_\\__,_|_|_| |_|\__|_|\___|____/| .__/|_|_|_| |_|\___|
   |                                       |_|
   |
  \*/

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  static
  void
  Quintic_build(
    QUINTIC_SPLINE_TYPE q_sub_type,
    real_type const     X[],
    real_type const     Y[],
    real_type           Yp[],
    real_type           Ypp[],
    integer             npts
  ) {
    switch ( q_sub_type ) {
    case CUBIC_QUINTIC:
      {
        size_t n = size_t(npts > 0 ? npts-1 : 0);
        vector<real_type> buffer(3*(n+1));
        real_type * ptr = &buffer.front();
        real_type * L   = ptr; ptr += npts;
        real_type * D   = ptr; ptr += npts;
        real_type * U   = ptr;
        CubicSpline_build(
          X, Y, Yp, Ypp, L, D, U, npts, EXTRAPOLATE_BC, EXTRAPOLATE_BC
        );
        QuinticSpline_Yppp_continuous( X, Y, Yp, Ypp, npts, false );
      }
      return;
    case PCHIP_QUINTIC:
      Pchip_build( X, Y, Yp, npts );
      break;
    case AKIMA_QUINTIC:
      Akima_build( X, Y, Yp, npts );
      break;
    case BESSEL_QUINTIC:
      Bessel_build( X, Y, Yp, npts );
      break;
    }
    QuinticSpline_Ypp_build( X, Y, Yp, Ypp, npts );
  }

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  QuinticSpline::build() {
    SPLINE_ASSERT(
      this->npts > 1,
      "QuinticSpline::build(): npts = " << this->npts << " not enought points"
    )
    integer ibegin = 0;
    integer iend   = 0;
    do {
      // cerca intervallo monotono strettamente crescente
      while ( ++iend < this->npts && this->X[iend-1] < this->X[iend] ) {}
      Quintic_build(
        this->q_sub_type,
        this->X+ibegin,  this->Y+ibegin,
        this->Yp+ibegin, this->Ypp+ibegin,
        iend - ibegin
      );
      ibegin = iend;
    } while ( iend < this->npts );

    SPLINE_CHECK_NAN( this->Yp,  "QuinticSpline::build(): Yp",  this->npts );
    SPLINE_CHECK_NAN( this->Ypp, "QuinticSpline::build(): Ypp", this->npts );
  }

  using GenericContainerNamespace::GC_VEC_REAL;
  using GenericContainerNamespace::vec_real_type;

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  void
  QuinticSpline::setup( GenericContainer const & gc ) {
    /*
    // gc["xdata"]
    // gc["ydata"]
    //
    */
    SPLINE_ASSERT(
      gc.exists("xdata"),
      "QuinticSpline[" << this->_name << "]::setup missing `xdata` field!"
    )
    SPLINE_ASSERT(
      gc.exists("ydata"),
      "QuinticSpline[" << this->_name << "]::setup missing `ydata` field!"
    )

    GenericContainer const & gc_x = gc("xdata");
    GenericContainer const & gc_y = gc("ydata");

    vec_real_type x, y;
    {
      std::ostringstream ost;
      ost << "QuinticSpline[" << this->_name << "]::setup, field `xdata'";
      gc_x.copyto_vec_real ( x, ost.str().c_str() );
    }
    {
      std::ostringstream ost;
      ost << "QuinticSpline[" << this->_name << "]::setup, field `ydata'";
      gc_y.copyto_vec_real ( y, ost.str().c_str() );
    }
    if ( gc.exists("spline_sub_type") ) {
      std::string const & st = gc("spline_sub_type").get_string();
      if      ( st == "cubic"  ) this->q_sub_type = CUBIC_QUINTIC;
      else if ( st == "pchip"  ) this->q_sub_type = PCHIP_QUINTIC;
      else if ( st == "akima"  ) this->q_sub_type = AKIMA_QUINTIC;
      else if ( st == "bessel" ) this->q_sub_type = BESSEL_QUINTIC;
      else {
        SPLINE_DO_ERROR(
          "QuinticSpline[" << this->_name << "]::setup unknow sub type:" << st
        )
      }
    } else {
      SPLINE_WARNING( false, "QuinticSpline::setup, missing field `spline_sub_type` using `cubic` as default value")
    }
    this->build( x, y );
  }

}
