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

/*!
\mainpage  Spline class
\author    Enrico Bertolazzi (enrico.bertolazzi@unitn.it), homepage: http://www.ing.unitn.it/~bertolaz
\date      2016
\copyright see file license.txt
*/

#pragma once

#ifndef SPLINES_HH
#define SPLINES_HH

#include "SplinesConfig.hh"

#ifndef SPLINE_DO_ERROR
  #include <stdexcept>
  #include <sstream>
  #define SPLINE_DO_ERROR(MSG)           \
  {                                      \
    std::ostringstream ost;              \
    Splines::backtrace( ost );           \
    ost << "In spline: " << name()       \
        << " line: " << __LINE__         \
        << " file: " << __FILE__         \
        << '\n' << MSG << '\n';          \
    throw std::runtime_error(ost.str()); \
  }
#endif

#ifndef SPLINE_ASSERT
  #include <stdexcept>
  #include <sstream>
  #define SPLINE_ASSERT(COND,MSG) if ( !(COND) ) SPLINE_DO_ERROR(MSG)
#endif

#ifndef SPLINE_WARNING
  #include <stdexcept>
  #include <sstream>
  #define SPLINE_WARNING(COND,MSG)         \
    if ( !(COND) ) {                       \
      std::cout << "In spline: " << name() \
                << " line: " << __LINE__   \
                << " file: " << __FILE__   \
                << MSG << '\n';            \
    }
#endif

#ifndef SPLINES_OVERRIDE
  #define SPLINES_OVERRIDE override
#endif

#ifndef SPLINES_PURE_VIRTUAL
  #define SPLINES_PURE_VIRTUAL = 0
#endif

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wc++98-compat"
#endif

//! Various kind of splines
namespace Splines {

  using namespace ::std; // load standard namespace

  typedef double real_type; //!< Floating point type for splines
  typedef int    integer;   //!< Signed integer type for splines
  typedef basic_ostream<char> ostream_type;

  void backtrace( ostream_type & );

  //! Associate a number for each type of splines implemented
  typedef enum {
    CONSTANT_TYPE   = 0,
    LINEAR_TYPE     = 1,
    CUBIC_TYPE      = 2,
    AKIMA_TYPE      = 3,
    BESSEL_TYPE     = 4,
    PCHIP_TYPE      = 5,
    QUINTIC_TYPE    = 6,
    HERMITE_TYPE    = 7,
    SPLINE_SET_TYPE = 8,
    SPLINE_VEC_TYPE = 9
  } SplineType1D;

  //! Associate a number for each type of splines implemented
  typedef enum {
    BILINEAR_TYPE  = 0,
    BICUBIC_TYPE   = 1,
    BIQUINTIC_TYPE = 2,
    AKIMA2D_TYPE   = 3
  } SplineType2D;

  extern char const *spline_type_1D[];

  extern SplineType1D string_to_splineType( string const & n );

  using GenericContainerNamespace::GenericContainer;
  using GenericContainerNamespace::vec_real_type;
  using GenericContainerNamespace::vec_string_type;
  using GenericContainerNamespace::vector_type;
  using GenericContainerNamespace::map_type;

  pair<int,int>
  quadraticRoots(
    real_type const a[3],
    real_type       real[2],
    real_type       imag[2]
  );

  pair<int,int>
  cubicRoots(
    real_type const a[4],
    real_type       real[3],
    real_type       imag[3]
  );

  /*       _               _    _   _       _   _
  //   ___| |__   ___  ___| | _| \ | | __ _| \ | |
  //  / __| '_ \ / _ \/ __| |/ /  \| |/ _` |  \| |
  // | (__| | | |  __/ (__|   <| |\  | (_| | |\  |
  //  \___|_| |_|\___|\___|_|\_\_| \_|\__,_|_| \_|
  */
  void
  checkNaN(
    real_type const pv[],
    char      const v_name[],
    integer         DIM
  );

  /*
  //   _   _                     _ _
  //  | | | | ___ _ __ _ __ ___ (_) |_ ___
  //  | |_| |/ _ \ '__| '_ ` _ \| | __/ _ \
  //  |  _  |  __/ |  | | | | | | | ||  __/
  //  |_| |_|\___|_|  |_| |_| |_|_|\__\___|
  */
  void Hermite3( real_type x, real_type H, real_type base[4] );
  void Hermite3_D( real_type x, real_type H, real_type base_D[4] );
  void Hermite3_DD( real_type x, real_type H, real_type base_DD[4] );
  void Hermite3_DDD( real_type x, real_type H, real_type base_DDD[4] );

  void Hermite5( real_type x, real_type H, real_type base[6] );
  void Hermite5_D( real_type x, real_type H, real_type base_D[6] );
  void Hermite5_DD( real_type x, real_type H, real_type base_DD[6] );
  void Hermite5_DDD( real_type x, real_type H, real_type base_DDD[6] );
  void Hermite5_DDDD( real_type x, real_type H, real_type base_DDDD[6] );
  void Hermite5_DDDDD( real_type x, real_type H, real_type base_DDDDD[6] );

  /*
  //   ____  _ _ _
  //  | __ )(_) (_)_ __   ___  __ _ _ __
  //  |  _ \| | | | '_ \ / _ \/ _` | '__|
  //  | |_) | | | | | | |  __/ (_| | |
  //  |____/|_|_|_|_| |_|\___|\__,_|_|
  */
  real_type
  bilinear3(
    real_type const p[4],
    real_type const M[4][4],
    real_type const q[4]
  );

  real_type
  bilinear5(
    real_type const p[6],
    real_type const M[6][6],
    real_type const q[6]
  );

  //! Check if cubic spline with this data is monotone, -1 no, 0 yes, 1 strictly monotone
  integer
  checkCubicSplineMonotonicity(
    real_type const X[],
    real_type const Y[],
    real_type const Yp[],
    integer         npts
  );

  /*
  //   __  __       _ _
  //  |  \/  | __ _| | | ___   ___
  //  | |\/| |/ _` | | |/ _ \ / __|
  //  | |  | | (_| | | | (_) | (__
  //  |_|  |_|\__,_|_|_|\___/ \___|
  */

  //! Allocate memory
  template <typename T>
  class SplineMalloc {
  public:
    typedef T valueType;

  private:

    string      _name;
    size_t      numTotValues;
    size_t      numTotReserved;
    size_t      numAllocated;
    valueType * pMalloc;

    SplineMalloc( SplineMalloc<T> const & ) = delete;
    SplineMalloc<T> const & operator = ( SplineMalloc<T> & ) const = delete ;

  public:

    //! malloc object constructor
    explicit
    SplineMalloc( string const & __name )
    : _name(__name)
    , numTotValues(0)
    , numTotReserved(0)
    , numAllocated(0)
    , pMalloc(nullptr)
    {}

    //! malloc object destructor
    ~SplineMalloc()
    { free(); }

    //! allocate memory for `n` objects
    void
    allocate( size_t n ) {
      try {
        if ( n > numTotReserved ) {
          delete [] pMalloc;
          numTotValues   = n;
          numTotReserved = n + (n>>3); // 12% more values
          pMalloc        = new T[numTotReserved];
        }
      }
      catch ( std::exception const & exc ) {
        std::cerr
          << "Memory allocation failed: " << exc.what()
          << "\nTry to allocate " << n << " bytes for " << _name
          << '\n';
        exit(0);
      }
      catch (...) {
        std::cerr
          << "SplineMalloc allocation failed for " << _name << ": memory exausted\n"
          << "Requesting " << n << " blocks\n";
        exit(0);
      }
      numTotValues = n;
      numAllocated = 0;
    }

    //! free memory
    void
    free(void) {
      if ( pMalloc != nullptr ) {
        delete [] pMalloc;
        numTotValues   = 0;
        numTotReserved = 0;
        numAllocated   = 0;
        pMalloc        = nullptr;
      }
    }

    //! number of objects allocated
    size_t size(void) const { return numTotValues; }

    //! get pointer of allocated memory for `sz` objets
    T *
    operator () ( size_t sz ) {
      size_t offs = numAllocated;
      numAllocated += sz;
      if ( numAllocated > numTotValues ) {
        std::ostringstream ost;
        ost
          << "\nMalloc<" << _name
          << ">::operator () (" << sz << ") -- SplineMalloc EXAUSTED\n"
          << "request = " << numAllocated << " > "
          << numTotValues << " = available\n";
        throw std::runtime_error(ost.str());
      }
      return pMalloc + offs;
    }

    void
    must_be_empty( char const where[] ) const {
      if ( numAllocated < numTotValues ) {
        std::ostringstream ost;
        ost
          << "\nMalloc<" << _name << ">\n"
          << "in " << _name << " " << where
          << ": not fully used!\nUnused: "
          << numTotValues - numAllocated << " values\n";
        throw std::runtime_error(ost.str());
      }
      if ( numAllocated > numTotValues ) {
        std::ostringstream ost;
        ost
          << "\nMalloc<" << _name << ">\n"
          << "in " << _name << " " << where
          << ": too much used!\nMore used: "
          << numAllocated - numTotValues << " values\n";
        throw std::runtime_error(ost.str());
      }
    }
  };

  /*\
   |  ____                                _        _          _   _
   | |  _ \ __ _ _ __ __ _ _ __ ___   ___| |_ _ __(_)______ _| |_(_) ___  _ __
   | | |_) / _` | '__/ _` | '_ ` _ \ / _ \ __| '__| |_  / _` | __| |/ _ \| '_ \
   | |  __/ (_| | | | (_| | | | | | |  __/ |_| |  | |/ / (_| | |_| | (_) | | | |
   | |_|   \__,_|_|  \__,_|_| |_| |_|\___|\__|_|  |_/___\__,_|\__|_|\___/|_| |_|
   |
  \*/

  void
  uniform(
    integer         dim,
    integer         npts,
    real_type const pnts[],
    integer         ld_pnts,
    real_type       t[]
  );

  void
  chordal(
    integer         dim,
    integer         npts,
    real_type const pnts[],
    integer         ld_pnts,
    real_type       t[]
  );

  void
  centripetal(
    integer         dim,
    integer         npts,
    real_type const pnts[],
    integer         ld_pnts,
    real_type const alpha,
    real_type       t[]
  );

  void
  universal(
    integer         dim,
    integer         npts,
    real_type const pnts[],
    integer         ld_pnts,
    real_type       t[]
  );

  void
  FoleyNielsen(
    integer         dim,
    integer         npts,
    real_type const pnts[],
    integer         ld_pnts,
    real_type       t[]
  );

  void
  FangHung(
    integer         dim,
    integer         npts,
    real_type const pnts[],
    integer         ld_pnts,
    real_type       t[]
  );

  void
  searchInterval(
    integer         npts,
    real_type const X[],
    real_type     & x,
    integer       & lastInterval,
    bool            _curve_is_closed,
    bool            _curve_can_extend
  );

  /*\
   |   ____        _ _
   |  / ___| _ __ | (_)_ __   ___
   |  \___ \| '_ \| | | '_ \ / _ \
   |   ___) | |_) | | | | | |  __/
   |  |____/| .__/|_|_|_| |_|\___|
   |        |_|
  \*/
  //! Spline Management Class
  class Spline {
  protected:

    string _name;
    bool   _curve_is_closed;
    bool   _curve_can_extend;

    integer   npts, npts_reserved;
    real_type *X; // allocated in the derived class!
    real_type *Y; // allocated in the derived class!

    mutable std::mutex                   lastInterval_mutex;
    mutable map<std::thread::id,integer> lastInterval_by_thread;

    integer
    search( real_type & x ) const {
      integer lastInterval;
      {
        std::lock_guard<std::mutex> lck(lastInterval_mutex);
        lastInterval = lastInterval_by_thread[std::this_thread::get_id()];
      }
      searchInterval(
        this->npts,
        this->X,
        x,
        lastInterval,
        this->_curve_is_closed,
        this->_curve_can_extend
      );
      {
        std::lock_guard<std::mutex> lck(lastInterval_mutex);
        lastInterval_by_thread[std::this_thread::get_id()] = lastInterval;
      }
      return lastInterval;
    }

    void
    initLastInterval() {
      std::lock_guard<std::mutex> lck(lastInterval_mutex);
      lastInterval_by_thread[std::this_thread::get_id()] = 0;
    }

    Spline( Spline const & ) = delete;
    Spline const & operator = ( Spline const & ) = delete;

  public:

    //! spline constructor
    Spline( string const & name = "Spline" )
    : _name(name)
    , _curve_is_closed(false)
    , _curve_can_extend(true)
    , npts(0)
    , npts_reserved(0)
    , X(nullptr)
    , Y(nullptr)
    {
      this->initLastInterval();
    }
    //! spline destructor
    virtual
    ~Spline()
    {}

    string const & name() const { return _name; }

    bool is_closed() const { return this->_curve_is_closed; }
    void make_closed() { this->_curve_is_closed = true; }
    void make_opened() { this->_curve_is_closed = false; }

    bool is_bounded() const { return !this->_curve_can_extend; }
    void make_unbounded() { this->_curve_can_extend = true; }
    void make_bounded()   { this->_curve_can_extend = false; }

    //! return the number of support points of the spline.
    integer
    numPoints(void) const { return this->npts; }

    //! return the i-th node of the spline (x component).
    real_type
    xNode( integer i ) const { return this->X[size_t(i)]; }

    //! return the i-th node of the spline (y component).
    real_type
    yNode( integer i ) const { return this->Y[size_t(i)]; }

    //! return first node of the spline (x component).
    real_type
    xBegin() const { return this->X[0]; }

    //! return first node of the spline (y component).
    real_type
    yBegin() const { return this->Y[0]; }

    //! return last node of the spline (x component).
    real_type
    xEnd() const { return this->X[size_t(this->npts-1)]; }

    //! return last node of the spline (y component).
    real_type
    yEnd() const { return this->Y[size_t(this->npts-1)]; }

    //! Allocate memory for `npts` points
    virtual
    void
    reserve( integer npts ) SPLINES_PURE_VIRTUAL;

    //! Add a support point (x,y) to the spline.
    void pushBack( real_type x, real_type y );

    //! Drop a support point to the spline.
    void dropBack() { if ( npts > 0 ) --npts; }

    //! Build a spline.
    // must be defined in derived classes
    virtual
    void
    build(void) SPLINES_PURE_VIRTUAL;

    virtual
    void
    setup( GenericContainer const & gc );

    void
    build( GenericContainer const & gc )
    { setup(gc); }

