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
      m_clearButton(new QPushButton("Clear", this)),
      m_gridLayout(new QGridLayout()) {
    m_display->setReadOnly(true);

    auto* layout = new QVBoxLayout(this);
    layout->addWidget(m_display);
    layout->addLayout(m_gridLayout);

    auto* controlRow = new QHBoxLayout();
    controlRow->addWidget(m_backspaceButton);
    controlRow->addWidget(m_clearButton);
    layout->addLayout(controlRow);

    connect(m_backspaceButton, &QPushButton::clicked, this, &CharacterSelectionWidget::backspace);
    connect(m_clearButton, &QPushButton::clicked, this, &CharacterSelectionWidget::clearSelection);

    setCharacters(CharacterUtils::defaultCharacters());
}

QString CharacterSelectionWidget::selection() const {
    return m_selection;
}

void CharacterSelectionWidget::clear() {
    setSelection({});
}

void CharacterSelectionWidget::setCharacters(const QStringList& characters) {
    m_characters = characters.isEmpty() ? CharacterUtils::defaultCharacters() : characters;
    rebuildGrid();
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

void CharacterSelectionWidget::rebuildGrid() {
    QLayoutItem* item = nullptr;
    while ((item = m_gridLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    const int columns = 6;
    for (int i = 0; i < m_characters.size(); ++i) {
        auto* button = new QPushButton(m_characters[i], this);
        button->setProperty("character", m_characters[i]);
        connect(button, &QPushButton::clicked, this, &CharacterSelectionWidget::appendCharacter);
        m_gridLayout->addWidget(button, i / columns, i % columns);
    }
}
