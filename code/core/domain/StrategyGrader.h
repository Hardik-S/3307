#pragma once

#include <QString>

#include "Result.h"

class Exercise;

// Behavioral Pattern: Strategy for grading algorithms.
class StrategyGrader {
public:
    virtual ~StrategyGrader() = default;
    virtual Result grade(const QString& userAnswer, const Exercise* exercise) = 0;
};