    //! Build a spline.
    /*!
     | \param x    vector of x-coordinates
     | \param incx access elements as x[0], x[incx], x[2*incx],...
     | \param y    vector of y-coordinates
     | \param incy access elements as y[0], y[incy], x[2*incy],...
     | \param n    total number of points
    \*/
    // must be defined in derived classes
    virtual
    void
    build(
      real_type const x[], integer incx,
      real_type const y[], integer incy,
      integer n
    );

    //! Build a spline.
    /*!
     | \param x vector of x-coordinates
     | \param y vector of y-coordinates
     | \param n total number of points
    \*/
    inline
    void
    build( real_type const x[], real_type const y[], integer n )
    { this->build( x, 1, y, 1, n ); }

    //! Build a spline.
    /*!
     | \param x vector of x-coordinates
     | \param y vector of y-coordinates
    \*/
    inline
    void
    build( vector<real_type> const & x, vector<real_type> const & y ) {
      integer N = integer(x.size());
      if ( N > integer(y.size()) ) N = integer(y.size());
      this->build( &x.front(), 1, &y.front(), 1, N );
    }

    //! Cancel the support points, empty the spline.
    virtual
    void
    clear(void) SPLINES_PURE_VIRTUAL;

    //! return x-minumum spline value
    real_type xMin() const { return this->X[0]; }

    //! return x-maximum spline value
    real_type xMax() const { return this->X[npts-1]; }

    //! return y-minumum spline value
    real_type
    yMin() const {
      integer N = integer(npts);
      if ( type() == CONSTANT_TYPE ) --N;
      return *std::min_element(Y,Y+N);
    }

    //! return y-maximum spline value
    real_type
    yMax() const {
      integer N = npts;
      if ( type() == CONSTANT_TYPE ) --N;
      return *std::max_element(Y,Y+N);
    }

    ///////////////////////////////////////////////////////////////////////////
    //! change X-origin of the spline
    void setOrigin( real_type x0 );

    //! change X-range of the spline
    void setRange( real_type xmin, real_type xmax );

    ///////////////////////////////////////////////////////////////////////////
    //! dump a sample of the spline
    void
    dump(
      ostream_type & s,
      integer        nintervals,
      char const     header[] = "x\ty"
    ) const;

    void
    dump(
      char const fname[],
      integer    nintervals,
      char const header[] = "x\ty"
    ) const {
      ofstream file(fname);
      this->dump( file, nintervals, header );
      file.close();
    }

    ///////////////////////////////////////////////////////////////////////////
    //! Evaluate spline value
    virtual
    real_type
    operator () ( real_type x ) const SPLINES_PURE_VIRTUAL;

    //! First derivative
    virtual
    real_type
    D( real_type x ) const SPLINES_PURE_VIRTUAL;

    //! Second derivative
    virtual
    real_type
    DD( real_type x ) const SPLINES_PURE_VIRTUAL;

    //! Third derivative
    virtual
    real_type
    DDD( real_type x ) const SPLINES_PURE_VIRTUAL;

    //! 4th derivative
    virtual
    real_type
    DDDD( real_type ) const
    { return real_type(0); }

    //! 4th derivative
    virtual
    real_type
    DDDDD( real_type ) const
    { return real_type(0); }

    //! Some aliases
    real_type eval( real_type x ) const { return (*this)(x); }
    real_type eval_D( real_type x ) const { return this->D(x); }
    real_type eval_DD( real_type x ) const { return this->DD(x); }
    real_type eval_DDD( real_type x ) const { return this->DDD(x); }
    real_type eval_DDDD( real_type x ) const { return this->DDDD(x); }
    real_type eval_DDDDD( real_type x ) const { return this->DDDDD(x); }

    //! get the piecewise polinomials of the spline
    virtual
    integer // order
    coeffs(
      real_type cfs[],
      real_type nodes[],
      bool      transpose = false
    ) const SPLINES_PURE_VIRTUAL;

    virtual
    integer // order
    order() const SPLINES_PURE_VIRTUAL;

    //! Print spline coefficients
    virtual
    void
    writeToStream( ostream_type & s ) const SPLINES_PURE_VIRTUAL;

    //! Return spline typename
    char const *
    type_name() const
    { return Splines::spline_type_1D[type()]; }

    //! Return spline type (as number)
    virtual
    unsigned
    type() const SPLINES_PURE_VIRTUAL;

    void
    info( ostream_type & s ) const;

    friend class SplineSet;

  };

  //! compute curvature of a planar curve
  real_type
  curvature( real_type s, Spline const & X, Spline const & Y );

  //! compute curvature derivative of a planar curve
  real_type
  curvature_D( real_type s, Spline const & X, Spline const & Y );

  //! compute curvature second derivative of a planar curve
  real_type
  curvature_DD( real_type s, Spline const & X, Spline const & Y );

  /*\
   |    ____      _     _        ____        _ _              ____
   |   / ___|   _| |__ (_) ___  / ___| _ __ | (_)_ __   ___  | __ )  __ _ ___  ___
   |  | |  | | | | '_ \| |/ __| \___ \| '_ \| | | '_ \ / _ \ |  _ \ / _` / __|/ _ \
   |  | |__| |_| | |_) | | (__   ___) | |_) | | | | | |  __/ | |_) | (_| \__ \  __/
   |   \____\__,_|_.__/|_|\___| |____/| .__/|_|_|_| |_|\___| |____/ \__,_|___/\___|
   |                                  |_|
  \*/
  //! cubic spline base class
  class CubicSplineBase : public Spline {
  protected:
    SplineMalloc<real_type> baseValue;

    real_type * Yp;
    bool        _external_alloc;

  public:

    using Spline::build;

    //! spline constructor
    CubicSplineBase( string const & name = "CubicSplineBase")
    : Spline(name)
    , baseValue(name+"_memory")
    , Yp(nullptr)
    , _external_alloc(false)
    {}

    virtual
    ~CubicSplineBase() SPLINES_OVERRIDE
    {}

    void
    copySpline( CubicSplineBase const & S );

    //! return the i-th node of the spline (y' component).
    real_type
    ypNode( integer i ) const
    { return this->Yp[size_t(i)]; }

    //! change X-range of the spline
    void
    setRange( real_type xmin, real_type xmax );

    //! Use externally allocated memory for `npts` points
    void
    reserve_external(
      integer       n,
      real_type * & p_x,
      real_type * & p_y,
      real_type * & p_dy
    );

    // --------------------------- VIRTUALS -----------------------------------
    //! Evaluate spline value
    virtual
    real_type
    operator () ( real_type x ) const SPLINES_OVERRIDE;

    //! First derivative
    virtual
    real_type
    D( real_type x ) const SPLINES_OVERRIDE;

    //! Second derivative
    virtual
    real_type
    DD( real_type x ) const SPLINES_OVERRIDE;

    //! Third derivative
    virtual
    real_type
    DDD( real_type x ) const SPLINES_OVERRIDE;

    //! Print spline coefficients
    virtual
    void
    writeToStream( ostream_type & s ) const SPLINES_OVERRIDE;

    // --------------------------- VIRTUALS -----------------------------------

    //! Allocate memory for `npts` points
    virtual
    void
    reserve( integer npts ) SPLINES_OVERRIDE;

    //! Build a spline.
    /*!
     | \param x     vector of x-coordinates
     | \param incx  access elements as `x[0]`, `x[incx]`, `x[2*incx]`,...
     | \param y     vector of y-coordinates
     | \param incy  access elements as `y[0]`, `y[incy]`, `x[2*incy]`,...
     | \param yp    vector of y'-coordinates
     | \param incyp access elements as `yp[0]`, `yp[incy]`, `xp[2*incy]`,...
     | \param n     total number of points
    \*/
    void
    build(
      real_type const x[],  integer incx,
      real_type const y[],  integer incy,
      real_type const yp[], integer incyp,
      integer n
    );

    //! Build a spline.
    /*!
     | \param x  vector of x-coordinates
     | \param y  vector of y-coordinates
     | \param yp vector of y'-coordinates
     | \param n  total number of points
    \*/
    inline
    void
    build(
      real_type const x[],
      real_type const y[],
      real_type const yp[],
      integer n
    ) {
      this->build( x, 1, y, 1, yp, 1, n );
    }

    //! Build a spline.
    /*!
     | \param x  vector of x-coordinates
     | \param y  vector of y-coordinates
     | \param yp vector of y'-coordinates
    \*/
    inline
    void
    build(
      vector<real_type> const & x,
      vector<real_type> const & y,
      vector<real_type> const & yp
    ) {
      integer N = integer(x.size());
      if ( N > integer(y.size())  ) N = integer(y.size());
      if ( N > integer(yp.size()) ) N = integer(yp.size());
      this->build (
        &x.front(),  1,
        &y.front(),  1,
        &yp.front(), 1,
        N
      );
    }

    //! Cancel the support points, empty the spline.
    virtual
    void
    clear(void) SPLINES_OVERRIDE;

    //! get the piecewise polinomials of the spline
    virtual
    integer // order
    coeffs(
      real_type cfs[],
      real_type nodes[],
      bool      transpose = false
    ) const SPLINES_OVERRIDE;

    virtual
    integer // order
    order() const SPLINES_OVERRIDE;

  };

  /*\
   |    ____      _     _      ____        _ _
   |   / ___|   _| |__ (_) ___/ ___| _ __ | (_)_ __   ___
   |  | |  | | | | '_ \| |/ __\___ \| '_ \| | | '_ \ / _ \
   |  | |__| |_| | |_) | | (__ ___) | |_) | | | | | |  __/
   |   \____\__,_|_.__/|_|\___|____/| .__/|_|_|_| |_|\___|
   |                                |_|
  \*/

  typedef enum {
    EXTRAPOLATE_BC = 0,
    NATURAL_BC,
    PARABOLIC_RUNOUT_BC,
    NOT_A_KNOT
  } CUBIC_SPLINE_TYPE_BC;

  void
  CubicSpline_build(
    real_type const      X[],
    real_type const      Y[],
    real_type            Yp[],
    integer              npts,
    CUBIC_SPLINE_TYPE_BC bc0,
    CUBIC_SPLINE_TYPE_BC bcn
  );

  void
  CubicSpline_build(
    real_type const      X[],
    real_type const      Y[],
    real_type            Yp[],
    real_type            Ypp[],
    real_type            L[],
    real_type            D[],
    real_type            U[],
    integer              npts,
    CUBIC_SPLINE_TYPE_BC bc0,
    CUBIC_SPLINE_TYPE_BC bcn
  );

  //! Cubic Spline Management Class
  class CubicSpline : public CubicSplineBase {
  private:
    CUBIC_SPLINE_TYPE_BC bc0, bcn;
  public:

    using CubicSplineBase::build;
    using CubicSplineBase::reserve;

    //! spline constructor
    CubicSpline( string const & name = "CubicSpline" )
    : CubicSplineBase( name )
    , bc0( EXTRAPOLATE_BC )
    , bcn( EXTRAPOLATE_BC )
    {}

    //! spline destructor
    virtual
    ~CubicSpline() SPLINES_OVERRIDE
    {}

    /*!
     | \param _bc0  initial boundary condition.
    \*/
    void
    setInitialBC( CUBIC_SPLINE_TYPE_BC _bc0 )
    { this->bc0 = _bc0; }

    /*!
     | \param _bcn final boundary condition.
    \*/
    void
    setFinalBC( CUBIC_SPLINE_TYPE_BC _bcn )
    { this->bcn = _bcn; }

    //! Return spline type (as number)
    virtual
    unsigned
    type() const SPLINES_OVERRIDE
    { return CUBIC_TYPE; }

    // --------------------------- VIRTUALS -----------------------------------

    virtual
    void
    build(void) SPLINES_OVERRIDE;

    virtual
    void
    setup( GenericContainer const & gc ) SPLINES_OVERRIDE;

  };

  /*\
   |      _    _    _                   ____        _ _
   |     / \  | | _(_)_ __ ___   __ _  / ___| _ __ | (_)_ __   ___
   |    / _ \ | |/ / | '_ ` _ \ / _` | \___ \| '_ \| | | '_ \ / _ \
   |   / ___ \|   <| | | | | | | (_| |  ___) | |_) | | | | | |  __/
   |  /_/   \_\_|\_\_|_| |_| |_|\__,_| |____/| .__/|_|_|_| |_|\___|
   |                                         |_|
  \*/

  void
  Akima_build(
    real_type const X[],
    real_type const Y[],
    real_type       Yp[],
    integer         npts
  );

  //! Akima spline class
  /*!
   |  Reference
   |  =========
   |  Hiroshi Akima, Journal of the ACM, Vol. 17, No. 4, October 1970, pages 589-602.
  \*/
  class AkimaSpline : public CubicSplineBase {
  public:

    using CubicSplineBase::build;
    using CubicSplineBase::reserve;

    //! spline constructor
    AkimaSpline( string const & name = "AkimaSpline" )
    : CubicSplineBase( name )
    {}

    //! spline destructor
    virtual
    ~AkimaSpline() SPLINES_OVERRIDE
    {}

    //! Return spline type (as number)
    virtual
    unsigned
    type() const SPLINES_OVERRIDE
    { return AKIMA_TYPE; }

    // --------------------------- VIRTUALS -----------------------------------

    //! Build an Akima spline from previously inserted points
    virtual
    void
    build(void) SPLINES_OVERRIDE;

    virtual
    void
    setup( GenericContainer const & gc ) SPLINES_OVERRIDE;

  };

  /*
   |   ____                     _ ____        _ _
   |  | __ )  ___  ___ ___  ___| / ___| _ __ | (_)_ __   ___
   |  |  _ \ / _ \/ __/ __|/ _ \ \___ \| '_ \| | | '_ \ / _ \
   |  | |_) |  __/\__ \__ \  __/ |___) | |_) | | | | | |  __/
   |  |____/ \___||___/___/\___|_|____/| .__/|_|_|_| |_|\___|
   |                                   |_|
  \*/

  void
  Bessel_build(
    real_type const X[],
    real_type const Y[],
    real_type       Yp[],
    integer         npts
  );

  //! Bessel spline class
  class BesselSpline : public CubicSplineBase {
  public:

    using CubicSplineBase::build;
    using CubicSplineBase::reserve;

    //! spline constructor
    BesselSpline( string const & name = "BesselSpline" )
    : CubicSplineBase( name )
    {}

    //! spline destructor
    virtual
    ~BesselSpline() SPLINES_OVERRIDE
    {}

    //! Return spline type (as number)
    virtual
    unsigned
    type() const SPLINES_OVERRIDE
    { return BESSEL_TYPE; }

    // --------------------------- VIRTUALS -----------------------------------

    //! Build a Bessel spline from previously inserted points
    virtual
    void
    build (void) SPLINES_OVERRIDE;

