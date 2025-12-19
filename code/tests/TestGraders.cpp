#include <gtest/gtest.h>

#include "core/domain/MCQExercise.h"
#include "core/domain/MCQGrader.h"
#include "core/domain/TranslateExercise.h"
#include "core/domain/TranslateGrader.h"
#include "core/domain/CharacterSelectionGrader.h"
#include "core/domain/TileOrderExercise.h"
#include "core/domain/TileOrderGrader.h"
#include "core/domain/ListenExercise.h"
#include "core/domain/ListenGrader.h"
#include "core/domain/SpeakExercise.h"
#include "core/domain/SpeakGrader.h"
#include "core/domain/StubSpeechEvaluator.h"

TEST(GradersTest, MCQCorrectness) {
    MCQExercise ex("id", "prompt", {"A", "B", "C"}, 1);
    MCQGrader grader;
    auto resCorrect = grader.grade("2", &ex);
    EXPECT_TRUE(resCorrect.correct);
    auto resWrong = grader.grade("1", &ex);
    EXPECT_FALSE(resWrong.correct);
}

TEST(GradersTest, TranslateExactAndTrimLower) {
    TranslateExercise ex("id", "prompt", {"Namaste", "Hello"}, false);
    TranslateGrader grader;
    auto res = grader.grade(" namaste  ", &ex);
    EXPECT_TRUE(res.correct);
    auto resWrong = grader.grade("bye", &ex);
    EXPECT_FALSE(resWrong.correct);
}

TEST(GradersTest, CharacterSelectionUsesExact) {
    TranslateExercise ex("id", "prompt", {"नमस्ते"}, true);
    CharacterSelectionGrader grader;
    auto res = grader.grade("नमस्ते", &ex);
    EXPECT_TRUE(res.correct);
    auto resWrong = grader.grade("नम स ते", &ex);
    EXPECT_FALSE(resWrong.correct);
}

TEST(GradersTest, TileOrderTrims) {
    TileOrderExercise ex("id", "prompt", {"a", "b", "c"}, {"a", "b", "c"});
    TileOrderGrader grader;
    auto res = grader.grade("a, b, c", &ex);
    EXPECT_TRUE(res.correct);
    auto resWrong = grader.grade("b,a,c", &ex);
    EXPECT_FALSE(resWrong.correct);
}

TEST(GradersTest, ListenUsesIndex) {
    ListenExercise ex("id", "prompt", "audio", {"A", "B"}, 0);
    ListenGrader grader;
    auto res = grader.grade("1", &ex);
    EXPECT_TRUE(res.correct);
    auto resWrong = grader.grade("2", &ex);
    EXPECT_FALSE(resWrong.correct);
}

TEST(GradersTest, SpeakStubKeywordBias) {
    SpeakExercise ex("id", "prompt", "hello");
    StubSpeechEvaluator eval;
    SpeakGrader grader(eval);
    auto res = grader.grade("I said hello", &ex);
    EXPECT_TRUE(res.score >= 70);
}
