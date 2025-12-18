#pragma once

#include "Exercise.h"

class TranslateExercise : public Exercise {
public:
    TranslateExercise(const QString& id, const QString& prompt, const QStringList& acceptableAnswers, bool characterSelection);

    QString type() const override;
    QStringList acceptableAnswers() const;
    QString correctAnswer() const override;
    bool usesCharacterSelection() const override;

private:
    QStringList m_acceptableAnswers;
    bool m_characterSelection;
};
