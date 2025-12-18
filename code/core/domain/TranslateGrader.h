#pragma once

#include "StrategyGrader.h"

class TranslateGrader : public StrategyGrader {
public:
    Result grade(const QString& userAnswer, const Exercise* exercise) override;
};
