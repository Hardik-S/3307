#include <gtest/gtest.h>

#include "core/domain/Profile.h"

TEST(ProfileTest, XpAndStreakUpdate) {
    Profile profile("Hardik");
    profile.addXp(10);
    EXPECT_EQ(profile.xp(), 10);
    profile.updateStreak(true);
    profile.updateStreak(true);
    EXPECT_EQ(profile.streak(), 2);
    profile.updateStreak(false);
    EXPECT_EQ(profile.streak(), 0);
}

TEST(ProfileTest, UnitCompletionTracking) {
    Profile profile("Hardik");
    profile.markUnitCompleted("nepali", "u1");
    EXPECT_TRUE(profile.isUnitCompleted("nepali", "u1"));
    EXPECT_FALSE(profile.isUnitCompleted("nepali", "u2"));
    EXPECT_EQ(profile.completedUnits("nepali").size(), 1);
}
