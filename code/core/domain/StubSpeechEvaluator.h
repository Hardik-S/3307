#pragma once

#include <QString>

class StubSpeechEvaluator {
public:
    int evaluate(const QString& expectedKeyword, const QString& userTranscript) const;
};
