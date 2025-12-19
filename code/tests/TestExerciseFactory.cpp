#include <gtest/gtest.h>

#include <QJsonArray>
#include <QJsonObject>

#include "core/domain/ExerciseFactory.h"
#include "core/domain/MCQExercise.h"
#include "core/domain/TranslateExercise.h"
#include "core/domain/TileOrderExercise.h"
#include "core/domain/ListenExercise.h"
#include "core/domain/SpeakExercise.h"

TEST(ExerciseFactoryTest, CreatesMCQWithAudio) {
    QJsonObject spec;
    spec.insert("id", "mcq-1");
    spec.insert("prompt", "Pick one");
    spec.insert("correctIndex", 1);
    spec.insert("audioPath", "assets/audio/foo.mp3");
    QJsonArray choices;
    choices.append("A");
    choices.append("B");
    spec.insert("choices", choices);

    std::unique_ptr<Exercise> exercise(ExerciseFactory::createExercise("MCQ", spec));
    ASSERT_NE(exercise, nullptr);
    EXPECT_EQ(exercise->type(), "MCQ");
    EXPECT_EQ(exercise->audioPath(), "assets/audio/foo.mp3");
    auto* mcq = dynamic_cast<MCQExercise*>(exercise.get());
    ASSERT_NE(mcq, nullptr);
    EXPECT_EQ(mcq->correctIndex(), 1);
}

TEST(ExerciseFactoryTest, CreatesTranslateWithCharacterSet) {
    QJsonObject spec;
    spec.insert("id", "tr-1");
    spec.insert("prompt", "Translate");
    spec.insert("characterSelection", true);
    QJsonArray answers;
    answers.append("नमस्ते");
    answers.append("namaste");
    spec.insert("answers", answers);
    QJsonArray chars;
    chars.append("न");
    chars.append("म");
    spec.insert("characterSet", chars);

    std::unique_ptr<Exercise> exercise(ExerciseFactory::createExercise("Translate", spec));
    ASSERT_NE(exercise, nullptr);
    auto* translate = dynamic_cast<TranslateExercise*>(exercise.get());
    ASSERT_NE(translate, nullptr);
    EXPECT_TRUE(translate->usesCharacterSelection());
    EXPECT_EQ(translate->characterSet().size(), 2);
}

TEST(ExerciseFactoryTest, CreatesTileOrder) {
    QJsonObject spec;
    spec.insert("id", "tile-1");
    spec.insert("prompt", "Order");
    QJsonArray tiles;
    tiles.append("a");
    tiles.append("b");
    spec.insert("tiles", tiles);
    QJsonArray correct;
    correct.append("a");
    correct.append("b");
    spec.insert("correctOrder", correct);

    std::unique_ptr<Exercise> exercise(ExerciseFactory::createExercise("TileOrder", spec));
    ASSERT_NE(exercise, nullptr);
    EXPECT_EQ(exercise->type(), "TileOrder");
}

TEST(ExerciseFactoryTest, CreatesListenAndSpeak) {
    QJsonObject listenSpec;
    listenSpec.insert("id", "listen-1");
    listenSpec.insert("prompt", "Listen");
    listenSpec.insert("audioPath", "assets/audio/x.mp3");
    listenSpec.insert("correctIndex", 0);
    QJsonArray choices;
    choices.append("yes");
    choices.append("no");
    listenSpec.insert("choices", choices);
    std::unique_ptr<Exercise> listen(ExerciseFactory::createExercise("Listen", listenSpec));
    ASSERT_NE(listen, nullptr);
    EXPECT_EQ(listen->type(), "Listen");

    QJsonObject speakSpec;
    speakSpec.insert("id", "speak-1");
    speakSpec.insert("prompt", "Speak");
    speakSpec.insert("expectedKeyword", "hi");
    std::unique_ptr<Exercise> speak(ExerciseFactory::createExercise("Speak", speakSpec));
    ASSERT_NE(speak, nullptr);
    EXPECT_EQ(speak->type(), "Speak");
}

TEST(ExerciseFactoryTest, UnknownTypeReturnsNull) {
    QJsonObject spec;
    std::unique_ptr<Exercise> exercise(ExerciseFactory::createExercise("Unknown", spec));
    EXPECT_EQ(exercise, nullptr);
}
