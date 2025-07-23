#include "PlayerV.hpp"

PlayerV::PlayerV(QWidget *parent) :
    QWidget{parent}, m_mainLayout(new QVBoxLayout(this)),
    m_slider(new QSlider(Qt::Horizontal, this)),
    m_buttons(new PlayerButtonsV(this)), m_sliderPressed(false)
{
    QObject::connect(m_slider.get(), &QSlider::sliderPressed, this, &PlayerV::onSliderPressed);
    QObject::connect(m_slider.get(), &QSlider::sliderReleased, this, &PlayerV::onSliderRelease);
}

void PlayerV::init()
{
    m_mainLayout->setSpacing(5);
    m_mainLayout->setContentsMargins(5, 5, 5, 5);
    m_slider->setFixedWidth(this->width() - 15);
    m_slider->setFixedHeight((this->height() - 15) * 0.5);
    m_buttons->setFixedWidth(this->width() - 15);
    m_buttons->setFixedHeight((this->height() - 15) * 0.5);

    this->setLayout(m_mainLayout.get());
    m_mainLayout->addWidget(m_slider.get());
    m_mainLayout->addWidget(m_buttons.get());
    m_buttons->init();
}

QSlider *PlayerV::slider() const
{
    return m_slider.get();
}

PlayerButtonsV *PlayerV::buttons() const
{
    return m_buttons.get();
}

void PlayerV::onDurationChanged(qint64 time)
{
    m_slider->setMaximum(time);
}

void PlayerV::onPositionChanged(qint64 pos)
{
    if (!m_sliderPressed)
        m_slider->setSliderPosition(pos);
}

void PlayerV::onSliderPressed()
{
    m_sliderPressed = true;
}

void PlayerV::onSliderRelease()
{
    emit positionChanged(m_slider->value());
    m_sliderPressed = false;
}
