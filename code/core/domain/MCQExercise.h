#pragma once

#include "Exercise.h"

class MCQExercise : public Exercise {
public:
    MCQExercise(const QString& id, const QString& prompt, const QStringList& choices, int correctIndex, const QString& audioPath = QString());

    QString type() const override;
    QStringList choices() const override;
    QString correctAnswer() const override;
    QString audioPath() const override;

    int correctIndex() const;

private:
    QStringList m_choices;
    int m_correctIndex;
    QString m_audioPath;
};