    virtual
    void
    setup( GenericContainer const & gc ) SPLINES_OVERRIDE;
  };

  /*\
   |   ____      _     _      ____        _ _
   |  |  _ \ ___| |__ (_)_ __/ ___| _ __ | (_)_ __   ___
   |  | |_) / __| '_ \| | '_ \___ \| '_ \| | | '_ \ / _ \
   |  |  __/ (__| | | | | |_) |__) | |_) | | | | | |  __/
   |  |_|   \___|_| |_|_| .__/____/| .__/|_|_|_| |_|\___|
   |                    |_|        |_|
  \*/
  void
  Pchip_build(
    real_type const X[],
    real_type const Y[],
    real_type       Yp[],
    integer         npts
  );

  //! Pchip (Piecewise Cubic Hermite Interpolating Polynomial) spline class
  class PchipSpline : public CubicSplineBase {
  public:

    using CubicSplineBase::build;
    using CubicSplineBase::reserve;

    //! spline constructor
    PchipSpline( string const & name = "PchipSpline" )
    : CubicSplineBase( name )
    {}

    //! spline destructor
    virtual
    ~PchipSpline() SPLINES_OVERRIDE
    {}

    //! Return spline type (as number)
    virtual
    unsigned
    type() const SPLINES_OVERRIDE
    { return PCHIP_TYPE; }

    // --------------------------- VIRTUALS -----------------------------------

    //! Build a Monotone spline from previously inserted points
    virtual
    void
    build(void) SPLINES_OVERRIDE;

    virtual
    void
    setup( GenericContainer const & gc ) SPLINES_OVERRIDE;

  };

  /*\
   |   _     _                       ____        _ _
   |  | |   (_)_ __   ___  __ _ _ __/ ___| _ __ | (_)_ __   ___
   |  | |   | | '_ \ / _ \/ _` | '__\___ \| '_ \| | | '_ \ / _ \
   |  | |___| | | | |  __/ (_| | |   ___) | |_) | | | | | |  __/
   |  |_____|_|_| |_|\___|\__,_|_|  |____/| .__/|_|_|_| |_|\___|
   |                                      |_|
  \*/
  //! Linear spline class
  class LinearSpline : public Spline {
    SplineMalloc<real_type> baseValue;
    bool                    _external_alloc;
  public:

    using Spline::build;

    LinearSpline( string const & name = "LinearSpline" )
    : Spline(name)
    , baseValue( name+"_memory")
    , _external_alloc(false)
    {}

    virtual
    ~LinearSpline() SPLINES_OVERRIDE
    {}

    //! Use externally allocated memory for `npts` points
    void
    reserve_external(
      integer      n,
      real_type *& p_x,
      real_type *& p_y
    );

    // --------------------------- VIRTUALS -----------------------------------

    //! Evalute spline value at `x`
    virtual
    real_type
    operator () ( real_type x ) const SPLINES_OVERRIDE {
      SPLINE_ASSERT(
        this->npts > 0, "in LinearSpline::operator(), npts == 0!"
      )
      if ( x < this->X[0]      ) return this->Y[0];
      if ( x > this->X[npts-1] ) return this->Y[this->npts-1];
      integer   i = this->search(x);
      real_type s = (x-this->X[i])/(this->X[i+1] - this->X[i]);
      return (1-s)*this->Y[i] + s * this->Y[i+1];
    }

    //! First derivative
    virtual
    real_type
    D( real_type x ) const SPLINES_OVERRIDE {
      SPLINE_ASSERT(
        this->npts > 0, "in LinearSpline::operator(), npts == 0!"
      )
      if ( x < this->X[0]      ) return 0;
      if ( x > this->X[npts-1] ) return 0;
      integer i = this->search(x);
      return ( this->Y[i+1] - this->Y[i] ) / ( this->X[i+1] - this->X[i] );
    }

    //! Second derivative
    virtual
    real_type
    DD( real_type ) const SPLINES_OVERRIDE
    { return 0; }

    //! Third derivative
    virtual
    real_type
    DDD( real_type ) const SPLINES_OVERRIDE
    { return 0; }

    //! Print spline coefficients
    virtual
    void
    writeToStream( ostream_type & s ) const SPLINES_OVERRIDE;

    //! Return spline type (as number)
    virtual
    unsigned
    type() const SPLINES_OVERRIDE
    { return LINEAR_TYPE; }

    // --------------------------- VIRTUALS -----------------------------------

    //! Allocate memory for `npts` points
    virtual
    void
    reserve( integer npts ) SPLINES_OVERRIDE;

    //! added for compatibility with cubic splines
    virtual
    void
    build(void) SPLINES_OVERRIDE
    {}

    //! Cancel the support points, empty the spline.
    virtual
    void
    clear(void) SPLINES_OVERRIDE;

    //! get the piecewise polinomials of the spline
    virtual
    integer // order
    coeffs(
      real_type cfs[],
      real_type nodes[],
      bool      transpose = false
    ) const SPLINES_OVERRIDE;

    virtual
    integer // order
    order() const SPLINES_OVERRIDE;

    virtual
    void
    setup( GenericContainer const & gc ) SPLINES_OVERRIDE;

  };

  /*\
   |    ____                _              _       ____        _ _
   |   / ___|___  _ __  ___| |_ __ _ _ __ | |_ ___/ ___| _ __ | (_)_ __   ___
   |  | |   / _ \| '_ \/ __| __/ _` | '_ \| __/ __\___ \| '_ \| | | '_ \ / _ \
   |  | |__| (_) | | | \__ \ || (_| | | | | |_\__ \___) | |_) | | | | | |  __/
   |   \____\___/|_| |_|___/\__\__,_|_| |_|\__|___/____/| .__/|_|_|_| |_|\___|
   |                                                    |_|
  \*/
  //! Picewise constants spline class
  class ConstantSpline : public Spline {
    SplineMalloc<real_type> baseValue;
    bool                    _external_alloc;
  public:

    using Spline::build;

    ConstantSpline( string const & name = "ConstantSpline" )
    : Spline(name)
    , baseValue(name+"_memory")
    , _external_alloc(false)
    {}

    ~ConstantSpline() SPLINES_OVERRIDE
    {}

    //! Use externally allocated memory for `npts` points
    void
    reserve_external(
      integer       n,
      real_type * & p_x,
      real_type * & p_y
    );

    // --------------------------- VIRTUALS -----------------------------------
    //! Build a spline.
    virtual
    void
    build(void) SPLINES_OVERRIDE
    {} // nothing to do

    virtual
    void
    build(
      real_type const x[], integer incx,
      real_type const y[], integer incy,
      integer n
    ) SPLINES_OVERRIDE;

    //! Evaluate spline value at `x`
    virtual
    real_type
    operator () ( real_type x ) const SPLINES_OVERRIDE;

    //! First derivative
    virtual
    real_type
    D( real_type ) const SPLINES_OVERRIDE
    { return 0; }

    //! Second derivative
    virtual
    real_type
    DD( real_type ) const SPLINES_OVERRIDE
    { return 0; }

    //! Third derivative
    virtual
    real_type
    DDD( real_type ) const SPLINES_OVERRIDE
    { return 0; }

    //! Print spline coefficients
    virtual
    void
    writeToStream( ostream_type & ) const SPLINES_OVERRIDE;

    //! Return spline type (as number)
    virtual
    unsigned
    type() const SPLINES_OVERRIDE
    { return CONSTANT_TYPE; }

    // --------------------------- VIRTUALS -----------------------------------

    //! Allocate memory for `npts` points
    virtual
    void
    reserve( integer npts ) SPLINES_OVERRIDE;

    //! Cancel the support points, empty the spline.
    virtual
    void
    clear(void) SPLINES_OVERRIDE;

    //! get the piecewise polinomials of the spline
    virtual
    integer // order
    coeffs(
      real_type cfs[],
      real_type nodes[],
      bool      transpose = false
    ) const SPLINES_OVERRIDE;

    virtual
    integer // order
    order() const SPLINES_OVERRIDE;

    virtual
    void
    setup( GenericContainer const & gc ) SPLINES_OVERRIDE;

  };

  /*\
   |    _   _                     _ _       ____        _ _
   |   | | | | ___ _ __ _ __ ___ (_) |_ ___/ ___| _ __ | (_)_ __   ___
   |   | |_| |/ _ \ '__| '_ ` _ \| | __/ _ \___ \| '_ \| | | '_ \ / _ \
   |   |  _  |  __/ |  | | | | | | | ||  __/___) | |_) | | | | | |  __/
   |   |_| |_|\___|_|  |_| |_| |_|_|\__\___|____/| .__/|_|_|_| |_|\___|
   |                                             |_|
  \*/
  //! Hermite Spline Management Class
  class HermiteSpline : public CubicSplineBase {
  public:

    using CubicSplineBase::build;
    using CubicSplineBase::reserve;

    //! spline constructor
    HermiteSpline( string const & name = "HermiteSpline" )
    : CubicSplineBase( name )
    {}

    //! spline destructor
    virtual
    ~HermiteSpline() SPLINES_OVERRIDE
    {}

    //! Return spline type (as number)
    virtual
    unsigned
    type() const SPLINES_OVERRIDE
    { return HERMITE_TYPE; }

    // --------------------------- VIRTUALS -----------------------------------

    virtual
    void
    build(void) SPLINES_OVERRIDE
    {} // nothing to do

    // block method!
    virtual
    void
    build(
      real_type const [], integer,
      real_type const [], integer,
      integer
    ) SPLINES_OVERRIDE;

    virtual
    void
    setup( GenericContainer const & gc ) SPLINES_OVERRIDE;

  };

  /*\
   |    ___        _       _   _      ____        _ _            ____
   |   / _ \ _   _(_)_ __ | |_(_) ___/ ___| _ __ | (_)_ __   ___| __ )  __ _ ___  ___
   |  | | | | | | | | '_ \| __| |/ __\___ \| '_ \| | | '_ \ / _ \  _ \ / _` / __|/ _ \
   |  | |_| | |_| | | | | | |_| | (__ ___) | |_) | | | | | |  __/ |_) | (_| \__ \  __/
   |   \__\_\\__,_|_|_| |_|\__|_|\___|____/| .__/|_|_|_| |_|\___|____/ \__,_|___/\___|
   |                                       |_|
   |
  \*/
  //! cubic quintic base class
  class QuinticSplineBase : public Spline {
  protected:
    SplineMalloc<real_type> baseValue;

    real_type * Yp;
    real_type * Ypp;
    bool        _external_alloc;

  public:

    using Spline::build;

    //! spline constructor
    QuinticSplineBase( string const & name = "Spline" )
    : Spline(name)
    , baseValue(name+"_memeory")
    , Yp(nullptr)
    , Ypp(nullptr)
    , _external_alloc(false)
    {}

    virtual
    ~QuinticSplineBase() SPLINES_OVERRIDE
    {}

    void
    copySpline( QuinticSplineBase const & S );

    //! return the i-th node of the spline (y' component).
    real_type
    ypNode( integer i ) const
    { return this->Yp[size_t(i)]; }

    //! return the i-th node of the spline (y'' component).
    real_type
    yppNode( integer i ) const
    { return this->Ypp[size_t(i)]; }

    //! change X-range of the spline
    void
    setRange( real_type xmin, real_type xmax );

    //! Use externally allocated memory for `npts` points
    void
    reserve_external(
      integer       n,
      real_type * & p_x,
      real_type * & p_y,
      real_type * & p_Yp,
      real_type * & p_Ypp
    );

    // --------------------------- VIRTUALS -----------------------------------

    //! Evaluate spline value
    virtual
    real_type
    operator () ( real_type x ) const SPLINES_OVERRIDE;

    //! First derivative
    virtual
    real_type
    D( real_type x ) const SPLINES_OVERRIDE;

    //! Second derivative
    virtual
    real_type
    DD( real_type x ) const SPLINES_OVERRIDE;

    //! Third derivative
    virtual
    real_type
    DDD( real_type x ) const SPLINES_OVERRIDE;

    //! Fourth derivative
    real_type
    DDDD( real_type x ) const SPLINES_OVERRIDE;

    //! Fifth derivative
    real_type
    DDDDD( real_type x ) const SPLINES_OVERRIDE;

    //! Print spline coefficients
    virtual
    void
    writeToStream( ostream_type & s ) const SPLINES_OVERRIDE;

    //! Return spline type (as number)
    virtual
    unsigned
    type() const SPLINES_OVERRIDE
    { return QUINTIC_TYPE; }

    //! Allocate memory for `npts` points
    virtual
    void
    reserve( integer npts ) SPLINES_OVERRIDE;

    //! Cancel the support points, empty the spline.
    virtual
    void
    clear(void) SPLINES_OVERRIDE;

    //! get the piecewise polinomials of the spline
    virtual
    integer // order
    coeffs(
      real_type cfs[],
      real_type nodes[],
      bool      transpose = false
    ) const SPLINES_OVERRIDE;

    virtual
    integer // order
    order() const SPLINES_OVERRIDE;

  };

  /*\
   |    ___        _       _   _      ____        _ _
   |   / _ \ _   _(_)_ __ | |_(_) ___/ ___| _ __ | (_)_ __   ___
   |  | | | | | | | | '_ \| __| |/ __\___ \| '_ \| | | '_ \ / _ \
   |  | |_| | |_| | | | | | |_| | (__ ___) | |_) | | | | | |  __/
   |   \__\_\\__,_|_|_| |_|\__|_|\___|____/| .__/|_|_|_| |_|\___|
   |                                       |_|
   |
  \*/

  typedef enum {
    CUBIC_QUINTIC = 0,
    PCHIP_QUINTIC,
    AKIMA_QUINTIC,
    BESSEL_QUINTIC
  } QUINTIC_SPLINE_TYPE;

  //! Quintic spline class
  class QuinticSpline : public QuinticSplineBase {
    QUINTIC_SPLINE_TYPE q_sub_type;
  public:

    using Spline::build;
    using QuinticSplineBase::reserve;

    //! spline constructor
    QuinticSpline( string const & name = "Spline" )
    : QuinticSplineBase( name )
    , q_sub_type(CUBIC_QUINTIC)
    {}

    //! spline destructor
    virtual
    ~QuinticSpline() SPLINES_OVERRIDE
    {}

    void
    setQuinticType( QUINTIC_SPLINE_TYPE qt )
    { this->q_sub_type = qt; }

    // --------------------------- VIRTUALS -----------------------------------
    //! Build a Monotone quintic spline from previously inserted points
    virtual
    void
    build(void) SPLINES_OVERRIDE;

