#include "JsonContentRepository.h"

#include <QCoreApplication>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <memory>

#include "core/domain/Exercise.h"
#include "core/domain/ExerciseFactory.h"
#include "core/domain/LearningStream.h"
#include "core/domain/Unit.h"

JsonContentRepository::JsonContentRepository(const QString& contentPath)
    : m_contentPath(contentPath) {}

QString JsonContentRepository::resolveContentPath() const {
    if (!m_contentPath.isEmpty()) {
        return m_contentPath;
    }
    return QCoreApplication::applicationDirPath() + "/content.json";
}

std::vector<LearningStream> JsonContentRepository::loadStreams(QString* error) {
    std::vector<LearningStream> streams;
    const QString path = resolveContentPath();
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        if (error) {
            *error = "Failed to open content.json at " + path;
        }
        return streams;
    }

    const auto doc = QJsonDocument::fromJson(file.readAll());
    if (!doc.isObject()) {
        if (error) {
            *error = "Content JSON root is not an object.";
        }
        return streams;
    }

    const auto root = doc.object();
    const auto streamItems = root.value("streams").toArray();
    for (const auto& streamValue : streamItems) {
        const auto streamObj = streamValue.toObject();
        LearningStream stream(
            streamObj.value("id").toString(),
            streamObj.value("name").toString(),
            streamObj.value("language").toString()
        );

        const auto unitItems = streamObj.value("units").toArray();
        for (const auto& unitValue : unitItems) {
            const auto unitObj = unitValue.toObject();
            Unit unit(unitObj.value("id").toString(), unitObj.value("title").toString());

            const auto exercises = unitObj.value("exercises").toArray();
            for (const auto& exerciseValue : exercises) {
                const auto exerciseObj = exerciseValue.toObject();
                const QString type = exerciseObj.value("type").toString();
                const QJsonObject spec = exerciseObj.value("spec").toObject();
                std::unique_ptr<Exercise> exercise(ExerciseFactory::createExercise(type, spec));
                if (exercise) {
                    unit.addExercise(std::move(exercise));
                }
            }
            stream.addUnit(std::move(unit));
        }
        streams.emplace_back(std::move(stream));
    }

    return streams;
}
