#pragma once

#include "Exercise.h"

class SpeakExercise : public Exercise {
public:
    SpeakExercise(const QString& id, const QString& prompt, const QString& expectedKeyword);

    QString type() const override;
    QString expectedKeyword() const;

private:
    QString m_expectedKeyword;
};
