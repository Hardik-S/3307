#include "MCQExercise.h"

MCQExercise::MCQExercise(const QString& id, const QString& prompt, const QStringList& choices, int correctIndex)
    : Exercise(id, prompt), m_choices(choices), m_correctIndex(correctIndex) {}

QString MCQExercise::type() const {
    return "MCQ";
}

QStringList MCQExercise::choices() const {
    return m_choices;
}

QString MCQExercise::correctAnswer() const {
    if (m_correctIndex >= 0 && m_correctIndex < m_choices.size()) {
        return m_choices[m_correctIndex];
    }
    return {};
}

int MCQExercise::correctIndex() const {
    return m_correctIndex;
}
