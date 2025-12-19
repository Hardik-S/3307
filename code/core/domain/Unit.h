#pragma once

#include <QString>
#include <memory>
#include <vector>

#include "Exercise.h"

class Unit {
public:
    Unit(const QString& id, const QString& title);

    const QString& id() const;
    const QString& title() const;

    void addExercise(std::unique_ptr<Exercise> exercise);
    const Exercise* exerciseAt(int index) const;
    int size() const;

private:
    QString m_id;
    QString m_title;
    std::vector<std::unique_ptr<Exercise>> m_exercises;
};
