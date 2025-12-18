#pragma once

#include "StrategyGrader.h"

class ListenGrader : public StrategyGrader {
public:
    Result grade(const QString& userAnswer, const Exercise* exercise) override;
};
