// Copyright (C) 2016 Erik Hofman - erik@ehofman.com
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//

#ifndef __SIMD_H__
#define __SIMD_H__	1

# ifdef __SSE__
#  include <xmmintrin.h>
# endif

template<typename T>
class simd4_t
{
public:
    ~simd4_t() {}
};

template<>
class simd4_t<float>
{
private:
   typedef float  __vec4_t[4];

# ifdef __SSE__
    union {
        __m128 v4;
        __vec4_t vec;
    };
# else
    __vec4_t vec;
# endif

public:
    simd4_t() {}
    simd4_t(float f)
    {
        vec[0] = vec[1] = vec[2] = vec[3] = f;
    }
    simd4_t(const __vec4_t& v)
    {
        vec[0] = v[0];
        vec[1] = v[1];
        vec[2] = v[2];
        vec[3] = v[3];
    }

    inline float (&ptr(void))[4] {
        return vec;
    }

    inline const float (&ptr(void) const)[4] {
        return vec;
    }

    inline simd4_t& operator=(float f)
    {
        vec[0] = vec[1] = vec[2] = vec[3] = f;
        return *this;
    }

    inline simd4_t& operator=(const __vec4_t& v)
    {
        vec[0] = v[0];
        vec[1] = v[1];
        vec[2] = v[2];
        vec[3] = v[3];
        return *this;
    }

    inline simd4_t& operator=(const simd4_t& v)
    {
        vec[0] = v[0];
        vec[1] = v[1];
        vec[2] = v[2];
        vec[3] = v[3];
        return *this;
    }

    inline simd4_t operator-()
    {
        simd4_t r(0.0f);
        r -= vec;
        return r;
    }

    inline simd4_t operator+(float f)
    {
        simd4_t r(vec);
        r += f;
        return r;
    }

    inline simd4_t operator-(float f)
    {
        simd4_t r(vec);
        r -= f;
        return r;
    }

    inline simd4_t operator*(float f)
    {
        simd4_t r(vec);
        r *= f;
        return r;
    }

    inline simd4_t operator/(float f)
    {
        simd4_t r(vec);
        r /= f;
        return r;
    }

    inline simd4_t& operator +=(float f)
    {
# ifdef __SSE__
        v4 += f;
# else
        vec[0] += f;
        vec[1] += f;
        vec[2] += f;
        vec[3] += f;
# endif
        return *this;
    }

    inline simd4_t& operator -=(float f)
    {
# ifdef __SSE__
        v4 -= f;
# else
        vec[0] -= f;
        vec[1] -= f;
        vec[2] -= f;
        vec[3] -= f;
# endif
        return *this;
    }

    inline simd4_t& operator *=(float f)
    {
# ifdef __SSE__
        v4 *= f;
# else
        vec[0] *= f;
        vec[1] *= f;
        vec[2] *= f;
        vec[3] *= f;
# endif
        return *this;
    }

    inline simd4_t& operator /=(float f)
    {
# ifdef __SSE__
        v4 /= f;
# else
        vec[0] /= f;
        vec[1] /= f;
        vec[2] /= f;
        vec[3] /= f;
#endif
        return *this;
    }

    inline simd4_t& operator +=(__vec4_t v)
    {
        vec[0] += v[0];
        vec[1] += v[1];
        vec[2] += v[2];
        vec[3] += v[3];
        return *this;
    }

    inline simd4_t& operator -=(__vec4_t v)
    {
        vec[0] -= v[0];
        vec[1] -= v[1];
        vec[2] -= v[2];
        vec[3] -= v[3];
        return *this;
    }

    inline simd4_t& operator *=(__vec4_t v)
    {
        vec[0] *= v[0];
        vec[1] *= v[1];
        vec[2] *= v[2];
        vec[3] *= v[3];
        return *this;
    }

    inline simd4_t& operator /=(__vec4_t v)
    {
        vec[0] /= v[0];
        vec[1] /= v[1];
        vec[2] /= v[2];
        vec[3] /= v[3];
        return *this;
    }

