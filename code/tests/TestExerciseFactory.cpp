#include <gtest/gtest.h>

#include <QJsonArray>
#include <QJsonObject>

#include "core/domain/ExerciseFactory.h"
#include "core/domain/MCQExercise.h"

TEST(ExerciseFactoryTest, CreatesMCQExercise) {
    QJsonObject spec;
    spec.insert("id", "mcq-test");
    spec.insert("prompt", "Pick A");
    spec.insert("correctIndex", 0);
    QJsonArray choices;
    choices.append("A");
    choices.append("B");
    spec.insert("choices", choices);

    auto* exercise = ExerciseFactory::createExercise("MCQ", spec);
    ASSERT_NE(exercise, nullptr);
    EXPECT_EQ(exercise->type(), "MCQ");

    delete exercise;
}
