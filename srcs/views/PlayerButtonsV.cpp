#include "PlayerButtonsV.hpp"

#include <QFont>

PlayerButtonsV::PlayerButtonsV(QWidget *parent) :
    QWidget{parent}, m_mainLayout(new QHBoxLayout(this)),
    m_lect(new QPushButton(this)),
    m_pause(new QPushButton(this)),
    m_stop(new QPushButton(this)),
    m_next(new QPushButton(this)),
    m_prev(new QPushButton(this))
{

}

void PlayerButtonsV::init()
{
    this->setLayout(m_mainLayout.get());
    m_mainLayout->setSpacing(5);
    m_mainLayout->setContentsMargins(5, 5, 5, 5);
    setButton(m_lect.get(), "img/ButtonsIcons/play.png", "Lect");
    setButton(m_pause.get(), "img/ButtonsIcons/pause.png", "Pause");
    setButton(m_stop.get(), "img/ButtonsIcons/stop.png", "Stop");
    setButton(m_next.get(), "img/ButtonsIcons/next.png", "Next");
    setButton(m_prev.get(), "img/ButtonsIcons/prev.png", "Prev");
}

QPushButton *PlayerButtonsV::lectButton() const
{
    return m_lect.get();
}

QPushButton *PlayerButtonsV::pauseButton() const
{
    return m_pause.get();
}

QPushButton *PlayerButtonsV::stopButton() const
{
    return m_stop.get();
}

QPushButton *PlayerButtonsV::nextButton() const
{
    return m_next.get();
}

QPushButton *PlayerButtonsV::prevButton() const
{
    return m_prev.get();
}

void PlayerButtonsV::setPlayList(bool off)
{
    m_lect->setEnabled(!off);
    m_pause->setEnabled(!off);
    m_stop->setEnabled(!off);
    m_next->setEnabled(!off);
    m_prev->setEnabled(!off);
}

void PlayerButtonsV::setStop(bool on)
{
    m_lect->setEnabled(on);
    m_pause->setEnabled(!on);
    m_stop->setEnabled(!on);
}

void PlayerButtonsV::setPause(const bool on)
{
    m_lect->setEnabled(on);
    m_pause->setEnabled(!on);
    m_stop->setEnabled(on);
}

void PlayerButtonsV::setButton(QPushButton *button, QString name, QString tooltip)
{
    button->setIcon(QIcon(QPixmap(name)));
    button->setIconSize(QSize(40, 40));
    button->setFixedHeight(this->height() - 10);
    button->setFixedWidth((this->width() - 30) * 0.2);
    button->setFont(QFont("Tahoma", 20, QFont::Bold, false));
    button->setToolTip(tooltip);
    button->setEnabled(false);
    m_mainLayout->addWidget(button);
}
