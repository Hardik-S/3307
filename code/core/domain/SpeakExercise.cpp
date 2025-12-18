#include "SpeakExercise.h"

SpeakExercise::SpeakExercise(const QString& id, const QString& prompt, const QString& expectedKeyword)
    : Exercise(id, prompt), m_expectedKeyword(expectedKeyword) {}

QString SpeakExercise::type() const {
    return "Speak";
}

QString SpeakExercise::expectedKeyword() const {
    return m_expectedKeyword;
}
