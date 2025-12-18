#include "Exercise.h"

Exercise::Exercise(const QString& id, const QString& prompt)
    : m_id(id), m_prompt(prompt) {}

QString Exercise::id() const {
    return m_id;
}

QString Exercise::prompt() const {
    return m_prompt;
}

QStringList Exercise::choices() const {
    return {};
}

QString Exercise::correctAnswer() const {
    return {};
}

QString Exercise::audioPath() const {
    return {};
}

bool Exercise::usesCharacterSelection() const {
    return false;
}
