#include "test_assert.h"

#include <iostream>
#include <random>

#include "../math.hpp"

void test_dvec4(math::e_arch arch, unsigned seed) {
    using namespace math;

    init(arch);

    const int NUM_REPEATS = 1000;
    std::mt19937 gen(seed);
    std::uniform_real_distribution<float> dist(-1000000, 1000000);

    std::cout << "\t" << math::arch_name[arch] << " ...";

    // basic usage
    for (int i = 0; i < NUM_REPEATS; i++) {
        double r1 = dist(gen), r2 = dist(gen), r3 = dist(gen), r4 = dist(gen), r5 = dist(gen), r6 = dist(gen);

        dvec4 v1, v2(r1), v3(r2, r3, r4, r5);

        assert(v2[0] == Approx(r1));
        assert(v2[1] == Approx(r1));
        assert(v2[2] == Approx(r1));
        assert(v2[3] == Approx(r1));

        v2[0] = v2[1] = v2[2] = v2[3] = r6;

        assert(v1[0] == Approx(0));
        assert(v1[1] == Approx(0));
        assert(v1[2] == Approx(0));
        assert(v1[3] == Approx(0));
        assert(v2[0] == Approx(r6));
        assert(v2[1] == Approx(r6));
        assert(v2[2] == Approx(r6));
        assert(v2[3] == Approx(r6));
        assert(v3[0] == Approx(r2));
        assert(v3[1] == Approx(r3));
        assert(v3[2] == Approx(r4));
        assert(v3[3] == Approx(r5));
        assert(v3.x == Approx(r2));
        assert(v3.y == Approx(r3));
        assert(v3.z == Approx(r4));
        assert(v3.w == Approx(r5));
        assert(v3.r == Approx(r2));
        assert(v3.g == Approx(r3));
        assert(v3.b == Approx(r4));
        assert(v3.a == Approx(r5));
        assert(v3.s == Approx(r2));
        assert(v3.t == Approx(r3));
        assert(v3.p == Approx(r4));
        assert(v3.q == Approx(r5));

        dvec4 v4 = v1 + v2, v5 = v2 + v3;

        assert(v4[0] == Approx(r6));
        assert(v4[1] == Approx(r6));
        assert(v4[2] == Approx(r6));
        assert(v4[3] == Approx(r6));
        assert(v5[0] == Approx(r6 + r2));
        assert(v5[1] == Approx(r6 + r3));
        assert(v5[2] == Approx(r6 + r4));
        assert(v5[3] == Approx(r6 + r5));

        dvec4 v6 = v1 - v2, v7 = v2 - v3;

        assert(v6[0] == Approx(-r6));
        assert(v6[1] == Approx(-r6));
        assert(v6[2] == Approx(-r6));
        assert(v6[3] == Approx(-r6));
        assert(v7[0] == Approx(r6 - r2));
        assert(v7[1] == Approx(r6 - r3));
        assert(v7[2] == Approx(r6 - r4));
        assert(v7[3] == Approx(r6 - r5));

        dvec4 v8 = v1 * v2, v9 = v2 * v3;

        assert(v8[0] == Approx(0));
        assert(v8[1] == Approx(0));
        assert(v8[2] == Approx(0));
        assert(v8[3] == Approx(0));
        assert(v9[0] == Approx(r6 * r2));
        assert(v9[1] == Approx(r6 * r3));
        assert(v9[2] == Approx(r6 * r4));
        assert(v9[3] == Approx(r6 * r5));

        dvec4 v10 = v1 / v2, v11 = v2 / v3;

        assert(v10[0] == Approx(0));
        assert(v10[1] == Approx(0));
        assert(v10[2] == Approx(0));
        assert(v10[3] == Approx(0));
        assert(v11[0] == Approx(r6 / r2));
        assert(v11[1] == Approx(r6 / r3));
        assert(v11[2] == Approx(r6 / r4));
        assert(v11[3] == Approx(r6 / r5));
    }

    // additional constructors
    for (int i = 0; i < NUM_REPEATS; i++) {
        double r1 = dist(gen), r2 = dist(gen), r3 = dist(gen), r4 = dist(gen), r5 = dist(gen), r6 = dist(gen),
               r7 = dist(gen), r8 = dist(gen), r9 = dist(gen), r10 = dist(gen), r11 = dist(gen), r12 = dist(gen),
               r13 = dist(gen), r14 = dist(gen), r15 = dist(gen);

        dvec2 v0 = { r1, r2 }, v1 = { r3, r4 };
        dvec3 v2 = { r5, r6, r7 };
        dvec4 v3 = { v0, v1 }, v4 = { v0, r8, r9 }, v5 = { r10, v0, r11 }, v6 = { r12, r13, v1 },
              v7 = { v2, r14 }, v8 = { r15, v2 }, v9(v3), v10 = v3;

        assert(v3 == Approx4(r1, r2, r3, r4));
        assert(v4 == Approx4(r1, r2, r8, r9));
        assert(v5 == Approx4(r10, r1, r2, r11));
        assert(v6 == Approx4(r12, r13, r3, r4));
        assert(v7 == Approx4(r5, r6, r7, r14));
        assert(v8 == Approx4(r15, r5, r6, r7));
        assert(v9 == Approx4(r1, r2, r3, r4));
        assert(v10 == Approx4(r1, r2, r3, r4));
    }

    // additional operators
    for (int i = 0; i < NUM_REPEATS; i++) {
        double r1 = dist(gen), r2 = dist(gen), r3 = dist(gen), r4 = dist(gen), r5 = dist(gen), r6 = dist(gen),
               r7 = dist(gen), r8 = dist(gen), r9 = dist(gen), r10 = dist(gen), r11 = dist(gen), r12 = dist(gen),
               r13 = dist(gen), r14 = dist(gen), r15 = dist(gen), r16 = dist(gen);

        dvec4 v0 = { r1, r2, r3, r4 }, v1 = { r1, r2, r3, r4 }, v2 = { r5, r6, r7, r8 }, v3 = { r5, r6, r7, r8 };

        dvec4 v4 = v0++, v5 = ++v1;

        assert(v0 == Approx4(r1 + 1, r2 + 1, r3 + 1, r4 + 1));
        assert(v1 == Approx4(r1 + 1, r2 + 1, r3 + 1, r4 + 1));
        assert(v4 == Approx4(r1, r2, r3, r4));
        assert(v5 == Approx4(r1 + 1, r2 + 1, r3 + 1, r4 + 1));

        dvec4 v6 = v2--, v7 = --v3;

        assert(v2 == Approx4(r5 - 1, r6 - 1, r7 - 1, r8 - 1));
        assert(v3 == Approx4(r5 - 1, r6 - 1, r7 - 1, r8 - 1));
        assert(v6 == Approx4(r5, r6, r7, r8));
        assert(v7 == Approx4(r5 - 1, r6 - 1, r7 - 1, r8 - 1));

        dvec4 v8 = { r9, r10, r11, r12 }, v9 = { r9, r10, r11, r12 }, v10 = { r9, r10, r11, r12 }, v11 = { r9, r10, r11, r12 };

        v8 += dvec4{ r13, r14, r15, r16 };
        v9 -= dvec4{ r13, r14, r15, r16 };
        v10 *= dvec4{ r13, r14, r15, r16 };
        v11 /= dvec4{ r13, r14, r15, r16 };

        assert(v8 == Approx4(r9 + r13, r10 + r14, r11 + r15, r12 + r16));
        assert(v9 == Approx4(r9 - r13, r10 - r14, r11 - r15, r12 - r16));
        assert(v10 == Approx4(r9 * r13, r10 * r14, r11 * r15, r12 * r16));
        assert(v11 == Approx4(r9 / r13, r10 / r14, r11 / r15, r12 / r16));

        dvec4 v12 = { r1, r2, r3, r4 };
        v12 = -v12;

        assert(v12 == Approx4(-r1, -r2, -r3, -r4));

        dvec4 v13 = v12;

        assert(v12 == v13);
        assert(v11 != v13);

        dvec4 v14 = { r1, r2, r3, r4 };

        v14[0] += 1;
        v14[1] -= 1;
        v14[2] *= 2;
        v14[3] /= 2;

        assert(v14 == Approx4(r1 + 1, r2 - 1, r3 * 2, r4 / 2));
    }

    // arithmetics with deref
    for (int i = 0; i < NUM_REPEATS; i++) {
        double r1 = dist(gen), r2 = dist(gen), r3 = dist(gen), r4 = dist(gen), r5 = dist(gen);

        dvec4 vv{ r5, r5, r5, r5 };

        double f1 = r1;
        dvec2 v1 = { r1, r2 };
        dvec3 v2 = { r1, r2, r3 };
        dvec4 v3 = { r1, r2, r3, r4 };
        //dmat2 m1;
        //dmat3 m2;
        //dmat4 m3;

        f1 = f1 * vv[0];
        v1 = v1 * vv[0];
        v2 = v2 * vv[0];
        v3 = v3 * vv[0];
        //m1 = m1 * vv[0];
        //m2 = m2 * vv[0];
        //m3 = m3 * vv[0];

        assert(f1 == Approx(r1 * r5));
        assert(v1 == Approx2(r1 * r5, r2 * r5));
        assert(v2 == Approx3(r1 * r5, r2 * r5, r3 * r5));
        assert(v3 == Approx4(r1 * r5, r2 * r5, r3 * r5, r4 * r5));

        /*assert(m1[0] == Approx2(r5, 0));
        assert(m1[1] == Approx2(0, r5));
        assert(m2[0] == Approx3(r5, 0, 0));
        assert(m2[1] == Approx3(0, r5, 0));
        assert(m2[2] == Approx3(0, 0, r5));
        assert(m3[0] == Approx4(r5, 0, 0, 0));
        assert(m3[1] == Approx4(0, r5, 0, 0));
        assert(m3[2] == Approx4(0, 0, r5, 0));
        assert(m3[3] == Approx4(0, 0, 0, r5));*/
    }

    std::cout << "OK" << std::endl;
}

void test_dvec4() {
    std::random_device rd;
    auto seed = rd();

    std::cout << "test_dvec4 (seed " << seed << ")" << std::endl;

    test_dvec4(math::Scalar, seed);
#ifndef __arm__
    test_dvec4(math::SSE2, seed);
    test_dvec4(math::SSE3, seed);
    test_dvec4(math::SSE4_1, seed);
    test_dvec4(math::AVX, seed);
#else
    test_dvec4(math::NEON, seed);
#endif
}
