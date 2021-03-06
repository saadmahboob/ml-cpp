/*
 * Copyright Elasticsearch B.V. and/or licensed to Elasticsearch B.V. under one
 * or more contributor license agreements. Licensed under the Elastic License;
 * you may not use this file except in compliance with the Elastic License.
 */

#include "CMathsFuncsTest.h"

#include <maths/CMathsFuncs.h>

#include <cmath>
#include <limits>
#include <vector>

using namespace ml;

namespace {
double zero() {
    return 0.0;
}
}

void CMathsFuncsTest::testIsNan() {
    CPPUNIT_ASSERT(!maths::CMathsFuncs::isNan(0.0));
    CPPUNIT_ASSERT(!maths::CMathsFuncs::isNan(1e7));
    CPPUNIT_ASSERT(!maths::CMathsFuncs::isNan(-1e17));
    CPPUNIT_ASSERT(!maths::CMathsFuncs::isNan(std::numeric_limits<double>::max()));
    CPPUNIT_ASSERT(!maths::CMathsFuncs::isNan(-std::numeric_limits<double>::max()));
    CPPUNIT_ASSERT(!maths::CMathsFuncs::isNan(std::numeric_limits<double>::min()));
    CPPUNIT_ASSERT(!maths::CMathsFuncs::isNan(-std::numeric_limits<double>::min()));
    CPPUNIT_ASSERT(maths::CMathsFuncs::isNan(zero() / zero()));
    CPPUNIT_ASSERT(maths::CMathsFuncs::isNan(1.0 / zero() - 2.0 / zero()));
}

void CMathsFuncsTest::testIsInf() {
    CPPUNIT_ASSERT(!maths::CMathsFuncs::isInf(0.0));
    CPPUNIT_ASSERT(!maths::CMathsFuncs::isInf(1.8738e7));
    CPPUNIT_ASSERT(!maths::CMathsFuncs::isInf(-1.376e17));
    CPPUNIT_ASSERT(!maths::CMathsFuncs::isInf(std::numeric_limits<double>::max()));
    CPPUNIT_ASSERT(!maths::CMathsFuncs::isInf(-std::numeric_limits<double>::max()));
    CPPUNIT_ASSERT(!maths::CMathsFuncs::isInf(std::numeric_limits<double>::min()));
    CPPUNIT_ASSERT(!maths::CMathsFuncs::isInf(-std::numeric_limits<double>::min()));
    CPPUNIT_ASSERT(maths::CMathsFuncs::isInf(1.0 / zero()));
    CPPUNIT_ASSERT(maths::CMathsFuncs::isInf(2.0 / zero()));
    CPPUNIT_ASSERT(maths::CMathsFuncs::isInf(std::log(zero())));
    CPPUNIT_ASSERT(maths::CMathsFuncs::isInf(std::exp(1.0 / zero())));
}

void CMathsFuncsTest::testIsFinite() {
    using TDoubleVec = std::vector<double>;

    CPPUNIT_ASSERT(maths::CMathsFuncs::isFinite(0.0));
    CPPUNIT_ASSERT(maths::CMathsFuncs::isFinite(1.3e7));
    CPPUNIT_ASSERT(maths::CMathsFuncs::isFinite(-1.5368e17));
    CPPUNIT_ASSERT(maths::CMathsFuncs::isFinite(std::numeric_limits<double>::max()));
    CPPUNIT_ASSERT(maths::CMathsFuncs::isFinite(-std::numeric_limits<double>::max()));
    CPPUNIT_ASSERT(maths::CMathsFuncs::isFinite(std::numeric_limits<double>::min()));
    CPPUNIT_ASSERT(maths::CMathsFuncs::isFinite(-std::numeric_limits<double>::min()));
    CPPUNIT_ASSERT(!maths::CMathsFuncs::isFinite(1.0 / zero()));
    CPPUNIT_ASSERT(!maths::CMathsFuncs::isFinite(2.0 / zero()));
    CPPUNIT_ASSERT(!maths::CMathsFuncs::isFinite(std::log(zero())));
    CPPUNIT_ASSERT(!maths::CMathsFuncs::isFinite(zero() / zero()));
    CPPUNIT_ASSERT(!maths::CMathsFuncs::isFinite(1.0 / zero() - 2.0 / zero()));

    TDoubleVec test1;
    test1.push_back(2.0);
    test1.push_back(25.0);
    test1.push_back(-1e6);
    CPPUNIT_ASSERT(std::equal(test1.begin(), test1.end(),
                              maths::CMathsFuncs::beginFinite(test1)));

    TDoubleVec test2;
    test2.push_back(zero() / zero());
    test2.push_back(2.0);
    test2.push_back(1.0 / zero());
    test2.push_back(zero() / zero());
    test2.push_back(3.0 / zero());
    test2.push_back(25.0);
    test2.push_back(-1e6);
    test2.push_back(zero() / zero());
    CPPUNIT_ASSERT(std::equal(test1.begin(), test1.end(),
                              maths::CMathsFuncs::beginFinite(test2)));

    TDoubleVec test3;
    CPPUNIT_ASSERT(maths::CMathsFuncs::beginFinite(test3) ==
                   maths::CMathsFuncs::endFinite(test3));

    TDoubleVec test4;
    test4.push_back(zero() / zero());
    test4.push_back(1.0 / zero());
    test4.push_back(zero() / zero());
    CPPUNIT_ASSERT(maths::CMathsFuncs::beginFinite(test4) ==
                   maths::CMathsFuncs::endFinite(test4));
}

void CMathsFuncsTest::testFpStatus() {
    CPPUNIT_ASSERT_EQUAL(maths_t::E_FpNoErrors, maths::CMathsFuncs::fpStatus(3.8));
    CPPUNIT_ASSERT_EQUAL(maths_t::E_FpOverflowed,
                         maths::CMathsFuncs::fpStatus(1.0 / zero()));
    CPPUNIT_ASSERT_EQUAL(maths_t::E_FpFailed,
                         maths::CMathsFuncs::fpStatus(zero() / zero()));
}

CppUnit::Test* CMathsFuncsTest::suite() {
    CppUnit::TestSuite* suiteOfTests = new CppUnit::TestSuite("CMathsFuncsTest");

    suiteOfTests->addTest(new CppUnit::TestCaller<CMathsFuncsTest>(
        "CMathsFuncsTest::testIsNan", &CMathsFuncsTest::testIsNan));
    suiteOfTests->addTest(new CppUnit::TestCaller<CMathsFuncsTest>(
        "CMathsFuncsTest::testIsInf", &CMathsFuncsTest::testIsInf));
    suiteOfTests->addTest(new CppUnit::TestCaller<CMathsFuncsTest>(
        "CMathsFuncsTest::testIsFinite", &CMathsFuncsTest::testIsFinite));
    suiteOfTests->addTest(new CppUnit::TestCaller<CMathsFuncsTest>(
        "CMathsFuncsTest::testFpStatus", &CMathsFuncsTest::testFpStatus));

    return suiteOfTests;
}
