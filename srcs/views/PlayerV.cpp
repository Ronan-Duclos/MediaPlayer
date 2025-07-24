#include "PlayerV.hpp"

PlayerV::PlayerV(QWidget *parent) :
    QWidget{parent}, m_mainLayout(new QHBoxLayout(this)),
    m_secondLayout(new QVBoxLayout),
    m_volume(new QSlider(Qt::Vertical, this)),
    m_position(new QSlider(Qt::Horizontal, this)),
    m_buttons(new PlayerButtonsV(this)), m_positionPressed(false)
{
    QObject::connect(m_position.get(), &QSlider::sliderPressed, this, &PlayerV::onPositionPressed);
    QObject::connect(m_position.get(), &QSlider::sliderReleased, this, &PlayerV::onPositionRelease);
    QObject::connect(m_volume.get(), &QSlider::sliderMoved, this, &PlayerV::onVolumeMoved);
}

void PlayerV::init()
{
    m_mainLayout->setSpacing(5);
    m_mainLayout->setContentsMargins(5, 5, 5, 5);
    m_secondLayout->setSpacing(5);
    m_secondLayout->setContentsMargins(5, 5, 5, 5);

    m_position->setFixedWidth((this->width() - 15) * 0.9);
    m_position->setFixedHeight((this->height() - 15) * 0.5);
    m_buttons->setFixedWidth((this->width() - 15) * 0.9);
    m_buttons->setFixedHeight((this->height() - 15) * 0.5);
    m_volume->setFixedHeight(this->height() - 15);
    m_volume->setFixedWidth((this->width() - 15) * 0.1);

    this->setLayout(m_mainLayout.get());
    m_secondLayout->addWidget(m_position.get());
    m_secondLayout->addWidget(m_buttons.get());
    m_mainLayout->addLayout(m_secondLayout.get());
    m_mainLayout->addWidget(m_volume.get());

    m_volume->setMinimum(0);
    m_volume->setMaximum(100);
    m_volume->setValue(100);
    m_buttons->init();

    m_position->setStyleSheet("QSlider::sub-page:Horizontal { background-color: #6fd67a; }"
                              "QSlider::add-page:Horizontal { background-color: #7d7d7d; }"
                              "QSlider::groove:Horizontal { background: transparent; height:10px; }"
                              "QSlider::handle:Horizontal { width:30px; height:25px; background:#44e350; border-style:solid; border-color: #04590d; border-width:1px; border-radius:15px; margin: -12px 0px -12px 0px; }");

    m_volume->setStyleSheet("QSlider::sub-page:Vertical { background-color: #7d7d7d; }"
                            "QSlider::add-page:Vertical { background-color: #6fd67a; }"
                            "QSlider::groove:Vertical { background: transparent; width:5px; }"
                            "QSlider::handle:Vertical { width:16px; height:16px; background:#44e350; border-style:solid; border-color: #04590d; border-width:1px; border-radius:8px; margin: 0px -8px 0px -8px; }");
}

QSlider *PlayerV::position() const
{
    return m_position.get();
}

QSlider *PlayerV::volume() const
{
    return m_volume.get();
}

PlayerButtonsV *PlayerV::buttons() const
{
    return m_buttons.get();
}

void PlayerV::onDurationChanged(qint64 time)
{
    m_position->setMaximum(time);
}

void PlayerV::onPositionChanged(qint64 pos)
{
    if (!m_positionPressed)
        m_position->setSliderPosition(pos);
}

void PlayerV::onPositionPressed()
{
    m_positionPressed = true;
}

void PlayerV::onPositionRelease()
{
    m_positionPressed = false;
    emit positionChanged(m_position->value());
}

void PlayerV::onVolumeMoved()
{
    emit volumeChanged(m_volume->value());
}
