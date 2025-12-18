#include "ExerciseFactory.h"

#include <QJsonArray>

#include "ListenExercise.h"
#include "MCQExercise.h"
#include "SpeakExercise.h"
#include "TileOrderExercise.h"
#include "TranslateExercise.h"

Exercise* ExerciseFactory::createExercise(const QString& type, const QJsonObject& spec) {
    if (type == "MCQ") {
        return createMCQ(spec);
    }
    if (type == "Translate") {
        return createTranslate(spec);
    }
    if (type == "TileOrder") {
        return createTileOrder(spec);
    }
    if (type == "Listen") {
        return createListen(spec);
    }
    if (type == "Speak") {
        return createSpeak(spec);
    }
    return nullptr;
}

Exercise* ExerciseFactory::createMCQ(const QJsonObject& spec) {
    const QString id = spec.value("id").toString();
    const QString prompt = spec.value("prompt").toString();
    const int correctIndex = spec.value("correctIndex").toInt();
    QStringList choices;
    for (const auto& value : spec.value("choices").toArray()) {
        choices.append(value.toString());
    }
    return new MCQExercise(id, prompt, choices, correctIndex);
}

Exercise* ExerciseFactory::createTranslate(const QJsonObject& spec) {
    const QString id = spec.value("id").toString();
    const QString prompt = spec.value("prompt").toString();
    const bool characterSelection = spec.value("characterSelection").toBool(false);
    QStringList answers;
    for (const auto& value : spec.value("answers").toArray()) {
        answers.append(value.toString());
    }
    return new TranslateExercise(id, prompt, answers, characterSelection);
}

Exercise* ExerciseFactory::createTileOrder(const QJsonObject& spec) {
    const QString id = spec.value("id").toString();
    const QString prompt = spec.value("prompt").toString();
    QStringList tiles;
    for (const auto& value : spec.value("tiles").toArray()) {
        tiles.append(value.toString());
    }
    QStringList correctOrder;
    for (const auto& value : spec.value("correctOrder").toArray()) {
        correctOrder.append(value.toString());
    }
    return new TileOrderExercise(id, prompt, tiles, correctOrder);
}

Exercise* ExerciseFactory::createListen(const QJsonObject& spec) {
    const QString id = spec.value("id").toString();
    const QString prompt = spec.value("prompt").toString();
    const QString audioPath = spec.value("audioPath").toString();
    const int correctIndex = spec.value("correctIndex").toInt();
    QStringList choices;
    for (const auto& value : spec.value("choices").toArray()) {
        choices.append(value.toString());
    }
    return new ListenExercise(id, prompt, audioPath, choices, correctIndex);
}

Exercise* ExerciseFactory::createSpeak(const QJsonObject& spec) {
    const QString id = spec.value("id").toString();
    const QString prompt = spec.value("prompt").toString();
    const QString expectedKeyword = spec.value("expectedKeyword").toString();
    return new SpeakExercise(id, prompt, expectedKeyword);
}
