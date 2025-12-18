#include "MCQGrader.h"

#include "MCQExercise.h"

Result MCQGrader::grade(const QString& userAnswer, const Exercise* exercise) {
    const auto* mcq = dynamic_cast<const MCQExercise*>(exercise);
    Result result;
    if (!mcq) {
        result.feedback = "Invalid exercise.";
        return result;
    }
    const int selected = userAnswer.toInt() - 1;
    result.correct = (selected == mcq->correctIndex());
    result.score = result.correct ? 10 : 0;
    result.feedback = result.correct ? "Correct!" : "Try again.";
    return result;
}
