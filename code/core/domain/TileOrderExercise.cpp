#include "TileOrderExercise.h"

TileOrderExercise::TileOrderExercise(const QString& id, const QString& prompt, const QStringList& tiles, const QStringList& correctOrder)
    : Exercise(id, prompt), m_tiles(tiles), m_correctOrder(correctOrder) {}

QString TileOrderExercise::type() const {
    return "TileOrder";
}

QStringList TileOrderExercise::choices() const {
    return m_tiles;
}

QStringList TileOrderExercise::correctOrder() const {
    return m_correctOrder;
}
