#include "LessonView.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "core/domain/Exercise.h"
#include "core/domain/ListenExercise.h"
#include "core/domain/TileOrderExercise.h"
#include "core/domain/TranslateExercise.h"
#include "ui/widgets/CharacterSelectionWidget.h"

LessonView::LessonView(QWidget* parent)
    : QWidget(parent),
      m_exercise(nullptr),
      m_promptLabel(new QLabel(this)),
      m_progressLabel(new QLabel(this)),
      m_resultLabel(new QLabel(this)),
      m_choiceList(new QListWidget(this)),
      m_hintLabel(new QLabel(this)),
      m_answerInput(new QLineEdit(this)),
      m_characterWidget(new CharacterSelectionWidget(this)),
      m_submitButton(new QPushButton("Submit", this)),
      m_nextButton(new QPushButton("Next", this)),
      m_playButton(new QPushButton("Play Audio", this)) {
    setStyleSheet(
        "QWidget {"
        "    background-color: #f5f5f5;"
        "}"
        "QLabel {"
        "    color: #333333;"
        "}"
        "QPushButton {"
        "    background-color: #4CAF50;"
        "    color: white;"
        "    border: none;"
        "    border-radius: 5px;"
        "    padding: 10px;"
        "    font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #3d8b40;"
        "}"
        "QPushButton:disabled {"
        "    background-color: #cccccc;"
        "    color: #666666;"
        "}"
        "QProgressBar {"
        "    border: 2px solid #cccccc;"
        "    border-radius: 5px;"
        "    text-align: center;"
        "    height: 25px;"
        "}"
        "QProgressBar::chunk {"
        "    background-color: #4CAF50;"
        "    border-radius: 3px;"
        "}"
        "QLineEdit {"
        "    border: 2px solid #cccccc;"
        "    border-radius: 5px;"
        "    padding: 8px;"
        "    font-size: 12px;"
        "}"
        "QLineEdit:focus {"
        "    border: 2px solid #4CAF50;"
        "}"
        "QRadioButton {"
        "    spacing: 10px;"
        "    padding: 5px;"
        "}"
        "QRadioButton::indicator {"
        "    width: 20px;"
        "    height: 20px;"
        "}"
        "QListWidget {"
        "    border: 2px solid #cccccc;"
        "    border-radius: 5px;"
        "    padding: 5px;"
        "}"
        "QListWidget::item {"
        "    background-color: white;"
        "    border: 1px solid #e0e0e0;"
        "    border-radius: 3px;"
        "    padding: 10px;"
        "    margin: 3px;"
        "}"
        "QListWidget::item:selected {"
        "    background-color: #e3f2fd;"
        "    border: 2px solid #2196F3;"
        "}"
    );
    m_promptLabel->setWordWrap(true);
    m_resultLabel->setStyleSheet("font-weight: bold; color: #1b5e20;");
    m_hintLabel->setStyleSheet("color: #666;");

    auto* layout = new QVBoxLayout(this);
    m_progressLabel->setStyleSheet("color: #777; font-size: 12px;");
    layout->addWidget(m_progressLabel);
    layout->addWidget(m_promptLabel);
    layout->addWidget(m_playButton);
    layout->addWidget(m_choiceList);
    layout->addWidget(m_hintLabel);
    layout->addWidget(m_answerInput);
    layout->addWidget(m_characterWidget);

    auto* buttonRow = new QHBoxLayout();
    buttonRow->addWidget(m_submitButton);
    buttonRow->addWidget(m_nextButton);
    layout->addLayout(buttonRow);
    layout->addWidget(m_resultLabel);
    layout->addStretch(1);

    connect(m_submitButton, &QPushButton::clicked, this, &LessonView::handleSubmit);
    connect(m_nextButton, &QPushButton::clicked, this, &LessonView::handleNext);
    connect(m_playButton, &QPushButton::clicked, this, &LessonView::playAudioRequested);
    connect(m_characterWidget, &CharacterSelectionWidget::selectionChanged, this, &LessonView::handleCharacterSelectionChanged);
    connect(m_choiceList, &QListWidget::itemClicked, this, &LessonView::handleChoiceClicked);

    m_choiceList->setVisible(false);
    m_choiceList->setSelectionMode(QAbstractItemView::SingleSelection);
    m_playButton->setVisible(false);
    m_characterWidget->setVisible(false);
    m_nextButton->setEnabled(false);
}

