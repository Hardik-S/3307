#include "CharacterSelectionGrader.h"

#include "TranslateExercise.h"

Result CharacterSelectionGrader::grade(const QString& userAnswer, const Exercise* exercise) {
    const auto* translate = dynamic_cast<const TranslateExercise*>(exercise);
    Result result;
    if (!translate) {
        result.feedback = "Invalid exercise.";
        return result;
    }
    const QString normalized = userAnswer.trimmed();
    for (const auto& answer : translate->acceptableAnswers()) {
        if (normalized == answer.trimmed()) {
            result.correct = true;
            break;
        }
    }
    result.score = result.correct ? 14 : 0;
    result.feedback = result.correct ? "Nice characters." : "Check the sequence.";
    return result;
}