    virtual
    void
    setup( GenericContainer const & gc ) SPLINES_OVERRIDE;

  };


  /*\
   |   ____        _ _            _ ____
   |  / ___| _ __ | (_)_ __   ___/ |  _ \
   |  \___ \| '_ \| | | '_ \ / _ \ | | | |
   |   ___) | |_) | | | | | |  __/ | |_| |
   |  |____/| .__/|_|_|_| |_|\___|_|____/
   |        |_|
  \*/
  //! Spline Management Class
  class Spline1D {
  protected:

    std::string _name;

    Spline * pSpline;

    Spline1D( Spline1D const & ) = delete;
    Spline1D const & operator = ( Spline1D const & ) = delete;

  public:

    //! spline constructor
    Spline1D( std::string const & n )
    : _name(n)
    , pSpline(nullptr)
    {}

    //! spline destructor
    ~Spline1D()
    {}

    string const & name() const { return pSpline->name(); }

    bool is_closed() const { return pSpline->is_closed(); }
    void make_closed() { pSpline->make_closed(); }
    void make_opened() { pSpline->make_opened(); }

    bool is_bounded() const { return pSpline->is_bounded(); }
    void make_unbounded() { pSpline->make_unbounded(); }
    void make_bounded()   { pSpline->make_bounded(); }

    //! return the number of support points of the spline.
    integer numPoints(void) const { return pSpline->numPoints(); }

    //! return the i-th node of the spline (x component).
    real_type xNode( integer i ) const { return pSpline->xNode(i); }

    //! return the i-th node of the spline (y component).
    real_type yNode( integer i ) const { return pSpline->yNode(i); }

    //! return first node of the spline (x component).
    real_type xBegin() const { return pSpline->xBegin(); }

    //! return first node of the spline (y component).
    real_type yBegin() const { return pSpline->yBegin(); }

    //! return last node of the spline (x component).
    real_type xEnd() const { return pSpline->xEnd(); }

    //! return last node of the spline (y component).
    real_type yEnd() const { return pSpline->yEnd(); }

    //! Allocate memory for `npts` points
    void reserve( integer npts ) { return pSpline->reserve( npts ); }

    //! Add a support point (x,y) to the spline.
    void pushBack( real_type x, real_type y ) { return pSpline->pushBack( x, y ); }

    //! Drop a support point to the spline.
    void dropBack() { pSpline->dropBack(); }

    //! Build a spline.
    // must be defined in derived classes
    void build(void) { pSpline->build(); }

    void setup( GenericContainer const & gc );
    void build( GenericContainer const & gc ) { setup(gc); }

    //! Build a spline.
    /*!
     | \param x    vector of x-coordinates
     | \param incx access elements as x[0], x[incx], x[2*incx],...
     | \param y    vector of y-coordinates
     | \param incy access elements as y[0], y[incy], x[2*incy],...
     | \param n    total number of points
    \*/
    // must be defined in derived classes
    void
    build(
      SplineType1D tp,
      real_type const x[], integer incx,
      real_type const y[], integer incy,
      integer n
    );

    //! Build a spline.
    /*!
     | \param x vector of x-coordinates
     | \param y vector of y-coordinates
     | \param n total number of points
    \*/
    void
    build(
      SplineType1D    tp,
      real_type const x[],
      real_type const y[],
      integer         n
    ) {
      this->build( tp, x, 1, y, 1, n );
    }

    //! Build a spline.
    /*!
     | \param x vector of x-coordinates
     | \param y vector of y-coordinates
    \*/
    void
    build(
      SplineType1D              tp,
      vector<real_type> const & x,
      vector<real_type> const & y
    ) {
      integer n = integer(x.size());
      this->build( tp, &x.front(), &y.front(), n );
    }

    //! Cancel the support points, empty the spline.
    void
    clear(void) { pSpline->clear(); }

    //! return x-minumum spline value
    real_type xMin() const { return pSpline->xMin(); }

    //! return x-maximum spline value
    real_type xMax() const { return pSpline->xMax(); }

    //! return y-minumum spline value
    real_type yMin() const { return pSpline->yMin(); }

    //! return y-maximum spline value
    real_type yMax() const { return pSpline->yMax(); }

    ///////////////////////////////////////////////////////////////////////////
    //! change X-origin of the spline
    void
    setOrigin( real_type x0 )
    { return pSpline->setOrigin( x0 ); }

    //! change X-range of the spline
    void
    setRange( real_type xmin, real_type xmax )
    { return pSpline->setRange( xmin, xmax ); }

    ///////////////////////////////////////////////////////////////////////////
    //! dump a sample of the spline
    void
    dump(
      ostream_type & s,
      integer        nintervals,
      char const     header[] = "x\ty"
    ) const {
      pSpline->dump( s, nintervals, header );
    }

    void
    dump(
      char const fname[],
      integer    nintervals,
      char const header[] = "x\ty"
    ) const {
      pSpline->dump( fname, nintervals, header );
    }

    ///////////////////////////////////////////////////////////////////////////
    //! Evaluate spline value
    real_type
    operator () ( real_type x ) const { return (*pSpline)(x); }

    //! First derivative
    real_type
    D( real_type x ) const { return pSpline->D(x); }

    //! Second derivative
    real_type
    DD( real_type x ) const { return pSpline->DD(x); }

    //! Third derivative
    real_type
    DDD( real_type x ) const { return pSpline->DDD(x); }

    //! 4th derivative
    real_type
    DDDD( real_type x ) const { return pSpline->DDDD(x); }

    //! 5th derivative
    real_type
    DDDDD( real_type x ) const { return pSpline->DDDDD(x); }

    //! Some aliases
    real_type eval( real_type x ) const { return (*pSpline)(x); }
    real_type eval_D( real_type x ) const { return pSpline->D(x); }
    real_type eval_DD( real_type x ) const { return pSpline->DD(x); }
    real_type eval_DDD( real_type x ) const { return pSpline->DDD(x); }
    real_type eval_DDDD( real_type x ) const { return pSpline->DDDD(x); }
    real_type eval_DDDDD( real_type x ) const { return pSpline->DDDDD(x); }

    //! get the piecewise polinomials of the spline
    integer // order
    coeffs(
      real_type cfs[],
      real_type nodes[],
      bool      transpose = false
    ) const {
      return pSpline->coeffs( cfs, nodes, transpose );
    }

    integer order() const { return pSpline->order(); }

    //! Print spline coefficients
    void
    writeToStream( ostream_type & s ) const
    { return pSpline->writeToStream( s ); }

    //! Return spline typename
    char const *
    type_name() const
    { return pSpline->type_name(); }

    //! Return spline type (as number)
    unsigned
    type() const
    { return pSpline->type(); }

    void
    info( ostream_type & s ) const
    { pSpline->info( s ); }
  };


  /*\
   |   ____        _ _          __     __
   |  / ___| _ __ | (_)_ __   __\ \   / /__  ___
   |  \___ \| '_ \| | | '_ \ / _ \ \ / / _ \/ __|
   |   ___) | |_) | | | | | |  __/\ V /  __/ (__
   |  |____/| .__/|_|_|_| |_|\___| \_/ \___|\___|
   |        |_|
  \*/

  //! Splines Management Class
  class SplineVec {

    SplineVec( SplineVec const & ) = delete;
    SplineVec const & operator = ( SplineVec const & ) = delete;

  protected:

    string const _name;

    SplineMalloc<real_type>  baseValue;
    SplineMalloc<real_type*> basePointer;

    integer _dim;
    integer _npts;
    bool    _curve_is_closed;
    bool    _curve_can_extend;

    real_type *  _X;
    real_type ** _Y;
    real_type ** _Yp;

    mutable std::mutex                   lastInterval_mutex;
    mutable map<std::thread::id,integer> lastInterval_by_thread;

    integer
    search( real_type & x ) const {
      integer lastInterval;
      {
        std::lock_guard<std::mutex> lck(lastInterval_mutex);
        lastInterval = lastInterval_by_thread[std::this_thread::get_id()];
      }
      searchInterval(
        this->_npts,
        this->_X,
        x,
        lastInterval,
        this->_curve_is_closed,
        this->_curve_can_extend
      );
      {
        std::lock_guard<std::mutex> lck(lastInterval_mutex);
        lastInterval_by_thread[std::this_thread::get_id()] = lastInterval;
      }
      return lastInterval;
    }

    ///////////////////////////////////////////////////////////////////////////
    void
    allocate( integer dim, integer npts );

    void
    computeChords();

  public:

    //! spline constructor
    SplineVec( string const & name = "SplineVec" );

    //! spline destructor
    virtual
    ~SplineVec();

    bool is_closed() const { return this->_curve_is_closed; }
    void make_closed() { this->_curve_is_closed = true; }
    void make_open()   { this->_curve_is_closed = false; }

    bool can_extend() const { return this->_curve_can_extend; }
    void make_unbounded() { this->_curve_can_extend = true; }
    void make_buonded()   { this->_curve_can_extend = false; }

    string const &
    name() const
    { return this->_name; }

    //! return the number of support points of the splines
    integer
    numPoints(void) const
    { return this->_npts; }

    //! return the number splines in the spline set
    integer
    dimension(void) const
    { return this->_dim; }

    //! return the vector of values of x-nodes
    real_type const *
    xNodes() const
    { return this->_X; }

    //! return the npt-th node of the spline (x component).
    real_type
    xNode( integer npt ) const
    { return this->_X[size_t(npt)]; }

    //! return the npt-th node of the spline (y component).
    real_type
    yNode( integer npt, integer j ) const
    { return this->_Y[size_t(j)][size_t(npt)]; }

    //! return x-minumum spline value
    real_type
    xMin() const
    { return this->_X[0]; }

    //! return x-maximum spline value
    real_type
    xMax() const
    { return this->_X[size_t(this->_npts-1)]; }

    //! Evaluate spline value
    real_type
    operator () ( real_type x, integer i ) const;

    real_type
    eval( real_type x, integer i ) const
    { return operator() (x,i); }

    //! First derivative
    real_type
    D( real_type x, integer i ) const;

    real_type
    eval_D( real_type x, integer i ) const
    { return this->D(x,i); }

    //! Second derivative
    real_type
    DD( real_type x, integer i ) const;

    real_type
    eval_DD( real_type x, integer i ) const
    { return this->DD(x,i); }

    //! Third derivative
    real_type
    DDD( real_type x, integer i ) const;

    real_type
    eval_DDD( real_type x, integer i ) const
    { return this->DDD(x,i); }

    //! 4th derivative
    real_type
    DDDD( real_type x, integer i ) const;

    real_type
    eval_DDDD( real_type x, integer i ) const
    { return this->DDDD(x,i); }

    //! 5th derivative
    real_type
    DDDDD( real_type x, integer i ) const;

    real_type
    eval_DDDDD( real_type x, integer i ) const
    { return this->DDDDD(x,i); }

    //! Evaluate all the splines at `x`
    void
    eval(
      real_type x,
      real_type vals[],
      integer   inc
    ) const;

    //! Evaluate the fist derivative of all the splines at `x`
    void
    eval_D(
      real_type x,
      real_type vals[],
      integer   inc
    ) const;

    //! Evaluate the second derivative of all the splines at `x`
    void
    eval_DD(
      real_type x,
      real_type vals[],
      integer   inc
    ) const;

    //! Evaluate the third derivative of all the splines at `x`
    void
    eval_DDD(
      real_type x,
      real_type vals[],
      integer   inc
    ) const;

    //! Evaluate the 4th derivative of all the splines at `x`
    void
    eval_DDDD(
      real_type x,
      real_type vals[],
      integer   inc
    ) const;

    //! Evaluate the 5th derivative of all the splines at `x`
    void
    eval_DDDDD(
      real_type x,
      real_type vals[],
      integer   inc
    ) const;

    //! Evaluate all the splines at `x`
    void
    eval( real_type x, vector<real_type> & vals ) const;

    //! Evaluate the fist derivative of all the splines at `x`
    void
    eval_D( real_type x, vector<real_type> & vals ) const;

    //! Evaluate the second derivative of all the splines at `x`
    void
    eval_DD( real_type x, vector<real_type> & vals ) const;

    //! Evaluate the third derivative of all the splines at `x`
    void
    eval_DDD( real_type x, vector<real_type> & vals ) const;

    //! Evaluate the 4th derivative of all the splines at `x`
    void
    eval_DDDD( real_type x, vector<real_type> & vals ) const;

    //! Evaluate the 5th derivative of all the splines at `x`
    void
    eval_DDDDD( real_type x, vector<real_type> & vals ) const;

    /*!
     | Evaluate at `x` and fill a GenericContainer
    \*/
    void
    eval( real_type x, GenericContainer & vals ) const
    { eval( x, vals.set_vec_real() ); }

    void
    eval_D( real_type x, GenericContainer & vals ) const
    { eval_D( x, vals.set_vec_real() ); }

    void
    eval_DD( real_type x, GenericContainer & vals ) const
    { eval_DD( x, vals.set_vec_real() ); }

    void
    eval_DDD( real_type x, GenericContainer & vals ) const
    { eval_DDD( x, vals.set_vec_real() ); }

    void
    eval_DDDD( real_type x, GenericContainer & vals ) const
    { eval_DDDD( x, vals.set_vec_real() ); }

    void
    eval_DDDDD( real_type x, GenericContainer & vals ) const
    { eval_DDDDD( x, vals.set_vec_real() ); }

    /*!
     | Evaluate at `x` and fill a GenericContainer
    \*/
    void
    eval( vec_real_type const & x, GenericContainer & vals ) const;

    void
    eval_D( vec_real_type const & x, GenericContainer & vals ) const;

    void
    eval_DD( vec_real_type const & x, GenericContainer & vals ) const;

    void
    eval_DDD( vec_real_type const & x, GenericContainer & vals ) const;

    void
    eval_DDDD( vec_real_type const & x, GenericContainer & vals ) const;

    void
    eval_DDDDD( vec_real_type const & x, GenericContainer & vals ) const;

    void
    setup(
      integer           dim,
      integer           npts,
      real_type const * Y[]
    );

    void
    setup(
      integer         dim,
      integer         npts,
      real_type const Y[],
      integer         ldY
    );

    void
    setKnots( real_type const X[] );

    void
    setKnotsChordLength();

    void
    setKnotsCentripetal();

    void
    setKnotsFoley();

    void
    CatmullRom();

    real_type
    curvature( real_type x ) const;

    real_type
    curvature_D( real_type x ) const;

    virtual
    void
    setup( GenericContainer const & gc );

    void
    build( GenericContainer const & gc )
    { setup(gc); }

