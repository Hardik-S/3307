#pragma once

#include "Exercise.h"

class TileOrderExercise : public Exercise {
public:
    TileOrderExercise(const QString& id, const QString& prompt, const QStringList& tiles, const QStringList& correctOrder);

    QString type() const override;
    QStringList choices() const override;
    QStringList correctOrder() const;

private:
    QStringList m_tiles;
    QStringList m_correctOrder;
};
