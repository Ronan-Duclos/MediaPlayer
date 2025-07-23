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

    QSlider *slider() const;
    PlayerButtonsV *buttons() const;

signals:
    void positionChanged(const qint64 pos);

public slots:
    void onDurationChanged(qint64 time);
    void onPositionChanged(qint64 pos);

private slots:
    void onSliderPressed();
    void onSliderRelease();

private:
    std::unique_ptr<QVBoxLayout>    m_mainLayout;
    std::unique_ptr<QSlider>        m_slider;
    std::unique_ptr<PlayerButtonsV> m_buttons;
    bool                            m_sliderPressed;

};