    inline operator const float*() const {
        return vec;
    }

    inline operator float*() {
        return vec;
    }
};

template<>
class simd4_t<double>
{
private:
   typedef double  __vec4_t[4];

# ifdef __SSE__
    union {
        __m128d v4;
        __vec4_t vec;
    };
# else
    __vec4_t vec;
# endif

public:
    simd4_t() {}
    simd4_t(double f)
    {
        vec[0] = vec[1] = vec[2] = vec[3] = f;
    }
    simd4_t(const __vec4_t& v)
    {
        vec[0] = v[0];
        vec[1] = v[1];
        vec[2] = v[2];
        vec[3] = v[3];
    }

    inline double (&ptr(void))[4] {
        return vec;
    }

    inline const double (&ptr(void) const)[4] {
        return vec;
    }

    inline simd4_t& operator=(double f)
    {
        vec[0] = vec[1] = vec[2] = vec[3] = f;
        return *this;
    }

    inline simd4_t& operator=(const __vec4_t& v)
    {
        vec[0] = v[0];
        vec[1] = v[1];
        vec[2] = v[2];
        vec[3] = v[3];
        return *this;
    }

    inline simd4_t& operator=(const simd4_t& v)
    {
        simd4_t(r);
        vec[0] = v[0];
        vec[1] = v[1];
        vec[2] = v[2];
        vec[3] = v[3];
        return *this;
    }

    inline simd4_t operator-()
    {
        simd4_t r(0.0f);
        r -= vec;
        return r;
    }

    inline simd4_t operator+(double f)
    {
        simd4_t r(vec);
        r += f;
        return r;
    }

    inline simd4_t operator-(double f)
    {
        simd4_t r(vec);
        r -= f;
        return r;
    }

    inline simd4_t operator*(double f)
    {
        simd4_t r(vec);
        r *= f;
        return r;
    }

    inline simd4_t operator/(double f)
    {
        simd4_t r(vec);
        r /= f;
        return r;
    }

    inline simd4_t& operator +=(double f)
    {
# ifdef __SSE__
        v4 += f;
# else
        vec[0] += f;
        vec[1] += f;
        vec[2] += f;
        vec[3] += f;
# endif
        return *this;
    }

    inline simd4_t& operator -=(double f)
    {
# ifdef __SSE__
        v4 -= f;
# else
        vec[0] -= f;
        vec[1] -= f;
        vec[2] -= f;
        vec[3] -= f;
# endif
        return *this;
    }

    inline simd4_t& operator *=(double f)
    {
# ifdef __SSE__
        v4 *= f;
# else
        vec[0] *= f;
        vec[1] *= f;
        vec[2] *= f;
        vec[3] *= f;
# endif
        return *this;
    }

    inline simd4_t& operator /=(double f)
    {
# ifdef __SSE__
        v4 /= f;
# else
        vec[0] /= f;
        vec[1] /= f;
        vec[2] /= f;
        vec[3] /= f;
#endif
        return *this;
    }

    inline simd4_t& operator +=(__vec4_t v)
    {
        vec[0] += v[0];
        vec[1] += v[1];
        vec[2] += v[2];
        vec[3] += v[3];
        return *this;
    }

    inline simd4_t& operator -=(__vec4_t v)
    {
        vec[0] -= v[0];
        vec[1] -= v[1];
        vec[2] -= v[2];
        vec[3] -= v[3];
        return *this;
    }

    inline simd4_t& operator *=(__vec4_t v)
    {
        vec[0] *= v[0];
        vec[1] *= v[1];
        vec[2] *= v[2];
        vec[3] *= v[3];
        return *this;
    }

    inline simd4_t& operator /=(__vec4_t v)
    {
        vec[0] /= v[0];
        vec[1] /= v[1];
        vec[2] /= v[2];
        vec[3] /= v[3];
        return *this;
    }