    //! Return spline type (as number)
    virtual
    unsigned
    type() const
    { return SPLINE_VEC_TYPE; }

    void
    info( ostream_type & s ) const;

    void
    dump_table( ostream_type & s, integer num_points ) const;

  };

  /*\
   |   ____        _ _            ____       _
   |  / ___| _ __ | (_)_ __   ___/ ___|  ___| |_
   |  \___ \| '_ \| | | '_ \ / _ \___ \ / _ \ __|
   |   ___) | |_) | | | | | |  __/___) |  __/ |_
   |  |____/| .__/|_|_|_| |_|\___|____/ \___|\__|
   |        |_|
  \*/

  //! Splines Management Class
  class SplineSet {

    SplineSet( SplineSet const & ) = delete;
    SplineSet const & operator = ( SplineSet const & ) = delete;

  protected:

    string const _name;

    SplineMalloc<real_type>  baseValue;
    SplineMalloc<real_type*> basePointer;

    integer _npts;
    integer _nspl;

    real_type *  _X;
    real_type ** _Y;
    real_type ** _Yp;
    real_type ** _Ypp;
    real_type *  _Ymin;
    real_type *  _Ymax;

    mutable std::mutex                   getPosition_mutex;
    mutable std::mutex                   lastInterval_mutex;
    mutable map<std::thread::id,integer> lastInterval_by_thread;

    vector<Spline*>     splines;
    vector<int>         is_monotone;
    map<string,integer> header_to_position;

  private:

    /*!
     | find `x` value such that the monotone spline
     | `(spline[spl])(x)` intersect the value `zeta`
    \*/
    Spline const *
    intersect( integer spl, real_type zeta, real_type & x ) const;

  public:

    //! spline constructor
    SplineSet( string const & name = "SplineSet" );

    //! spline destructor
    virtual
    ~SplineSet();

    string const & name() const { return _name; }

    string const &
    header( integer i ) const
    { return this->splines[size_t(i)]->name(); }

    // return +1 = strict monotone, 0 weak monotone, -1 non monotone
    int
    isMonotone( integer i ) const
    { return this->is_monotone[size_t(i)]; }

    //! return the number of support points of the splines
    integer
    numPoints(void) const
    { return this->_npts; }

    //! return the number splines in the spline set
    integer
    numSplines(void) const
    { return this->_nspl; }

    //! return the column with header(i) == hdr, return -1 if not found
    integer
    getPosition( char const * hdr ) const;

    //! return the vector of values of x-nodes
    real_type const *
    xNodes() const
    { return this->_X; }

    //! return the vector of values of x-nodes
    real_type const *
    yNodes( integer i ) const {
      SPLINE_ASSERT(
        i >=0 && i < this->_nspl,
        "SplineSet::yNodes( " << i <<
        ") argument out of range [0," << this->_nspl-1 << "]"
      )
      return this->_Y[size_t(i)];
    }

    //! return the i-th node of the spline (x component).
    real_type
    xNode( integer npt ) const
    { return this->_X[npt]; }

    //! return the i-th node of the spline (y component).
    real_type
    yNode( integer npt, integer spl ) const
    { return this->_Y[spl][npt]; }

    //! return x-minumum spline value
    real_type
    xMin() const
    { return this->_X[0]; }

    //! return x-maximum spline value
    real_type
    xMax() const
    { return this->_X[size_t(_npts-1)]; }

    //! return y-minumum spline value
    real_type
    yMin( integer spl ) const
    { return this->_Ymin[size_t(spl)]; }

    //! return y-maximum spline value
    real_type
    yMax( integer spl ) const
    { return this->_Ymax[size_t(spl)]; }

    //! return y-minumum spline value
    real_type
    yMin( char const spl[] ) const
    { return this->_Ymin[size_t(this->getPosition(spl))]; }

    //! return y-maximum spline value
    real_type
    yMax( char const spl[] ) const
    { return this->_Ymax[size_t(this->getPosition(spl))]; }

    //! Return pointer to the `i`-th spline
    Spline *
    getSpline( integer i ) const {
      SPLINE_ASSERT(
        i < _nspl,
        "SplineSet::getSpline( " << i <<
        ") argument out of range [0," << this->_nspl-1 << "]"
      )
      return this->splines[size_t(i)];
    }

    //! Return pointer to the `i`-th spline
    Spline *
    getSpline( char const * hdr ) const {
      return this->splines[size_t(this->getPosition(hdr))];
    }

    //! Evaluate spline value
    real_type
    operator () ( real_type x, integer spl ) const
    { return (*this->getSpline(spl))(x); }

    real_type
    eval( real_type x, integer spl ) const
    { return (*this->getSpline(spl))(x); }

    //! First derivative
    real_type
    D( real_type x, integer spl ) const
    { return this->getSpline(spl)->D(x); }

    real_type
    eval_D( real_type x, integer spl ) const
    { return this->getSpline(spl)->D(x); }

    //! Second derivative
    real_type
    DD( real_type x, integer spl ) const
    { return this->getSpline(spl)->DD(x); }

    real_type
    eval_DD( real_type x, integer spl ) const
    { return this->getSpline(spl)->DD(x); }

    //! Third derivative
    real_type
    DDD( real_type x, integer spl ) const
    { return this->getSpline(spl)->DDD(x); }

    real_type
    eval_DDD( real_type x, integer spl ) const
    { return this->getSpline(spl)->DDD(x); }

    //! 4th derivative
    real_type
    DDDD( real_type x, integer spl ) const
    { return this->getSpline(spl)->DDDD(x); }

    real_type
    eval_DDDD( real_type x, integer spl ) const
    { return this->getSpline(spl)->DDDD(x); }

    //! 5th derivative
    real_type
    DDDDD( real_type x, integer spl ) const
    { return this->getSpline(spl)->DDDDD(x); }

    real_type
    eval_DDDDD( real_type x, integer spl ) const
    { return this->getSpline(spl)->DDDDD(x); }

    //! Evaluate spline value
    real_type
    eval( real_type x, char const * name ) const
    { return (*this->getSpline(name))(x); }

    //! First derivative
    real_type
    eval_D( real_type x, char const * name ) const
    { return this->getSpline(name)->D(x); }

    //! Second derivative
    real_type
    eval_DD( real_type x, char const * name ) const
    { return this->getSpline(name)->DD(x); }

    //! Third derivative
    real_type
    eval_DDD( real_type x, char const * name ) const
    { return this->getSpline(name)->DDD(x); }

    //! 4th derivative
    real_type
    eval_DDDD( real_type x, char const * name ) const
    { return this->getSpline(name)->DDDD(x); }

    //! 5th derivative
    real_type
    eval_DDDDD( real_type x, char const * name ) const
    { return this->getSpline(name)->DDDDD(x); }

    // vectorial values
    //! fill a vector of strings with the names of the splines
    void
    getHeaders( vector<string> & h ) const;

    //! Evaluate all the splines at `x`
    void
    eval(
      real_type           x,
      vector<real_type> & vals
    ) const;

    //! Evaluate all the splines at `x`
    void
    eval(
      real_type x,
      real_type vals[],
      integer   incy = 1
    ) const;

    //! Evaluate the fist derivative of all the splines at `x`
    void
    eval_D(
      real_type           x,
      vector<real_type> & vals
    ) const;

    //! Evaluate the fist derivative of all the splines at `x`
    void
    eval_D(
      real_type x,
      real_type vals[],
      integer   incy = 1
    ) const;

    //! Evaluate the second derivative of all the splines at `x`
    void
    eval_DD(
      real_type           x,
      vector<real_type> & vals
    ) const;

    //! Evaluate the second derivative of all the splines at `x`
    void
    eval_DD(
      real_type x,
      real_type vals[],
      integer   incy = 1
    ) const;

    //! Evaluate the third derivative of all the splines at `x`
    void
    eval_DDD(
      real_type           x,
      vector<real_type> & vals
    ) const;

    //! Evaluate the third derivative of all the splines at `x`
    void
    eval_DDD(
      real_type x,
      real_type vals[],
      integer   incy = 1
    ) const;

    //! Evaluate the 4th derivative of all the splines at `x`
    void
    eval_DDDD(
      real_type           x,
      vector<real_type> & vals
    ) const;

    //! Evaluate the 4th derivative of all the splines at `x`
    void
    eval_DDDD(
      real_type x,
      real_type vals[],
      integer   incy = 1
    ) const;

    //! Evaluate the 5th derivative of all the splines at `x`
    void
    eval_DDDDD(
      real_type           x,
      vector<real_type> & vals
    ) const;

    //! Evaluate the 5th derivative of all the splines at `x`
    void
    eval_DDDDD(
      real_type x,
      real_type vals[],
      integer   incy = 1
    ) const;

    // change independent variable
    //! Evaluate all the splines at `zeta` using spline[spl] as independent
    void
    eval2(
      integer             spl,
      real_type           zeta,
      vector<real_type> & vals
    ) const;

    //! Evaluate all the splines at `zeta` using spline[spl] as independent
    void
    eval2(
      integer   spl,
      real_type zeta,
      real_type vals[],
      integer   incy = 1
    ) const;

    /*!
     | Evaluate the fist derivative of all the splines
     | at `zeta` using spline[spl] as independent
    \*/
    void
    eval2_D(
      integer             spl,
      real_type           zeta,
      vector<real_type> & vals
    ) const;

    /*!
     | Evaluate the fist derivative of all the splines
     | at `zeta` using spline[spl] as independent
    \*/
    void
    eval2_D(
      integer   spl,
      real_type zeta,
      real_type vals[],
      integer   incy = 1
    ) const;

    /*!
     | Evaluate the second derivative of all the splines
     | at `zeta` using spline[spl] as independent
    \*/
    void
    eval2_DD(
      integer             spl,
      real_type           zeta,
      vector<real_type> & vals
    ) const;

    /*!
     | Evaluate the second derivative of all the splines
     | at `zeta` using spline[spl] as independent
    \*/
    void
    eval2_DD(
      integer   spl,
      real_type zeta,
      real_type vals[],
      integer   incy = 1
    ) const;

    /*!
     | Evaluate the third derivative of all the splines
     | at `zeta` using spline[spl] as independent
    \*/
    void
    eval2_DDD(
      integer             spl,
      real_type           zeta,
      vector<real_type> & vals
    ) const;

    /*!
     | Evaluate the 3rd derivative of all the splines
     | at `zeta` using spline[spl] as independent
    \*/
    void
    eval2_DDD(
      integer   spl,
      real_type zeta,
      real_type vals[],
      integer   incy = 1
    ) const;

    /*!
     | Evaluate the spline `name` at `zeta` using
     | spline `indep` as independent
    \*/
    real_type
    eval2(
      real_type  zeta,
      char const indep[],
      char const name[]
    ) const;

    /*!
     | Evaluate first derivative of the spline `name`
     | at `zeta` using spline `indep` as independent
    \*/
    real_type
    eval2_D(
      real_type  zeta,
      char const indep[],
      char const name[]
    ) const;

    /*!
     | Evaluate second derivative of the spline `name`
     | at `zeta` using spline `indep` as independent
    \*/
    real_type
    eval2_DD(
      real_type  zeta,
      char const indep[],
      char const name[]
    ) const;

    /*!
     | Evaluate third derivative of the spline `name`
     | at `zeta` using spline `indep` as independent
    \*/
    real_type
    eval2_DDD(
      real_type  zeta,
      char const indep[],
      char const name[]
    ) const;

    /*!
     | Evaluate the spline `spl` at `zeta` using
     | spline `indep` as independent
    \*/
    real_type
    eval2(
      real_type zeta,
      integer   indep,
      integer   spl
    ) const;

    //! Evaluate first derivative of the spline `spl` at `zeta` using spline `indep` as independent
    real_type
    eval2_D(
      real_type zeta,
      integer   indep,
      integer   spl
    ) const;

    /*!
     | Evaluate second derivative of the spline `spl`
     | at `zeta` using spline `indep` as independent
    \*/
    real_type
    eval2_DD(
      real_type zeta,
      integer   indep,
      integer   spl
    ) const;

    /*!
     | Evaluate third derivative of the spline `spl`
     | at `zeta` using spline `indep` as independent
    \*/
    real_type
    eval2_DDD(
      real_type zeta,
      integer   indep,
      integer   spl
    ) const;

    /*!
     | Evaluate all the splines at `x`
     | and fill a map of values in a GenericContainer
    \*/
    void
    eval( real_type x, GenericContainer & vals ) const;

    /*!
     | Evaluate all the splines at `x` values contained
     | in vec and fill a map of vector in a GenericContainer
    \*/
    void
    eval( vec_real_type const & vec, GenericContainer & vals ) const;

    /*!
     | Evaluate all the splines at `x` and fill a map of
     | values in a GenericContainer with keys in `columns`
    \*/
    void
    eval(
      real_type               x,
      vec_string_type const & columns,
      GenericContainer      & vals
    ) const;

    /*!
     | Evaluate all the splines at `x` values contained
     | in vec and fill a map of vector in a GenericContainer
     | with keys in `columns`
    \*/
    void
    eval(
      vec_real_type   const & vec,
      vec_string_type const & columns,
      GenericContainer      & vals
    ) const;

    /*!
     | Evaluate all the splines at `zeta` and fill
     | a map of values in a GenericContainer and `indep`
     | as independent spline
    \*/
    void
    eval2(
      real_type          zeta,
      integer            indep,
      GenericContainer & vals
    ) const;

    /*!
     | Evaluate all the splines at `zeta` values contained in
     | vec and fill a map of vector in a GenericContainer and
     | `indep` as independent spline
    \*/
    void
    eval2(
      vec_real_type const & zetas,
      integer               indep,
      GenericContainer    & vals
    ) const;

    /*!
     | Evaluate all the splines at `zeta` and fill a map
     | of values in a GenericContainer with keys in `columns`
     | and `indep` as independent spline
    \*/
    void
    eval2(
      real_type               zeta,
      integer                 indep,
      vec_string_type const & columns,
      GenericContainer      & vals
    ) const;

    /*!
     | Evaluate all the splines at `zeta` values contained
     | in vec and fill a map of vector in a GenericContainer
     | with keys in `columns` and `indep` as independent spline
    \*/
    void
    eval2(
      vec_real_type   const & zetas,
      integer                 indep,
      vec_string_type const & columns,
      GenericContainer      & vals
    ) const;

    /*!
     | Evaluate all the splines at `zeta` and fill a map
     | of values in a GenericContainer and `indep` as independent spline
    \*/
    void
    eval2(
      real_type          zeta,
      char const       * indep,
      GenericContainer & vals
    ) const {
      this->eval2( zeta, this->getPosition(indep), vals );
    }

