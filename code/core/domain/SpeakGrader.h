#pragma once

#include "StrategyGrader.h"

#include "StubSpeechEvaluator.h"

class SpeakGrader : public StrategyGrader {
public:
    explicit SpeakGrader(StubSpeechEvaluator evaluator = StubSpeechEvaluator());
    Result grade(const QString& userAnswer, const Exercise* exercise) override;

private:
    StubSpeechEvaluator m_evaluator;
};
