#pragma once

#include "StrategyGrader.h"

class TileOrderGrader : public StrategyGrader {
public:
    Result grade(const QString& userAnswer, const Exercise* exercise) override;
};