void LessonView::setExercise(const Exercise* exercise) {
    m_exercise = exercise;
    m_resultLabel->clear();
    m_nextButton->setEnabled(false);
    m_answerInput->clear();
    m_characterWidget->clear();
    updateForExerciseType(exercise);
}

void LessonView::setUnitProgress(int current, int total) {
    m_progressLabel->setText(QString("Unit Progress: %1 / %2").arg(current).arg(total));
}

void LessonView::updateForExerciseType(const Exercise* exercise) {
    if (!exercise) {
        return;
    }

    m_promptLabel->setText(exercise->prompt());
    m_choiceList->clear();
    m_choiceList->setVisible(false);
    m_playButton->setVisible(false);
    m_answerInput->setVisible(true);
    m_answerInput->setReadOnly(false);
    m_characterWidget->setVisible(false);
    m_hintLabel->clear();

    if (exercise->type() == "MCQ" || exercise->type() == "Listen") {
        const auto choices = exercise->choices();
        for (int i = 0; i < choices.size(); ++i) {
            m_choiceList->addItem(QString::number(i + 1) + ". " + choices[i]);
        }
        m_choiceList->setVisible(true);
        m_hintLabel->setText("Click an option or type its number.");
        m_answerInput->setPlaceholderText("e.g., 1");
    }

    if (!exercise->audioPath().isEmpty()) {
        m_playButton->setVisible(true);
    }

    if (exercise->type() == "Translate") {
        const auto* translate = dynamic_cast<const TranslateExercise*>(exercise);
        if (translate && translate->usesCharacterSelection()) {
            m_answerInput->setReadOnly(true);
            m_characterWidget->setVisible(true);
            m_characterWidget->setCharacters(translate->characterSet());
            m_hintLabel->setText("Select characters to build the answer.");
        } else {
            m_answerInput->setReadOnly(false);
            m_hintLabel->setText("Type your translation.");
        }
    }

    if (exercise->type() == "TileOrder") {
        const auto* tile = dynamic_cast<const TileOrderExercise*>(exercise);
        if (tile) {
            m_hintLabel->setText("Order the tiles separated by commas.");
            m_answerInput->setPlaceholderText(tile->choices().join(", "));
        }
    }

    if (exercise->type() == "Speak") {
        m_hintLabel->setText("Type what you said (stub evaluation).");
        m_answerInput->setPlaceholderText("Transcript...");
    }
}

QString LessonView::currentAnswer() const {
    if (m_exercise && m_exercise->type() == "Translate") {
        const auto* translate = dynamic_cast<const TranslateExercise*>(m_exercise);
        if (translate && translate->usesCharacterSelection()) {
            return m_characterWidget->selection();
        }
    }
    return m_answerInput->text();
}

void LessonView::handleSubmit() {
    emit answerSubmitted(currentAnswer());
}

void LessonView::handleNext() {
    emit nextRequested();
}

void LessonView::handleCharacterSelectionChanged(const QString& value) {
    m_answerInput->setText(value);
}

void LessonView::handleChoiceClicked(QListWidgetItem* item) {
    if (!item) {
        return;
    }
    // Extract leading number before the dot, fallback to row index if parsing fails.
    const QString text = item->text();
    const int dotIndex = text.indexOf('.');
    if (dotIndex > 0) {
        m_answerInput->setText(text.left(dotIndex).trimmed());
    } else {
        const int row = m_choiceList->row(item);
        m_answerInput->setText(QString::number(row + 1));
    }
}

void LessonView::showResult(const QString& message) {
    m_resultLabel->setText(message);
    m_nextButton->setEnabled(true);
}
