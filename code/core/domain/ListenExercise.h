#pragma once

#include "Exercise.h"

class ListenExercise : public Exercise {
public:
    ListenExercise(const QString& id, const QString& prompt, const QString& audioPath, const QStringList& choices, int correctIndex);

    QString type() const override;
    QString audioPath() const override;
    QStringList choices() const override;
    QString correctAnswer() const override;
    int correctIndex() const;

private:
    QString m_audioPath;
    QStringList m_choices;
    int m_correctIndex;
};
