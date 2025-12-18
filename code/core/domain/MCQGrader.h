#pragma once

#include "StrategyGrader.h"

class MCQGrader : public StrategyGrader {
public:
    Result grade(const QString& userAnswer, const Exercise* exercise) override;
};
