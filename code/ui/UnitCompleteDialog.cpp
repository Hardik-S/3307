#include "UnitCompleteDialog.h"

#include <QEasingCurve>
#include <QHBoxLayout>
#include <QLabel>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QVBoxLayout>

UnitCompleteDialog::UnitCompleteDialog(const QString& title, QWidget* parent)
    : QDialog(parent),
      m_titleLabel(new QLabel(title, this)),
      m_continueButton(new QPushButton("Keep Learning", this)) {
    setWindowTitle("Unit Complete");
    setModal(true);
    setMinimumSize(360, 220);

    auto* layout = new QVBoxLayout(this);
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setStyleSheet("font-size: 18px; font-weight: bold;");

    auto* message = new QLabel("Great work finishing this unit!", this);
    message->setAlignment(Qt::AlignCenter);

    auto* confettiRow = new QHBoxLayout();
    layout->addWidget(m_titleLabel);
    layout->addWidget(message);
    layout->addLayout(confettiRow);
    layout->addStretch(1);
    layout->addWidget(m_continueButton, 0, Qt::AlignCenter);

    const QStringList colors = {"#f44336", "#ff9800", "#ffeb3b", "#4caf50", "#2196f3", "#9c27b0"};
    for (const auto& color : colors) {
        auto* dot = new QLabel("*", this);
        dot->setStyleSheet("font-size: 22px; color: " + color + ";");
        dot->setAlignment(Qt::AlignCenter);
        confettiRow->addWidget(dot);
        m_confettiDots.append(dot);
    }

    buildConfetti();

    connect(m_continueButton, &QPushButton::clicked, this, [this]() {
        emit continueRequested();
        accept();
    });
}

void UnitCompleteDialog::buildConfetti() {
    for (int i = 0; i < m_confettiDots.size(); ++i) {
        auto* dot = m_confettiDots[i];
        auto* animation = new QPropertyAnimation(dot, "pos", this);
        const QPoint start = dot->pos();
        animation->setStartValue(start);
        animation->setEndValue(start + QPoint(0, 12));
        animation->setDuration(600 + i * 80);
        animation->setLoopCount(-1);
        animation->setEasingCurve(QEasingCurve::InOutSine);
        animation->start();
        m_animations.append(animation);
    }
}
