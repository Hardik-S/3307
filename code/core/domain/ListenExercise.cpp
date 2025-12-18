#include "ListenExercise.h"

ListenExercise::ListenExercise(const QString& id, const QString& prompt, const QString& audioPath, const QStringList& choices, int correctIndex)
    : Exercise(id, prompt), m_audioPath(audioPath), m_choices(choices), m_correctIndex(correctIndex) {}

QString ListenExercise::type() const {
    return "Listen";
}

QString ListenExercise::audioPath() const {
    return m_audioPath;
}

QStringList ListenExercise::choices() const {
    return m_choices;
}

QString ListenExercise::correctAnswer() const {
    if (m_correctIndex >= 0 && m_correctIndex < m_choices.size()) {
        return m_choices[m_correctIndex];
    }
    return {};
}

int ListenExercise::correctIndex() const {
    return m_correctIndex;
}
