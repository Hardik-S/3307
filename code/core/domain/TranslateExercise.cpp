#include "TranslateExercise.h"

TranslateExercise::TranslateExercise(const QString& id, const QString& prompt, const QStringList& acceptableAnswers, bool characterSelection,
    const QStringList& characterSet, const QString& audioPath)
    : Exercise(id, prompt),
      m_acceptableAnswers(acceptableAnswers),
      m_characterSelection(characterSelection),
      m_characterSet(characterSet),
      m_audioPath(audioPath) {}

QString TranslateExercise::type() const {
    return "Translate";
}

QStringList TranslateExercise::acceptableAnswers() const {
    return m_acceptableAnswers;
}

QStringList TranslateExercise::characterSet() const {
    return m_characterSet;
}

QString TranslateExercise::correctAnswer() const {
    return m_acceptableAnswers.isEmpty() ? QString() : m_acceptableAnswers.first();
}

bool TranslateExercise::usesCharacterSelection() const {
    return m_characterSelection;
}

QString TranslateExercise::audioPath() const {
    return m_audioPath;
}
