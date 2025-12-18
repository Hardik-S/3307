#include "TileOrderGrader.h"

#include "TileOrderExercise.h"

Result TileOrderGrader::grade(const QString& userAnswer, const Exercise* exercise) {
    const auto* tile = dynamic_cast<const TileOrderExercise*>(exercise);
    Result result;
    if (!tile) {
        result.feedback = "Invalid exercise.";
        return result;
    }
    const QStringList submittedRaw = userAnswer.split(',', Qt::SkipEmptyParts);
    QStringList submitted;
    submitted.reserve(submittedRaw.size());
    for (const auto& item : submittedRaw) {
        submitted.append(item.trimmed());
    }
    result.correct = (submitted == tile->correctOrder());
    result.score = result.correct ? 15 : 0;
    result.feedback = result.correct ? "Great ordering." : "Order needs work.";
    return result;
}
