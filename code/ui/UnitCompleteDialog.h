#pragma once

#include <QDialog>

#include <QList>

class QLabel;
class QPushButton;
class QPropertyAnimation;

class UnitCompleteDialog : public QDialog {
    Q_OBJECT

public:
    explicit UnitCompleteDialog(const QString& title, QWidget* parent = nullptr);

signals:
    void continueRequested();

private:
    void buildConfetti();

    QLabel* m_titleLabel;
    QPushButton* m_continueButton;
    QList<QLabel*> m_confettiDots;
    QList<QPropertyAnimation*> m_animations;
};