    /*!
     | Evaluate all the splines at `zeta` values contained
     | in vec and fill a map of vector in a GenericContainer
     | and `indep` as independent spline
    \*/
    void
    eval2(
      vec_real_type const & zetas,
      char const          * indep,
      GenericContainer    & vals
    ) const {
      this->eval2( zetas, this->getPosition(indep), vals );
    }

    /*!
     | Evaluate all the splines at `zeta` and fill a map of
     | values in a GenericContainer with keys in `columns`
     | and `indep` as independent spline
    \*/
    void
    eval2(
      real_type               zeta,
      char const            * indep,
      vec_string_type const & columns,
      GenericContainer      & vals
    ) const {
      this->eval2( zeta, this->getPosition(indep), columns, vals );
    }

    /*!
     | Evaluate all the splines at `zeta` values contained
     | in vec and fill a map of vector in a GenericContainer
     | with keys in `columns` and `indep` as independent spline
    \*/
    void
    eval2(
      vec_real_type const   & zetas,
      char const            * indep,
      vec_string_type const & columns,
      GenericContainer      & vals
    ) const {
      this->eval2( zetas, this->getPosition(indep), columns, vals );
    }

    /*!
     | Evaluate all the splines at `x` and fill a map of
     | values in a GenericContainer
    \*/
    void
    eval_D(
      real_type          x,
      GenericContainer & vals
    ) const;

    /*!
     | Evaluate all the splines at `x` values contained
     | in vec and fill a map of vector in a GenericContainer
    \*/
    void
    eval_D(
      vec_real_type const & vec,
      GenericContainer    & vals
    ) const;

    /*!
     | Evaluate all the splines at `x` and fill a map of
     | values in a GenericContainer with keys in `columns`
    \*/
    void
    eval_D(
      real_type               x,
      vec_string_type const & columns,
      GenericContainer      & vals
    ) const;

    /*!
     | Evaluate all the splines at `x` values contained
     | in vec and fill a map of vector in a GenericContainer
     | with keys in `columns`
    \*/
    void
    eval_D(
      vec_real_type const   & vec,
      vec_string_type const & columns,
      GenericContainer      & vals
    ) const;

    /*!
     | Evaluate all the splines at `zeta` and fill a map
     | of values in a GenericContainer and `indep` as independent spline
    \*/
    void
    eval2_D(
      real_type          zeta,
      integer            indep,
      GenericContainer & vals
    ) const;

    /*!
     | Evaluate all the splines at `zeta` values contained
     | in vec and fill a map of vector in a GenericContainer
     | and `indep` as independent spline
    \*/
    void
    eval2_D(
      vec_real_type const & zetas,
      integer               indep,
      GenericContainer    & vals
    ) const;

    /*!
     | Evaluate all the splines at `zeta` and fill a map
     | of values in a GenericContainer with keys in `columns`
     | and `indep` as independent spline
    \*/
    void
    eval2_D(
      real_type               zeta,
      integer                 indep,
      vec_string_type const & columns,
      GenericContainer      & vals
    ) const;

    /*!
     | Evaluate all the splines at `zeta` values contained
     | in vec and fill a map of vector in a GenericContainer
     | with keys in `columns` and `indep` as independent spline
    \*/
    void
    eval2_D(
      vec_real_type   const & zetas,
      integer                 indep,
      vec_string_type const & columns,
      GenericContainer      & vals
    ) const;

    /*!
     | Evaluate all the splines at `zeta` and fill a map
     | of values in a GenericContainer and `indep` as independent spline
    \*/
    void
    eval2_D(
      real_type          zeta,
      char const       * indep,
      GenericContainer & vals
    ) const {
      this->eval2_D( zeta, this->getPosition(indep), vals );
    }

    //! Evaluate all the splines at `zeta` values contained in vec and fill a map of vector in a GenericContainer and `indep` as independent spline
    void
    eval2_D(
      vec_real_type const & zetas,
      char const          * indep,
      GenericContainer    & vals
    ) const {
      this->eval2_D( zetas, this->getPosition(indep), vals );
    }

    /*!
     | Evaluate all the splines at `zeta` and fill a map of
     | values in a GenericContainer with keys in `columns`
     | and `indep` as independent spline
    \*/
    void
    eval2_D(
      real_type               zeta,
      char const            * indep,
      vec_string_type const & columns,
      GenericContainer      & vals
    ) const {
      this->eval2_D( zeta, this->getPosition(indep), columns, vals );
    }

    /*!
     | Evaluate all the splines at `zeta` values contained
     | in vec and fill a map of vector in a GenericContainer
     | with keys in `columns` and `indep` as independent spline
    \*/
    void
    eval2_D(
      vec_real_type const   & zetas,
      char const            * indep,
      vec_string_type const & columns,
      GenericContainer      & vals
    ) const {
      this->eval2_D( zetas, this->getPosition(indep), columns, vals );
    }

    /*!
     | Evaluate all the splines at `x` and fill a map of
     | values in a GenericContainer
    \*/
    void
    eval_DD(
      real_type          x,
      GenericContainer & vals
    ) const;

    /*!
     | Evaluate all the splines at `x` values contained in vec
     | and fill a map of vector in a GenericContainer
    \*/
    void
    eval_DD(
      vec_real_type const & vec,
      GenericContainer    & vals
    ) const;

    /*!
     | Evaluate all the splines at `x` and fill a map of
     | values in a GenericContainer with keys in `columns`
    \*/
    void
    eval_DD(
      real_type               x,
      vec_string_type const & columns,
      GenericContainer      & vals
    ) const;

    /*!
     | Evaluate all the splines at `x` values contained in vec and
     | fill a map of vector in a GenericContainer with keys in `columns`
    \*/
    void
    eval_DD(
      vec_real_type   const & vec,
      vec_string_type const & columns,
      GenericContainer      & vals
    ) const;

    /*!
     | Evaluate all the splines at `zeta` and fill a map of
     | values in a GenericContainer and `indep` as independent spline
    \*/
    void
    eval2_DD(
      real_type          zeta,
      integer            indep,
      GenericContainer & vals
    ) const;

    /*!
     | Evaluate all the splines at `zeta` values contained in vec
     | and fill a map of vector in a GenericContainer
     | and `indep` as independent spline
    \*/
    void
    eval2_DD(
      vec_real_type const & zetas,
      integer               indep,
      GenericContainer    & vals
    ) const;

    /*!
     | Evaluate all the splines at `zeta` and fill a map
     | of values in a GenericContainer with keys in `columns`
     | and `indep` as independent spline
    \*/
    void
    eval2_DD(
      real_type               zeta,
      integer                 indep,
      vec_string_type const & columns,
      GenericContainer      & vals
    ) const;

    /*!
     | Evaluate all the splines at `zeta` values contained
     | in vec and fill a map of vector in a GenericContainer
     | with keys in `columns` and `indep` as independent spline
    \*/
    void
    eval2_DD(
      vec_real_type   const & zetas,
      integer                 indep,
      vec_string_type const & columns,
      GenericContainer      & vals
    ) const;

    /*!
     | Evaluate all the splines at `zeta` and fill a map of
     | values in a GenericContainer and `indep` as independent spline
    \*/
    void
    eval2_DD(
      real_type          zeta,
      char const       * indep,
      GenericContainer & vals
    ) const {
      this->eval2_DD( zeta, this->getPosition(indep), vals );
    }

    /*!
     | Evaluate all the splines at `zeta` values contained in vec
     | and fill a map of vector in a GenericContainer
     | and `indep` as independent spline
    \*/
    void
    eval2_DD(
      vec_real_type const & zetas,
      char const          * indep,
      GenericContainer    & vals
    ) const {
      this->eval2_DD( zetas, this->getPosition(indep), vals );
    }

    /*!
     | Evaluate all the splines at `zeta` and fill a map
     | of values in a GenericContainer with keys in `columns`
     | and `indep` as independent spline
    \*/
    void
    eval2_DD(
      real_type               zeta,
      char const            * indep,
      vec_string_type const & columns,
      GenericContainer      & vals
    ) const {
      this->eval2_DD( zeta, this->getPosition(indep), columns, vals );
    }

    /*!
     | Evaluate all the splines at `zeta` values contained
     | in vec and fill a map of vector in a GenericContainer
     | with keys in `columns` and `indep` as independent spline
    \*/
    void
    eval2_DD(
      vec_real_type   const & zetas,
      char            const * indep,
      vec_string_type const & columns,
      GenericContainer      & vals
    ) const {
      this->eval2_DD( zetas, this->getPosition(indep), columns, vals );
    }

    /*!
     | Evaluate all the splines at `x` and fill a map
     | of values in a GenericContainer
    \*/
    void
    eval_DDD(
      real_type          x,
      GenericContainer & vals
    ) const;

    /*!
     | Evaluate all the splines at `x` values contained
     | in vec and fill a map of vector in a GenericContainer
    \*/
    void
    eval_DDD(
      vec_real_type const & vec,
      GenericContainer    & vals
    ) const;

    /*!
     | Evaluate all the splines at `x` and fill a map of
     | values in a GenericContainer with keys in `columns`
    \*/
    void
    eval_DDD(
      real_type               x,
      vec_string_type const & columns,
      GenericContainer      & vals
    ) const;

    /*!
     | Evaluate all the splines at `x` values contained in vec
     | and fill a map of vector in a GenericContainer with keys in `columns`
    \*/
    void
    eval_DDD(
      vec_real_type   const & vec,
      vec_string_type const & columns,
      GenericContainer      & vals
    ) const;

    /*!
     | Evaluate all the splines at `zeta` and fill a map of values
     | in a GenericContainer and `indep` as independent spline
    \*/
    void
    eval2_DDD(
      real_type          zeta,
      integer            indep,
      GenericContainer & vals
    ) const;

    /*!
     | Evaluate all the splines at `zeta` values contained in vec
     | and fill a map of vector in a GenericContainer
     | and `indep` as independent spline
    \*/
    void
    eval2_DDD(
      vec_real_type const & zetas,
      integer               indep,
      GenericContainer    & vals
    ) const;

    /*!
     | Evaluate all the splines at `zeta` and fill a map of values
     | in a GenericContainer with keys in `columns`
     | and `indep` as independent spline
    \*/
    void
    eval2_DDD(
      real_type               zeta,
      integer                 indep,
      vec_string_type const & columns,
      GenericContainer      & vals
    ) const;

    /*!
     | Evaluate all the splines at `zeta` values contained
     | in vec and fill a map of vector in a GenericContainer
     | with keys in `columns` and `indep` as independent spline
    \*/
    void
    eval2_DDD(
      vec_real_type   const & zetas,
      integer                 indep,
      vec_string_type const & columns,
      GenericContainer      & vals
    ) const;

    /*!
     | Evaluate all the splines at `zeta` and fill a map
     | of values in a GenericContainer and `indep` as independent spline
    \*/
    void
    eval2_DDD(
      real_type          zeta,
      char const       * indep,
      GenericContainer & vals
    ) const {
      this->eval2_DDD( zeta, this->getPosition(indep), vals );
    }

    /*!
     | Evaluate all the splines at `zeta` values contained
     | in vec and fill a map of vector in a GenericContainer
     | and `indep` as independent spline
    \*/
    void
    eval2_DDD(
      vec_real_type const & zetas,
      char          const * indep,
      GenericContainer    & vals
    ) const {
      this->eval2_DDD( zetas, this->getPosition(indep), vals );
    }

    /*!
     | Evaluate all the splines at `zeta` and fill a map of
     | values in a GenericContainer with keys in `columns`
     | and `indep` as independent spline
    \*/
    void
    eval2_DDD(
      real_type               zeta,
      char            const * indep,
      vec_string_type const & columns,
      GenericContainer      & vals
    ) const {
      this->eval2_DDD( zeta, this->getPosition(indep), columns, vals );
    }

    /*!
     | Evaluate all the splines at `zeta` values contained
     | in vec and fill a map of vector in a GenericContainer
     | with keys in `columns` and `indep` as independent spline
    \*/
    void
    eval2_DDD(
      vec_real_type   const & zetas,
      char            const * indep,
      vec_string_type const & columns,
      GenericContainer      & vals
    ) const {
      this->eval2_DDD( zetas, this->getPosition(indep), columns, vals );
    }

    ///////////////////////////////////////////////////////////////////////////
    /*! Build a set of splines
     | \param nspl       the number of splines
     | \param npts       the number of points of each splines
     | \param headers    the names of the splines
     | \param stype      the type of each spline
     | \param X          pointer to X independent values
     | \param Y          vector of `nspl` pointers to Y depentendent values.
    \*/

    void
    build(
      integer            nspl,
      integer            npts,
      char         const *headers[],
      SplineType1D const stype[],
      real_type    const X[],
      real_type    const *Y[],
      real_type    const *Yp[] = nullptr
    );

    void
    setup( GenericContainer const & gc );

    void
    build( GenericContainer const & gc )
    { this->setup(gc); }

    //! Return spline type (as number)
    unsigned
    type() const
    { return SPLINE_SET_TYPE; }

    void
    info( ostream_type & s ) const;

    void
    dump_table( ostream_type & s, integer num_points ) const;

  };

  /*\
   |   ____        _ _            ____              __
   |  / ___| _ __ | (_)_ __   ___/ ___| _   _ _ __ / _|
   |  \___ \| '_ \| | | '_ \ / _ \___ \| | | | '__| |_
   |   ___) | |_) | | | | | |  __/___) | |_| | |  |  _|
   |  |____/| .__/|_|_|_| |_|\___|____/ \__,_|_|  |_|
   |        |_|
  \*/
  //! Spline Management Class
  class SplineSurf {

    SplineSurf( SplineSurf const & ) = delete; // block copy constructor
    SplineSurf const & operator = ( SplineSurf const & ) = delete; // block copy method

  protected:

    string const _name;
    bool         _x_closed;
    bool         _y_closed;
    bool         _x_can_extend;
    bool         _y_can_extend;

    vector<real_type> X, Y, Z;

    real_type Z_min, Z_max;

    mutable std::mutex                   lastInterval_x_mutex;
    mutable map<std::thread::id,integer> lastInterval_x_by_thread;

    integer
    search_x( real_type & x ) const {
      integer lastInterval;
      {
        std::lock_guard<std::mutex> lck(lastInterval_x_mutex);
        lastInterval = lastInterval_x_by_thread[std::this_thread::get_id()];
      }
      integer       npts_x = integer(this->X.size());
      real_type const * pX = &this->X.front();
      searchInterval(
        npts_x,
        pX,
        x,
        lastInterval,
        this->_x_closed,
        this->_x_can_extend
      );
      {
        std::lock_guard<std::mutex> lck(lastInterval_x_mutex);
        lastInterval_x_by_thread[std::this_thread::get_id()] = lastInterval;
      }
      return lastInterval;
    }

