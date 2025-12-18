#include "SpeakGrader.h"

#include "SpeakExercise.h"

SpeakGrader::SpeakGrader(StubSpeechEvaluator evaluator)
    : m_evaluator(evaluator) {}

Result SpeakGrader::grade(const QString& userAnswer, const Exercise* exercise) {
    const auto* speak = dynamic_cast<const SpeakExercise*>(exercise);
    Result result;
    if (!speak) {
        result.feedback = "Invalid exercise.";
        return result;
    }
    const int score = m_evaluator.evaluate(speak->expectedKeyword(), userAnswer);
    result.correct = score >= 70;
    result.score = score;
    result.feedback = result.correct ? "Nice pronunciation." : "Keep practicing.";
    return result;
}