    inline operator const double*(void) const {
        return vec;
    }

    inline operator double*(void) {
        return vec;
    }
};

template<>
class simd4_t<int>
{
private:
   typedef int  __vec4_t[4];

# ifdef __SSE__
    union {
        __m128i v4;
        __vec4_t vec;
    };
# else
    __vec4_t vec;
# endif

public:
    simd4_t() {}
    simd4_t(int i)
    {
        vec[0] = vec[1] = vec[2] = vec[3] = i;
    }
    simd4_t(const __vec4_t& v)
    {
        vec[0] = v[0];
        vec[1] = v[1];
        vec[2] = v[2];
        vec[3] = v[3];
    }

    inline int (&ptr(void))[4] {
        return vec;
    }

    inline const int (&ptr(void) const)[4] {
        return vec;
    }

    inline simd4_t& operator=(int i)
    {
        vec[0] = vec[1] = vec[2] = vec[3] = i;
        return *this;
    }

    inline simd4_t& operator=(const __vec4_t& v)
    {
        vec[0] = v[0];
        vec[1] = v[1];
        vec[2] = v[2];
        vec[3] = v[3];
        return *this;
    }

    inline simd4_t& operator=(const simd4_t& v)
    {
        vec[0] = v[0];
        vec[1] = v[1];
        vec[2] = v[2];
        vec[3] = v[3];
        return *this;
    }

    inline simd4_t operator-()
    {
        simd4_t r(0.0f);
        r -= vec;
        return r;
    }

    inline simd4_t operator+(int i)
    {
        simd4_t r(vec);
        r += i;
        return r;
    }

    inline simd4_t operator-(int i)
    {
        simd4_t r(vec);
        r -= i;
        return r;
    }

    inline simd4_t operator*(int i)
    {
        simd4_t r(vec);
        r *= i;
        return r;
    }

    inline simd4_t operator/(int i)
    {
        simd4_t r(vec);
        r /= i;
        return r;
    }

    inline simd4_t& operator +=(int i)
    {
# ifdef __SSE__
        v4 += i;
# else
        vec[0] += i;
        vec[1] += i;
        vec[2] += i;
        vec[3] += i;
# endif
        return *this;
    }

    inline simd4_t& operator -=(int i)
    {
# ifdef __SSE__
        v4 -= i;
# else
        vec[0] -= i;
        vec[1] -= i;
        vec[2] -= i;
        vec[3] -= i;
# endif
        return *this;
    }

    inline simd4_t& operator *=(int i)
    {
# ifdef __SSE__
        v4 *= i;
# else
        vec[0] *= i;
        vec[1] *= i;
        vec[2] *= i;
        vec[3] *= i;
# endif
        return *this;
    }

    inline simd4_t& operator /=(int i)
    {
# ifdef __SSE__
        v4 /= i;
# else
        vec[0] /= i;
        vec[1] /= i;
        vec[2] /= i;
        vec[3] /= i;
#endif
        return *this;
    }

    inline simd4_t& operator +=(__vec4_t v)
    {
        vec[0] += v[0];
        vec[1] += v[1];
        vec[2] += v[2];
        vec[3] += v[3];
        return *this;
    }

    inline simd4_t& operator -=(__vec4_t v)
    {
        vec[0] -= v[0];
        vec[1] -= v[1];
        vec[2] -= v[2];
        vec[3] -= v[3];
        return *this;
    }

    inline simd4_t& operator *=(__vec4_t v)
    {
        vec[0] *= v[0];
        vec[1] *= v[1];
        vec[2] *= v[2];
        vec[3] *= v[3];
        return *this;
    }

    inline simd4_t& operator /=(__vec4_t v)
    {
        vec[0] /= v[0];
        vec[1] /= v[1];
        vec[2] /= v[2];
        vec[3] /= v[3];
        return *this;
    }

    inline operator const int*() const {
        return vec;
    }

    inline operator int*() {
        return vec;
    }
};

#endif /* __SIMD_H__ */
