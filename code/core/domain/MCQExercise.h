#pragma once

#include "Exercise.h"

class MCQExercise : public Exercise {
public:
    MCQExercise(const QString& id, const QString& prompt, const QStringList& choices, int correctIndex);

    QString type() const override;
    QStringList choices() const override;
    QString correctAnswer() const override;

    int correctIndex() const;

private:
    QStringList m_choices;
    int m_correctIndex;
};
