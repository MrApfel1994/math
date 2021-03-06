#pragma once

#include "vec4.hpp"

namespace math {
    class mat3;
    class quat;

    class mat4 {
    public:
        union {
            float16 vec_;
            vec4 v[4];
        };

        mat4(e_noinit) { assert(is_aligned(this, alignment)); }
        mat4() : mat4(1.0f) {}
        explicit mat4(float v) : mat4(noinit) { mat4_init1(vec_, v); }
        mat4(float v00, float v01, float v02, float v03,
             float v10, float v11, float v12, float v13,
             float v20, float v21, float v22, float v23,
             float v30, float v31, float v32, float v33) : mat4(noinit) {
            mat4_init16(vec_, v00, v01, v02, v03, v10, v11, v12, v13, v20, v21, v22, v23, v30, v31, v32, v33);
        }
        mat4(const vec4 &v0, const vec4 &v1, const vec4 &v2, const vec4 &v3) : mat4(noinit) {
            mat4_init4(vec_, v0.vec_, v1.vec_, v2.vec_, v3.vec_);
        }
        mat4(const float16 &v) : mat4(noinit) { vec_ = v; }
        mat4(const float9 &v) : mat4(noinit) {
            mat4_init16(vec_,
                        v.comp3[0][0], v.comp3[0][1], v.comp3[0][2], 0,
                        v.comp3[1][0], v.comp3[1][1], v.comp3[1][2], 0,
                        v.comp3[2][0], v.comp3[2][1], v.comp3[2][2], 0,
                        0, 0, 0, 1);
        }
        mat4(const mat3 &v);

        vec4 &operator[] (int i) { return v[i]; }
        vec4 operator[] (int i) const { return v[i]; }

        mat4 &operator++();
        mat4 operator++(int);
        mat4 &operator--();
        mat4 operator--(int);

        mat4 &operator+=(const mat4 &rhs);
        mat4 &operator-=(const mat4 &rhs);
        mat4 &operator*=(const mat4 &rhs);
        mat4 &operator/=(const mat4 &rhs);

        mat4 operator-() const;

        static const size_t alignment = alignment_m256;
        using scalar_type = float;
    };

    inline bool operator==(const mat4 &m1, const mat4 &m2) { return mat4_eq_mat4(m1.vec_, m2.vec_); }
    inline bool operator!=(const mat4 &m1, const mat4 &m2) { return !operator==(m1, m2); }

    inline mat4 operator+(const mat4 &m1, const mat4 &m2) { return mat4(mat4_add_mat4(m1.vec_, m2.vec_)); }
    inline mat4 operator-(const mat4 &m1, const mat4 &m2) { return mat4(mat4_sub_mat4(m1.vec_, m2.vec_)); }
    inline mat4 operator*(const mat4 &m1, const mat4 &m2) { return mat4(mat4_mul_mat4(m1.vec_, m2.vec_)); }
    inline mat4 operator/(const mat4 &m1, const mat4 &m2) { return mat4(mat4_div_mat4(m1.vec_, m2.vec_)); }

    inline mat4 operator*(const mat4 &m1, float v1) { return mat4_mul_float(m1.vec_, v1); }
    inline mat4 operator*(float v1, const mat4 &m1) { return operator*(m1, v1); }
    inline mat4 operator/(const mat4 &m1, float v1) { return mat4_div_float(m1.vec_, v1); }

    inline mat4 matrix_comp_mult(const mat4 &m1, const mat4 &m2) { return mat4_comp_mul(m1.vec_, m2.vec_); }

    inline mat4 &mat4::operator++() { (*this) = (*this) + mat4(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1); return *this; }
    inline mat4 mat4::operator++(int) { mat4 temp = (*this); ++(*this); return temp; }
    inline mat4 &mat4::operator--() { (*this) = (*this) - mat4(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1); return *this; }
    inline mat4 mat4::operator--(int) { mat4 temp = (*this); --(*this); return temp; }

    inline mat4 &mat4::operator+=(const mat4 &rhs) { (*this) = (*this) + rhs; return *this; }
    inline mat4 &mat4::operator-=(const mat4 &rhs) { (*this) = (*this) - rhs; return *this; }
    inline mat4 &mat4::operator*=(const mat4 &rhs) { (*this) = (*this) * rhs; return *this; }
    inline mat4 &mat4::operator/=(const mat4 &rhs) { (*this) = (*this) / rhs; return *this; }

    inline mat4 mat4::operator-() const { return matrix_comp_mult((*this), mat4(-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1)); }

    inline mat4 make_mat4(const float v[16]) {
        return mat4(v[0], v[1], v[2], v[3],
                    v[4], v[5], v[6], v[7],
                    v[8], v[9], v[10], v[11],
                    v[12], v[13], v[14], v[15]);
    }

    inline const float *value_ptr(const mat4 &m) {
        return &m.vec_.comp[0];
    }
}

#include "mat3.hpp"
#include "quat.hpp"

namespace math {
    inline mat4::mat4(const mat3 &m) : mat4(m.vec_) {}

    inline quat to_quat(const mat4 &m) { return quat(mat4_to_quat(m.vec_)); }
}