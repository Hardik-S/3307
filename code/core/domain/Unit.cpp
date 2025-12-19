#include "Unit.h"

#include "Exercise.h"

Unit::Unit(const QString& id, const QString& title)
    : m_id(id), m_title(title) {}

const QString& Unit::id() const {
    return m_id;
}

const QString& Unit::title() const {
    return m_title;
}

void Unit::addExercise(std::unique_ptr<Exercise> exercise) {
    if (exercise) {
        m_exercises.emplace_back(std::move(exercise));
    }
}

const Exercise* Unit::exerciseAt(int index) const {
    if (index < 0 || index >= static_cast<int>(m_exercises.size())) {
        return nullptr;
    }
    return m_exercises[static_cast<size_t>(index)].get();
}

int Unit::size() const {
    return static_cast<int>(m_exercises.size());
}
