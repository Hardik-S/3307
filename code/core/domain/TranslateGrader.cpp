#include "TranslateGrader.h"

#include "TranslateExercise.h"

Result TranslateGrader::grade(const QString& userAnswer, const Exercise* exercise) {
    const auto* translate = dynamic_cast<const TranslateExercise*>(exercise);
    Result result;
    if (!translate) {
        result.feedback = "Invalid exercise.";
        return result;
    }
    const QString normalized = userAnswer.trimmed().toLower();
    for (const auto& answer : translate->acceptableAnswers()) {
        if (normalized == answer.trimmed().toLower()) {
            result.correct = true;
            break;
        }
    }
    result.score = result.correct ? 12 : 0;
    result.feedback = result.correct ? "Correct translation." : "Keep practicing.";
    return result;
}
