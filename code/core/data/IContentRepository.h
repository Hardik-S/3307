#pragma once

#include <QVector>
#include <QString>

class Exercise;

class IContentRepository {
public:
    virtual ~IContentRepository() = default;
    virtual QVector<Exercise*> loadExercises(QString* error = nullptr) = 0;
};
