#pragma once

#include <QString>
#include <vector>

class Exercise;
class LearningStream;

class IContentRepository {
public:
    virtual ~IContentRepository() = default;
    virtual std::vector<LearningStream> loadStreams(QString* error = nullptr) = 0;
};