    mutable std::mutex                   lastInterval_y_mutex;
    mutable map<std::thread::id,integer> lastInterval_y_by_thread;

    integer
    search_y( real_type & y ) const {
      integer lastInterval;
      {
        std::lock_guard<std::mutex> lck(lastInterval_y_mutex);
        lastInterval = lastInterval_y_by_thread[std::this_thread::get_id()];
      }
      integer       npts_y = integer(this->Y.size());
      real_type const * pY = &this->Y.front();
      searchInterval(
        npts_y,
        pY,
        y,
        lastInterval,
        this->_y_closed,
        this->_y_can_extend
      );
      {
        std::lock_guard<std::mutex> lck(lastInterval_y_mutex);
        lastInterval_y_by_thread[std::this_thread::get_id()] = lastInterval;
      }
      return lastInterval;
    }

    integer
    ipos_C( integer i, integer j, integer ldZ ) const
    { return i*ldZ + j; }

    integer
    ipos_F( integer i, integer j, integer ldZ ) const
    { return i + ldZ*j; }

    integer
    ipos_C( integer i, integer j ) const
    { return this->ipos_C(i,j,integer(this->Y.size())); }

    integer
    ipos_F( integer i, integer j ) const
    { return this->ipos_F(i,j,integer(this->X.size())); }

    virtual void makeSpline() SPLINES_PURE_VIRTUAL;

  public:

    //! spline constructor
    SplineSurf( string const & name = "Spline" )
    : _name(name)
    , _x_closed(false)
    , _y_closed(false)
    , _x_can_extend(true)
    , _y_can_extend(true)
    , X()
    , Y()
    , Z()
    , Z_min(0)
    , Z_max(0)
    {
      {
        std::lock_guard<std::mutex> lck(lastInterval_x_mutex);
        lastInterval_x_by_thread[std::this_thread::get_id()] = 0;
      }
      {
        std::lock_guard<std::mutex> lck(lastInterval_y_mutex);
        lastInterval_y_by_thread[std::this_thread::get_id()] = 0;
      }
    }

    //! spline destructor
    virtual
    ~SplineSurf();

    bool is_x_closed() const { return this->_x_closed; }
    void make_x_closed()     { this->_x_closed = true; }
    void make_x_opened()     { this->_x_closed = false; }

    bool is_y_closed() const { return this->_y_closed; }
    void make_y_closed()     { this->_y_closed = true; }
    void make_y_opened()     { this->_y_closed = false; }

    bool is_x_bounded() const { return this->_x_can_extend; }
    void make_x_unbounded()   { this->_x_can_extend = true; }
    void make_x_bounded()     { this->_x_can_extend = false; }

    bool is_y_bounded() const { return this->_y_can_extend; }
    void make_y_unbounded()   { this->_y_can_extend = true; }
    void make_y_bounded()     { this->_y_can_extend = false; }

    string const &
    name() const
    { return this->_name; }

    //! Cancel the support points, empty the spline.
    void
    clear(void);

    //! return the number of support points of the spline along x direction
    integer
    numPointX(void) const
    { return integer(this->X.size()); }

    //! return the number of support points of the spline along y direction
    integer
    numPointY(void) const
    { return integer(this->Y.size()); }

    //! return the i-th node of the spline (x component).
    real_type
    xNode( integer i ) const
    { return this->X[size_t(i)]; }

    //! return the i-th node of the spline (y component).
    real_type
    yNode( integer i ) const
    { return this->Y[size_t(i)]; }

    //! return the i-th node of the spline (y component).
    real_type
    zNode( integer i, integer j ) const
    { return this->Z[size_t(this->ipos_C(i,j))]; }

    //! return x-minumum spline value
    real_type
    xMin() const
    { return this->X.front(); }

    //! return x-maximum spline value
    real_type
    xMax() const
    { return this->X.back(); }

    //! return y-minumum spline value
    real_type
    yMin() const
    { return this->Y.front(); }

    //! return y-maximum spline value
    real_type
    yMax() const
    { return this->Y.back(); }

    //! return z-minumum spline value
    real_type
    zMin() const
    { return this->Z_min; }

    //! return z-maximum spline value
    real_type
    zMax() const
    { return this->Z_max; }

    ///////////////////////////////////////////////////////////////////////////
    /*! Build surface spline
     | \param x       vector of x-coordinates
     | \param incx    access elements as x[0], x[incx], x[2*incx],...
     | \param y       vector of y-coordinates
     | \param incy    access elements as y[0], y[incy], x[2*incy],...
     | \param z       matrix of z-values
     | \param ldZ     leading dimension of the matrix. Elements are stored
     |                by row Z(i,j) = z[i*ldZ+j] as C-matrix
     | \param nx      total number of points in direction x
     | \param ny      total number of points in direction y
     | \param fortran_storage if true elements are stored by column
     |                        i.e. Z(i,j) = z[i+j*ldZ] as Fortran-matrix
     | \param transposed      if true matrix Z is stored transposed
    \*/
    void
    build(
      real_type const x[], integer incx,
      real_type const y[], integer incy,
      real_type const z[], integer ldZ,
      integer nx, integer ny,
      bool fortran_storage = false,
      bool transposed      = false
    );

    /*! Build surface spline
     | \param x       vector of x-coordinates, nx = x.size()
     | \param y       vector of y-coordinates, ny = y.size()
     | \param z       matrix of z-values. Elements are stored
     |                by row Z(i,j) = z[i*ny+j] as C-matrix
     | \param fortran_storage if true elements are stored by column
     |                        i.e. Z(i,j) = z[i+j*nx] as Fortran-matrix
     | \param transposed      if true matrix Z is stored transposed
    \*/
    void
    build(
      vector<real_type> const & x,
      vector<real_type> const & y,
      vector<real_type> const & z,
      bool fortran_storage = false,
      bool transposed      = false
    ) {
      bool xyswp = (fortran_storage && transposed) ||
                   (!fortran_storage && !transposed);
      this->build(
        &x.front(), 1,
        &y.front(), 1,
        &z.front(), integer(xyswp ? y.size() : x.size()),
        integer(x.size()), integer(y.size()),
        fortran_storage, transposed
      );
    }

    /*! Build surface spline
     | \param z               matrix of z-values. Elements are stored
     |                        by row Z(i,j) = z[i*ny+j] as C-matrix
     | \param ldZ             leading dimension of the matrix. Elements are stored
     |                        by row Z(i,j) = z[i*ldZ+j] as C-matrix
     | \param fortran_storage if true elements are stored by column
     |                        i.e. Z(i,j) = z[i+j*nx] as Fortran-matrix
     | \param transposed      if true matrix Z is stored transposed
    \*/
    void
    build(
      real_type const z[],
      integer         ldZ,
      integer         nx,
      integer         ny,
      bool fortran_storage = false,
      bool transposed      = false
    );

    /*! Build surface spline
     | \param z               matrix of z-values. Elements are stored
     |                        by row Z(i,j) = z[i*ny+j] as C-matrix.
     |                        ldZ leading dimension of the matrix is ny for C-storage
     |                        and nx for Fortran storage.
     | \param fortran_storage if true elements are stored by column
     |                        i.e. Z(i,j) = z[i+j*nx] as Fortran-matrix
     | \param transposed      if true matrix Z is stored transposed
    \*/
    void
    build(
      vector<real_type> const & z,
      integer                   nx,
      integer                   ny,
      bool fortran_storage = false,
      bool transposed      = false
    ) {
      if ( fortran_storage )
        this->build( &z.front(), nx, nx, ny, fortran_storage, transposed );
      else
        this->build( &z.front(), ny, nx, ny, fortran_storage, transposed );
    }

    void
    setup( GenericContainer const & gc );

    void
    build ( GenericContainer const & gc )
    { setup(gc); }

    //! Evaluate spline value
    virtual
    real_type
    operator () ( real_type x, real_type y ) const SPLINES_PURE_VIRTUAL;

    //! First derivative
    virtual
    void
    D( real_type x, real_type y, real_type d[3] ) const SPLINES_PURE_VIRTUAL;

    virtual
    real_type
    Dx( real_type x, real_type y ) const SPLINES_PURE_VIRTUAL;

    virtual
    real_type
    Dy( real_type x, real_type y ) const SPLINES_PURE_VIRTUAL;

    //! Second derivative
    virtual
    void
    DD( real_type x, real_type y, real_type dd[6] ) const SPLINES_PURE_VIRTUAL;

    virtual
    real_type
    Dxx( real_type x, real_type y ) const SPLINES_PURE_VIRTUAL;

    virtual
    real_type
    Dxy( real_type x, real_type y ) const SPLINES_PURE_VIRTUAL;

    virtual
    real_type
    Dyy( real_type x, real_type y ) const SPLINES_PURE_VIRTUAL;

    //! Evaluate spline value
    real_type
    eval( real_type x, real_type y ) const
    { return (*this)(x,y); }

    //! First derivative
    real_type
    eval_D_1( real_type x, real_type y ) const
    { return this->Dx(x,y); }

    real_type
    eval_D_2( real_type x, real_type y ) const
    { return this->Dy(x,y); }

    //! Second derivative
    real_type
    eval_D_1_1( real_type x, real_type y ) const
    { return this->Dxx(x,y); }

    real_type
    eval_D_1_2( real_type x, real_type y ) const
    { return this->Dxy(x,y); }

    real_type
    eval_D_2_2( real_type x, real_type y ) const
    { return this->Dyy(x,y); }

    //! Print spline coefficients
    virtual
    void
    writeToStream( ostream_type & s ) const SPLINES_PURE_VIRTUAL;

    //! Return spline typename
    virtual
    char const *
    type_name() const SPLINES_PURE_VIRTUAL;

    void
    info( ostream & s ) const;

  };

  /*\
   |   ____  _ _ _                       ____        _ _
   |  | __ )(_) (_)_ __   ___  __ _ _ __/ ___| _ __ | (_)_ __   ___
   |  |  _ \| | | | '_ \ / _ \/ _` | '__\___ \| '_ \| | | '_ \ / _ \
   |  | |_) | | | | | | |  __/ (_| | |   ___) | |_) | | | | | |  __/
   |  |____/|_|_|_|_| |_|\___|\__,_|_|  |____/| .__/|_|_|_| |_|\___|
   |                                          |_|
  \*/
  //! bilinear spline base class
  class BilinearSpline : public SplineSurf {
    virtual void makeSpline() SPLINES_OVERRIDE {}
  public:

    //! spline constructor
    BilinearSpline( string const & name = "Spline" )
    : SplineSurf(name)
    {}

    virtual
    ~BilinearSpline() SPLINES_OVERRIDE
    {}

    //! Evaluate spline value
    virtual
    real_type
    operator () ( real_type x, real_type y ) const SPLINES_OVERRIDE;

    //! First derivative
    virtual
    void
    D( real_type x, real_type y, real_type d[3] ) const SPLINES_OVERRIDE;

    virtual
    real_type
    Dx( real_type x, real_type y ) const SPLINES_OVERRIDE;

    virtual
    real_type
    Dy( real_type x, real_type y ) const SPLINES_OVERRIDE;

    //! Second derivative
    virtual
    void
    DD( real_type x, real_type y, real_type dd[6] ) const SPLINES_OVERRIDE;

    virtual
    real_type
    Dxx( real_type , real_type ) const SPLINES_OVERRIDE
    { return 0; }

    virtual
    real_type
    Dxy( real_type , real_type ) const SPLINES_OVERRIDE
    { return 0; }

    virtual
    real_type
    Dyy( real_type , real_type ) const SPLINES_OVERRIDE
    { return 0; }

    //! Print spline coefficients
    virtual
    void
    writeToStream( ostream_type & s ) const SPLINES_OVERRIDE;

    //! Return spline typename
    virtual
    char const *
    type_name() const SPLINES_OVERRIDE;

  };

  /*\
   |   ____  _  ____      _     _      ____        _ _            ____
   |  | __ )(_)/ ___|   _| |__ (_) ___/ ___| _ __ | (_)_ __   ___| __ )  __ _ ___  ___
   |  |  _ \| | |  | | | | '_ \| |/ __\___ \| '_ \| | | '_ \ / _ \  _ \ / _` / __|/ _ \
   |  | |_) | | |__| |_| | |_) | | (__ ___) | |_) | | | | | |  __/ |_) | (_| \__ \  __/
   |  |____/|_|\____\__,_|_.__/|_|\___|____/| .__/|_|_|_| |_|\___|____/ \__,_|___/\___|
   |                                        |_|
  \*/
  //! Bi-cubic spline base class
  class BiCubicSplineBase : public SplineSurf {
  protected:

    vector<real_type> DX, DY, DXY;
    void load( integer i, integer j, real_type bili3[4][4] ) const;

  public:

    //! spline constructor
    BiCubicSplineBase( string const & name = "Spline" )
    : SplineSurf( name )
    , DX()
    , DY()
    {}

    virtual
    ~BiCubicSplineBase() SPLINES_OVERRIDE
    {}

    real_type
    DxNode ( integer i, integer j ) const
    { return this->DX[size_t(this->ipos_C(i,j))]; }

    real_type
    DyNode ( integer i, integer j ) const
    { return this->DY[size_t(this->ipos_C(i,j))]; }

    real_type
    DxyNode( integer i, integer j ) const
    { return this->DXY[size_t(this->ipos_C(i,j))]; }

    //! Evaluate spline value
    virtual
    real_type
    operator () ( real_type x, real_type y ) const SPLINES_OVERRIDE;

    //! First derivative
    virtual
    void
    D( real_type x, real_type y, real_type d[3] ) const SPLINES_OVERRIDE;

    virtual
    real_type
    Dx( real_type x, real_type y ) const SPLINES_OVERRIDE;

    virtual
    real_type
    Dy( real_type x, real_type y ) const SPLINES_OVERRIDE;

    //! Second derivative
    virtual
    void
    DD( real_type x, real_type y, real_type dd[6] ) const SPLINES_OVERRIDE;

    virtual
    real_type
    Dxx( real_type x, real_type y ) const SPLINES_OVERRIDE;

    virtual
    real_type
    Dxy( real_type x, real_type y ) const SPLINES_OVERRIDE;

    virtual
    real_type
    Dyy( real_type x, real_type y ) const SPLINES_OVERRIDE;
  };

