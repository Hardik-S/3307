#include "TranslateExercise.h"

TranslateExercise::TranslateExercise(const QString& id, const QString& prompt, const QStringList& acceptableAnswers, bool characterSelection)
    : Exercise(id, prompt), m_acceptableAnswers(acceptableAnswers), m_characterSelection(characterSelection) {}

QString TranslateExercise::type() const {
    return "Translate";
}

QStringList TranslateExercise::acceptableAnswers() const {
    return m_acceptableAnswers;
}

QString TranslateExercise::correctAnswer() const {
    return m_acceptableAnswers.isEmpty() ? QString() : m_acceptableAnswers.first();
}

bool TranslateExercise::usesCharacterSelection() const {
    return m_characterSelection;
}
