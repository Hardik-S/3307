#pragma once

#include "IContentRepository.h"

#include <vector>

class LearningStream;

class JsonContentRepository : public IContentRepository {
public:
    explicit JsonContentRepository(const QString& contentPath = QString());
    std::vector<LearningStream> loadStreams(QString* error = nullptr) override;

private:
    QString resolveContentPath() const;

    QString m_contentPath;
};
