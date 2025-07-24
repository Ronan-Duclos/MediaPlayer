#pragma once

#include <QWidget>
#include <QLayout>
#include <QSlider>

#include "PlayerButtonsV.hpp"

class PlayerV :public QWidget
{
    Q_OBJECT
public:
    explicit PlayerV(QWidget *parent = nullptr);

    void init();

    QSlider *position() const;
    QSlider *volume() const;
    PlayerButtonsV *buttons() const;

signals:
    void positionChanged(const qint64 pos);
    void volumeChanged(const int volume);

public slots:
    void onDurationChanged(qint64 time);
    void onPositionChanged(qint64 pos);

private slots:
    void onPositionPressed();
    void onPositionRelease();
    void onVolumeMoved();

private:
    std::unique_ptr<QHBoxLayout>    m_mainLayout;
    std::unique_ptr<QVBoxLayout>    m_secondLayout;
    std::unique_ptr<QSlider>        m_position;
    std::unique_ptr<QSlider>        m_volume;
    std::unique_ptr<PlayerButtonsV> m_buttons;
    bool                            m_positionPressed;

};
