#pragma once

#include <QJsonObject>

class Exercise;

// Creational Pattern: Factory for exercise instantiation.
class ExerciseFactory {
public:
    static Exercise* createExercise(const QString& type, const QJsonObject& spec);

private:
    static Exercise* createMCQ(const QJsonObject& spec);
    static Exercise* createTranslate(const QJsonObject& spec);
    static Exercise* createTileOrder(const QJsonObject& spec);
    static Exercise* createListen(const QJsonObject& spec);
    static Exercise* createSpeak(const QJsonObject& spec);
};
