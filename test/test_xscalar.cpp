/***************************************************************************
* Copyright (c) 2016, Johan Mabille, Sylvain Corlay and Wolf Vollprecht    *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#include "gtest/gtest.h"
#include "xtensor/xscalar.hpp"
#include "xtensor/xarray.hpp"

namespace xt
{
    TEST(xscalar, size)
    {
        // The shape of a 0-D xarray is ().  The size of the buffer is 1.
        xscalar<int> x(1);
        EXPECT_EQ(x.size(), 1);
    }

    TEST(xscalar, access)
    {
        // Calling operator() with no argument returns the wrapped value.
        xscalar<int> x(2);
        EXPECT_EQ(x(), 2);

        x() = 4;
        EXPECT_EQ(4, x());
    }

    TEST(xscalar, dimension)
    {
        // The dimension of a xscalar is 0
        xscalar<int> x(2);
        EXPECT_EQ(x.dimension(), 0);
        EXPECT_EQ(x.layout(), layout_type::any);
    }

    TEST(xscalar, iterator)
    {
        xscalar<int> x(2);
        auto xiter = x.begin();
        *xiter = 4;
        EXPECT_EQ(4, x());
        auto xiter_end = x.end();
        ++xiter;
        EXPECT_EQ(xiter, xiter_end);
        auto iter = x.begin();
        *iter = 3;
        EXPECT_EQ(3, x());
        auto iter_end = x.end();
        ++iter;
        EXPECT_EQ(iter, iter_end);
    }

    TEST(xscalar, dummy_iterator)
    {
        xscalar<int> x(2);
        auto iter = x.dummy_begin();
        auto iter_end = x.dummy_end();
        EXPECT_EQ(iter, iter_end);
        ++iter;
        EXPECT_EQ(2, *iter);
        EXPECT_EQ(iter, iter_end);
    }

    TEST(xscalar, xref)
    {
        int ref = 4;
        int x = 2;
        auto s = xref(x);
        s() = ref;
        EXPECT_EQ(ref, x);
    }

    TEST(xscalar, broadcasting)
    {
        xarray<int> a = {1, 2, 3, 4};
        xarray<int> ref = {6, 7, 8, 9};
        xarray<int> b = a + 5;
        EXPECT_EQ(ref, b);
    }
}
