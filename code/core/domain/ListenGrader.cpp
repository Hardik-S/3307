#include "ListenGrader.h"

#include "ListenExercise.h"

Result ListenGrader::grade(const QString& userAnswer, const Exercise* exercise) {
    const auto* listen = dynamic_cast<const ListenExercise*>(exercise);
    Result result;
    if (!listen) {
        result.feedback = "Invalid exercise.";
        return result;
    }
    const int selected = userAnswer.toInt() - 1;
    result.correct = (selected == listen->correctIndex());
    result.score = result.correct ? 10 : 0;
    result.feedback = result.correct ? "Nice listening." : "Listen again.";
    return result;
}
