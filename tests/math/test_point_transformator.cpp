#include "math/PointTransformator.h"
#include "gtest/gtest.h"

TEST(PointTransformatorTest, Positive) {
    PointTransformator<int> trans;
    trans.init(1024,768);
    int x, y;
    
    trans.LB2LT(200,100,&x,&y);

    EXPECT_EQ(200, x);
    EXPECT_EQ(668, y);

    trans.LT2LB(200,100,&x,&y);

    EXPECT_EQ(200, x);
    EXPECT_EQ(668, y);
}