  /*\
   |   ____  _  ____      _     _      ____        _ _
   |  | __ )(_)/ ___|   _| |__ (_) ___/ ___| _ __ | (_)_ __   ___
   |  |  _ \| | |  | | | | '_ \| |/ __\___ \| '_ \| | | '_ \ / _ \
   |  | |_) | | |__| |_| | |_) | | (__ ___) | |_) | | | | | |  __/
   |  |____/|_|\____\__,_|_.__/|_|\___|____/| .__/|_|_|_| |_|\___|
   |                                        |_|
  \*/
  //! cubic spline base class
  class BiCubicSpline : public BiCubicSplineBase {
    virtual void makeSpline() SPLINES_OVERRIDE;

  public:

    //! spline constructor
    BiCubicSpline( string const & name = "Spline" )
    : BiCubicSplineBase( name )
    {}

    virtual
    ~BiCubicSpline() SPLINES_OVERRIDE
    {}

    //! Print spline coefficients
    virtual
    void
    writeToStream( ostream_type & s ) const SPLINES_OVERRIDE;

    //! Return spline typename
    virtual
    char const *
    type_name() const SPLINES_OVERRIDE;

  };

  /*\
   |      _    _    _                 ____  ____            _ _
   |     / \  | | _(_)_ __ ___   __ _|___ \|  _ \ ___ _ __ | (_)_ __   ___
   |    / _ \ | |/ / | '_ ` _ \ / _` | __) | | | / __| '_ \| | | '_ \ / _ \
   |   / ___ \|   <| | | | | | | (_| |/ __/| |_| \__ \ |_) | | | | | |  __/
   |  /_/   \_\_|\_\_|_| |_| |_|\__,_|_____|____/|___/ .__/|_|_|_| |_|\___|
   |                                                 |_|
  \*/
  //! cubic spline base class
  class Akima2Dspline : public BiCubicSplineBase {
    virtual void makeSpline() SPLINES_OVERRIDE;

  public:

    //! spline constructor
    Akima2Dspline( string const & name = "Spline" )
    : BiCubicSplineBase( name )
    {}

    virtual
    ~Akima2Dspline() SPLINES_OVERRIDE
    {}

    //! Print spline coefficients
    virtual
    void
    writeToStream( ostream_type & s ) const SPLINES_OVERRIDE;

    //! Return spline typename
    virtual
    char const *
    type_name() const SPLINES_OVERRIDE;

  };

  /*\
   |   ____  _  ___        _       _   _      ____        _ _            ____
   |  | __ )(_)/ _ \ _   _(_)_ __ | |_(_) ___/ ___| _ __ | (_)_ __   ___| __ )  __ _ ___  ___
   |  |  _ \| | | | | | | | | '_ \| __| |/ __\___ \| '_ \| | | '_ \ / _ \  _ \ / _` / __|/ _ \
   |  | |_) | | |_| | |_| | | | | | |_| | (__ ___) | |_) | | | | | |  __/ |_) | (_| \__ \  __/
   |  |____/|_|\__\_\\__,_|_|_| |_|\__|_|\___|____/| .__/|_|_|_| |_|\___|____/ \__,_|___/\___|
   |                                               |_|
  \*/
  //! Bi-quintic spline base class
  class BiQuinticSplineBase : public SplineSurf {
  protected:

    vector<real_type> DX, DXX, DY, DYY, DXY, DXYY, DXXY, DXXYY;
    void load( integer i, integer j, real_type bili5[6][6] ) const;

  public:

    //! spline constructor
    BiQuinticSplineBase( string const & name = "Spline" )
    : SplineSurf( name )
    , DX()
    , DXX()
    , DY()
    , DYY()
    , DXY()
    {}

    virtual
    ~BiQuinticSplineBase() SPLINES_OVERRIDE
    {}

    real_type
    DxNode( integer i, integer j ) const
    { return this->DX[size_t(this->ipos_C(i,j))]; }

    real_type
    DyNode( integer i, integer j ) const
    { return this->DY[size_t(this->ipos_C(i,j))]; }

    real_type
    DxxNode( integer i, integer j ) const
    { return this->DXX[size_t(this->ipos_C(i,j))]; }

    real_type
    DyyNode( integer i, integer j ) const
    { return this->DYY[size_t(this->ipos_C(i,j))]; }

    real_type
    DxyNode( integer i, integer j ) const
    { return this->DXY[size_t(this->ipos_C(i,j))]; }

    //! Evaluate spline value
    virtual
    real_type
    operator () ( real_type x, real_type y ) const SPLINES_OVERRIDE;

    //! First derivative
    virtual
    void
    D( real_type x, real_type y, real_type d[3] ) const SPLINES_OVERRIDE;

    virtual
    real_type
    Dx( real_type x, real_type y ) const SPLINES_OVERRIDE;

    virtual
    real_type
    Dy( real_type x, real_type y ) const SPLINES_OVERRIDE;

    //! Second derivative
    virtual
    void
    DD( real_type x, real_type y, real_type dd[6] ) const SPLINES_OVERRIDE;

    virtual
    real_type
    Dxx( real_type x, real_type y ) const SPLINES_OVERRIDE;

    virtual
    real_type
    Dxy( real_type x, real_type y ) const SPLINES_OVERRIDE;

    virtual
    real_type
    Dyy( real_type x, real_type y ) const SPLINES_OVERRIDE;
  };

  /*\
   |   ____  _  ___        _       _   _      ____        _ _
   |  | __ )(_)/ _ \ _   _(_)_ __ | |_(_) ___/ ___| _ __ | (_)_ __   ___
   |  |  _ \| | | | | | | | | '_ \| __| |/ __\___ \| '_ \| | | '_ \ / _ \
   |  | |_) | | |_| | |_| | | | | | |_| | (__ ___) | |_) | | | | | |  __/
   |  |____/|_|\__\_\\__,_|_|_| |_|\__|_|\___|____/| .__/|_|_|_| |_|\___|
   |                                               |_|
  \*/
  //! cubic spline base class
  class BiQuinticSpline : public BiQuinticSplineBase {
    virtual void makeSpline() SPLINES_OVERRIDE;
  public:

    //! spline constructor
    BiQuinticSpline( string const & name = "Spline" )
    : BiQuinticSplineBase( name )
    {}

    virtual
    ~BiQuinticSpline() SPLINES_OVERRIDE
    {}

    //! Print spline coefficients
    virtual
    void
    writeToStream( ostream_type & s ) const SPLINES_OVERRIDE;

    //! Return spline typename
    virtual
    char const *
    type_name() const SPLINES_OVERRIDE;

  };

  /*\
   |   ____        _ _            ____  ____
   |  / ___| _ __ | (_)_ __   ___|___ \|  _ \
   |  \___ \| '_ \| | | '_ \ / _ \ __) | | | |
   |   ___) | |_) | | | | | |  __// __/| |_| |
   |  |____/| .__/|_|_|_| |_|\___|_____|____/
   |        |_|
  \*/

  //! Bi-quintic spline base class
  class Spline2D {
  protected:
    std::string  _name;
    SplineSurf * pSpline2D;
  public:

    //! spline constructor
    Spline2D( string const & name = "Spline2D" )
    : _name(name)
    , pSpline2D( nullptr )
    {}

    ~Spline2D()
    {}

    bool is_x_closed() const { return pSpline2D->is_x_closed(); }
    void make_x_closed()     { pSpline2D->make_x_closed(); }
    void make_x_opened()     { pSpline2D->make_x_opened(); }

    bool is_y_closed() const { return pSpline2D->is_y_closed(); }
    void make_y_closed()     { pSpline2D->make_y_closed(); }
    void make_y_opened()     { pSpline2D->make_y_opened(); }

    bool is_x_bounded() const { return pSpline2D->is_x_bounded(); }
    void make_x_unbounded()   { pSpline2D->make_x_unbounded(); }
    void make_x_bounded()     { pSpline2D->make_x_bounded(); }

    bool is_y_bounded() const { return pSpline2D->is_y_bounded(); }
    void make_y_unbounded()   { pSpline2D->make_y_unbounded(); }
    void make_y_bounded()     { pSpline2D->make_y_bounded(); }

    string const & name() const { return pSpline2D->name(); }

    //! Cancel the support points, empty the spline.
    void clear(void) { pSpline2D->clear(); }

    //! return the number of support points of the spline along x direction
    integer
    numPointX(void) const { return pSpline2D->numPointX(); }

    //! return the number of support points of the spline along y direction
    integer
    numPointY(void) const { return pSpline2D->numPointY(); }

    //! return the i-th node of the spline (x component).
    real_type
    xNode( integer i ) const { return pSpline2D->xNode(i); }

    //! return the i-th node of the spline (y component).
    real_type
    yNode( integer i ) const { return pSpline2D->yNode(i); }

    //! return the i-th node of the spline (y component).
    real_type
    zNode( integer i, integer j ) const { return pSpline2D->zNode(i,j); }

    //! return x-minumum spline value
    real_type
    xMin() const { return pSpline2D->xMin(); }

    //! return x-maximum spline value
    real_type
    xMax() const { return pSpline2D->xMax(); }

    //! return y-minumum spline value
    real_type
    yMin() const { return pSpline2D->yMin(); }

    //! return y-maximum spline value
    real_type
    yMax() const { return pSpline2D->yMax(); }

    //! return z-minumum spline value
    real_type
    zMin() const { return pSpline2D->zMin(); }

    //! return z-maximum spline value
    real_type
    zMax() const { return pSpline2D->zMax(); }

    void
    build(
      SplineType2D    tp,
      real_type const x[], integer incx,
      real_type const y[], integer incy,
      real_type const z[], integer ldZ,
      integer nx, integer ny,
      bool fortran_storage = false,
      bool transposed      = false
    );

    /*! Build surface spline
     | \param x       vector of x-coordinates, nx = x.size()
     | \param y       vector of y-coordinates, ny = y.size()
     | \param z       matrix of z-values. Elements are stored
     |                by row Z(i,j) = z[i*ny+j] as C-matrix
     | \param fortran_storage if true elements are stored by column
     |                        i.e. Z(i,j) = z[i+j*nx] as Fortran-matrix
     | \param transposed      if true matrix Z is stored transposed
    \*/
    void
    build(
      SplineType2D              tp,
      vector<real_type> const & x,
      vector<real_type> const & y,
      vector<real_type> const & z,
      bool fortran_storage = false,
      bool transposed      = false
    );

    /*! Build surface spline
     | \param z               matrix of z-values. Elements are stored
     |                        by row Z(i,j) = z[i*ny+j] as C-matrix
     | \param ldZ             leading dimension of the matrix. Elements are stored
     |                        by row Z(i,j) = z[i*ldZ+j] as C-matrix
     | \param fortran_storage if true elements are stored by column
     |                        i.e. Z(i,j) = z[i+j*nx] as Fortran-matrix
     | \param transposed      if true matrix Z is stored transposed
    \*/
    void
    build(
      SplineType2D    tp,
      real_type const z[],
      integer         ldZ,
      integer         nx,
      integer         ny,
      bool fortran_storage = false,
      bool transposed      = false
    );

    /*! Build surface spline
     | \param z               matrix of z-values. Elements are stored
     |                        by row Z(i,j) = z[i*ny+j] as C-matrix.
     |                        ldZ leading dimension of the matrix is ny for C-storage
     |                        and nx for Fortran storage.
     | \param fortran_storage if true elements are stored by column
     |                        i.e. Z(i,j) = z[i+j*nx] as Fortran-matrix
     | \param transposed      if true matrix Z is stored transposed
    \*/
    void
    build(
      SplineType2D              tp,
      vector<real_type> const & z,
      integer                   nx,
      integer                   ny,
      bool fortran_storage = false,
      bool transposed      = false
    );

    void
    setup( GenericContainer const & gc );

    void
    build( GenericContainer const & gc )
    { setup(gc); }

    //! Evaluate spline value
    real_type
    operator () ( real_type x, real_type y ) const
    { return (*pSpline2D)( x, y ); }

    //! First derivative
    void
    D( real_type x, real_type y, real_type d[3] ) const
    { return pSpline2D->D( x, y, d ); }

    real_type
    Dx( real_type x, real_type y ) const
    { return pSpline2D->Dx( x, y ); }

    real_type
    Dy( real_type x, real_type y ) const
    { return pSpline2D->Dy( x, y ); }

    //! Second derivative
    void
    DD( real_type x, real_type y, real_type dd[6] ) const
    { return pSpline2D->DD( x, y, dd ); }

    real_type
    Dxx( real_type x, real_type y ) const
    { return pSpline2D->Dxx( x, y ); }

    real_type
    Dxy( real_type x, real_type y ) const
    { return pSpline2D->Dxy( x, y ); }

    real_type
    Dyy( real_type x, real_type y ) const
    { return pSpline2D->Dyy( x, y ); }

    //! Evaluate spline value
    real_type
    eval( real_type x, real_type y ) const
    { return (*this)(x,y); }

    //! First derivative
    real_type
    eval_D_1( real_type x, real_type y ) const
    { return this->Dx(x,y); }

    real_type
    eval_D_2( real_type x, real_type y ) const
    { return this->Dy(x,y); }

    //! Second derivative
    real_type
    eval_D_1_1( real_type x, real_type y ) const
    { return this->Dxx(x,y); }

    real_type
    eval_D_1_2( real_type x, real_type y ) const
    { return this->Dxy(x,y); }

    real_type
    eval_D_2_2( real_type x, real_type y ) const
    { return this->Dyy(x,y); }

    //! Print spline coefficients
    void
    writeToStream( ostream_type & s ) const
    { return pSpline2D->writeToStream( s ); }

    //! Return spline typename
    char const * type_name() const { return pSpline2D->type_name(); }

    void info( ostream & s ) const { pSpline2D->info( s ); }

  };

}

namespace SplinesLoad {

  using Splines::Spline;
  using Splines::CubicSplineBase;
  using Splines::CubicSpline;
  using Splines::AkimaSpline;
  using Splines::BesselSpline;
  using Splines::PchipSpline;
  using Splines::LinearSpline;
  using Splines::ConstantSpline;
  using Splines::QuinticSpline;
  using Splines::Spline1D;

  using Splines::BilinearSpline;
  using Splines::BiCubicSpline;
  using Splines::BiQuinticSpline;
  using Splines::Akima2Dspline;
  using Splines::Spline2D;

  using Splines::SplineVec;
  using Splines::SplineSet;

  using Splines::SplineType1D;
  using Splines::SplineType2D;

  using Splines::quadraticRoots;
  using Splines::cubicRoots;

}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
#ifdef __clang__
#pragma clang diagnostic pop
#endif

#endif
