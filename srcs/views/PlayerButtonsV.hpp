#pragma once

#include <QWidget>
#include <QLayout>
#include <QPushButton>

class PlayerButtonsV : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerButtonsV(QWidget *parent = nullptr);

    void init();

    QPushButton *lectButton() const;
    QPushButton *pauseButton() const;
    QPushButton *stopButton() const;
    QPushButton *nextButton() const;
    QPushButton *prevButton() const;

public slots:
    void setPlayList(const bool off);
    void setStop(const bool on);
    void setPause(const bool on);

private:
    std::unique_ptr<QHBoxLayout>     m_mainLayout;
    std::unique_ptr<QPushButton>     m_lect;
    std::unique_ptr<QPushButton>     m_pause;
    std::unique_ptr<QPushButton>     m_stop;
    std::unique_ptr<QPushButton>     m_next;
    std::unique_ptr<QPushButton>     m_prev;

    void setButton(QPushButton *button, QString name, QString tooltip);

};
