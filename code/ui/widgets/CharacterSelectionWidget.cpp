#include "CharacterSelectionWidget.h"

#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include "core/domain/CharacterUtils.h"

CharacterSelectionWidget::CharacterSelectionWidget(QWidget* parent)
    : QWidget(parent),
      m_display(new QLineEdit(this)),
      m_backspaceButton(new QPushButton("Backspace", this)),
      m_clearButton(new QPushButton("Clear", this)) {
    m_display->setReadOnly(true);

    auto* layout = new QVBoxLayout(this);
    layout->addWidget(m_display);

    auto* grid = new QGridLayout();
    const auto characters = CharacterUtils::defaultCharacters();
    const int columns = 6;
    for (int i = 0; i < characters.size(); ++i) {
        auto* button = new QPushButton(characters[i], this);
        button->setProperty("character", characters[i]);
        connect(button, &QPushButton::clicked, this, &CharacterSelectionWidget::appendCharacter);
        grid->addWidget(button, i / columns, i % columns);
    }
    layout->addLayout(grid);

    auto* controlRow = new QHBoxLayout();
    controlRow->addWidget(m_backspaceButton);
    controlRow->addWidget(m_clearButton);
    layout->addLayout(controlRow);

    connect(m_backspaceButton, &QPushButton::clicked, this, &CharacterSelectionWidget::backspace);
    connect(m_clearButton, &QPushButton::clicked, this, &CharacterSelectionWidget::clearSelection);
}

QString CharacterSelectionWidget::selection() const {
    return m_selection;
}

void CharacterSelectionWidget::clear() {
    setSelection({});
}

void CharacterSelectionWidget::appendCharacter() {
    auto* button = qobject_cast<QPushButton*>(sender());
    if (!button) {
        return;
    }
    const QString value = button->property("character").toString();
    setSelection(m_selection + value);
}

void CharacterSelectionWidget::backspace() {
    if (m_selection.isEmpty()) {
        return;
    }
    m_selection.chop(1);
    setSelection(m_selection);
}

void CharacterSelectionWidget::clearSelection() {
    setSelection({});
}

void CharacterSelectionWidget::setSelection(const QString& value) {
    m_selection = value;
    m_display->setText(m_selection);
    emit selectionChanged(m_selection);
}
