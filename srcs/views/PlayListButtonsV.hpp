#pragma once

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QCheckBox>

class PlayListButtonsV : public QWidget
{
    Q_OBJECT
public:
    explicit PlayListButtonsV(QWidget *parent = nullptr);

    void init();

    QPushButton *addTrack();
    QPushButton *removeTrack();
    QPushButton *addDirTracks();
    QPushButton *loop();
    QPushButton *random();

private:
    std::unique_ptr<QHBoxLayout>    m_mainLayout;
    std::unique_ptr<QPushButton>    m_addTrack;
    std::unique_ptr<QPushButton>    m_removeTrack;
    std::unique_ptr<QPushButton>    m_addDirTracks;
    std::unique_ptr<QPushButton>      m_loop;
    std::unique_ptr<QPushButton>      m_random;

    void setButton(QAbstractButton *button, QString name, QString tooltip);
    void setButtonImg(QAbstractButton *button, QString name, QString tooltip);
};
