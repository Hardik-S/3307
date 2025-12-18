#pragma once

#include <QWidget>

class QLineEdit;
class QPushButton;

class CharacterSelectionWidget : public QWidget {
    Q_OBJECT

public:
    explicit CharacterSelectionWidget(QWidget* parent = nullptr);

    QString selection() const;
    void clear();

signals:
    void selectionChanged(const QString& value);

private slots:
    void appendCharacter();
    void backspace();
    void clearSelection();

private:
    void setSelection(const QString& value);

    QString m_selection;
    QLineEdit* m_display;
    QPushButton* m_backspaceButton;
    QPushButton* m_clearButton;
};
