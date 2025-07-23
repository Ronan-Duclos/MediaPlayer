#include "PlayListButtonsV.hpp"

PlayListButtonsV::PlayListButtonsV(QWidget *parent) :
    QWidget{parent}, m_mainLayout(new QHBoxLayout(this)),
    m_addTrack(new QPushButton(this)),
    m_removeTrack(new QPushButton(this)),
    m_addDirTracks(new QPushButton(this)),
    m_loop(new QPushButton(this)),
    m_random(new QPushButton(this))
{
    m_loop->setCheckable(true);
}

void PlayListButtonsV::init()
{
    this->setLayout(m_mainLayout.get());
    m_mainLayout->setSpacing(5);
    m_mainLayout->setContentsMargins(5, 5, 5, 5);
    setButton(m_addTrack.get(), "+", "Add Tracks");
    setButton(m_removeTrack.get(), "-", "Remove Selected Track");
    setButton(m_addDirTracks.get(), "...", "Add Directory of Tracks");
    setButtonImg(m_loop.get(), "img/ButtonsIcons/loop.png", "Infinite");
    setButtonImg(m_random.get(), "img/ButtonsIcons/random.png", "Random");
}

QPushButton *PlayListButtonsV::addTrack()
{
    return m_addTrack.get();
}

QPushButton *PlayListButtonsV::removeTrack()
{
    return m_removeTrack.get();
}

QPushButton *PlayListButtonsV::addDirTracks()
{
    return m_addDirTracks.get();
}

QPushButton *PlayListButtonsV::loop()
{
    return m_loop.get();
}

QPushButton *PlayListButtonsV::random()
{
    return m_random.get();
}

void PlayListButtonsV::setButton(QAbstractButton *button, QString name, QString tooltip)
{
    button->setText(name);
    button->setFixedHeight(this->height() - 10);
    button->setFixedWidth((this->width() - 30) * 0.2);
    button->setFont(QFont("Tahoma", button->height() / 1.8, QFont::Bold, false));
    button->setToolTip(tooltip);
    m_mainLayout->addWidget(button);
}

void PlayListButtonsV::setButtonImg(QAbstractButton *button, QString name, QString tooltip)
{
    button->setIcon(QIcon(QPixmap(name)));
    button->setIconSize(QSize(30, 30));
    button->setFixedHeight(this->height() - 10);
    button->setFixedWidth((this->width() - 30) * 0.2);
    button->setFont(QFont("Tahoma", button->height() / 1.8, QFont::Bold, false));
    button->setToolTip(tooltip);
    m_mainLayout->addWidget(button);
}
