#include <gtest/gtest.h>

#include "core/domain/TranslateExercise.h"
#include "core/domain/TranslateGrader.h"

TEST(TranslateGraderTest, AcceptsMatchingAnswer) {
    TranslateExercise exercise("t1", "Translate", {"hello", "hi"}, false);
    TranslateGrader grader;

    Result result = grader.grade(" Hello ", &exercise);
    EXPECT_TRUE(result.correct);
}
