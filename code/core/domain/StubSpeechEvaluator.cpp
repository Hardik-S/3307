#include "StubSpeechEvaluator.h"

#include <QRandomGenerator>

int StubSpeechEvaluator::evaluate(const QString& expectedKeyword, const QString& userTranscript) const {
    if (!expectedKeyword.isEmpty() && userTranscript.contains(expectedKeyword, Qt::CaseInsensitive)) {
        return 85;
    }
    return static_cast<int>(QRandomGenerator::global()->bounded(40, 71));
}
