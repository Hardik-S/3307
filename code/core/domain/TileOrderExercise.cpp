#include "TileOrderExercise.h"

TileOrderExercise::TileOrderExercise(const QString& id, const QString& prompt, const QStringList& tiles, const QStringList& correctOrder,
    const QString& audioPath)
    : Exercise(id, prompt), m_tiles(tiles), m_correctOrder(correctOrder), m_audioPath(audioPath) {}

QString TileOrderExercise::type() const {
    return "TileOrder";
}

QStringList TileOrderExercise::choices() const {
    return m_tiles;
}

QStringList TileOrderExercise::correctOrder() const {
    return m_correctOrder;
}

QString TileOrderExercise::audioPath() const {
    return m_audioPath;
}
