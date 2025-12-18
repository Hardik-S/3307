#pragma once

#include "IContentRepository.h"

class JsonContentRepository : public IContentRepository {
public:
    explicit JsonContentRepository(const QString& contentPath = QString());
    QVector<Exercise*> loadExercises(QString* error = nullptr) override;

private:
    QString resolveContentPath() const;

    QString m_contentPath;
};
