#pragma once

#include <QWidget>

class QPushButton;

class HomeView : public QWidget {
    Q_OBJECT

public:
    explicit HomeView(QWidget* parent = nullptr);

signals:
    void startLessonRequested();
    void profileRequested();

private:
    QPushButton* m_startButton;
    QPushButton* m_profileButton;
};
