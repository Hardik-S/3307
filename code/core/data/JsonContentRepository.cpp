#include "JsonContentRepository.h"

#include <QCoreApplication>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "core/domain/Exercise.h"
#include "core/domain/ExerciseFactory.h"

JsonContentRepository::JsonContentRepository(const QString& contentPath)
    : m_contentPath(contentPath) {}

QString JsonContentRepository::resolveContentPath() const {
    if (!m_contentPath.isEmpty()) {
        return m_contentPath;
    }
    return QCoreApplication::applicationDirPath() + "/content.json";
}

QVector<Exercise*> JsonContentRepository::loadExercises(QString* error) {
    QVector<Exercise*> exercises;
    const QString path = resolveContentPath();
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        if (error) {
            *error = "Failed to open content.json at " + path;
        }
        return exercises;
    }

    const auto doc = QJsonDocument::fromJson(file.readAll());
    if (!doc.isObject()) {
        if (error) {
            *error = "Content JSON root is not an object.";
        }
        return exercises;
    }

    const auto root = doc.object();
    const auto items = root.value("exercises").toArray();
    for (const auto& item : items) {
        const auto obj = item.toObject();
        const QString type = obj.value("type").toString();
        const QJsonObject spec = obj.value("spec").toObject();
        Exercise* exercise = ExerciseFactory::createExercise(type, spec);
        if (exercise) {
            exercises.append(exercise);
        }
    }

    return exercises;
}
