#pragma once

#include "Exercise.h"

class TranslateExercise : public Exercise {
public:
    TranslateExercise(const QString& id, const QString& prompt, const QStringList& acceptableAnswers, bool characterSelection,
        const QStringList& characterSet = QStringList(), const QString& audioPath = QString());

    QString type() const override;
    QStringList acceptableAnswers() const;
    QStringList characterSet() const;
    QString correctAnswer() const override;
    bool usesCharacterSelection() const override;
    QString audioPath() const override;

private:
    QStringList m_acceptableAnswers;
    bool m_characterSelection;
    QStringList m_characterSet;
    QString m_audioPath;
};
