#pragma once

#include "StrategyGrader.h"

class CharacterSelectionGrader : public StrategyGrader {
public:
    Result grade(const QString& userAnswer, const Exercise* exercise) override;
};
