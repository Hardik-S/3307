#include <gtest/gtest.h>

#include <QDateTime>

#include "core/domain/SRSScheduler.h"

TEST(SRSSchedulerTest, CalculatesNextReview) {
    SRSScheduler scheduler;
    QDateTime start(QDate(2025, 1, 1), QTime(10, 0));

    EXPECT_EQ(scheduler.nextReview(start, Difficulty::Easy), start.addDays(2));
    EXPECT_EQ(scheduler.nextReview(start, Difficulty::Medium), start.addDays(1));
    EXPECT_EQ(scheduler.nextReview(start, Difficulty::Hard), start.addSecs(6 * 60 * 60));
}
