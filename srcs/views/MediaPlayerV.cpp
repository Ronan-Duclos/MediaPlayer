#include "MediaPlayerV.hpp"

MediaPlayerV::MediaPlayerV(QWidget *parent) :
    QWidget{parent}, m_mainLayout(new QVBoxLayout(this)),
    m_secondLayout(new QHBoxLayout),
    m_screen(new PlayScreenV(this)),
    m_playList(new PlayListV(this)),
    m_player(new PlayerV(this))
{

}

void MediaPlayerV::init()
{
    m_mainLayout->setSpacing(5);
    m_mainLayout->setContentsMargins(5, 5, 5, 5);
    m_screen->setFixedHeight((this->height() - 15) * 0.8);
    m_screen->setFixedWidth((this->width() - 15) * 0.434);
    m_playList->setFixedHeight((this->height() - 15) * 0.8);
    m_playList->setFixedWidth((this->width() - 15) * 0.564);
    m_player->setFixedHeight((this->height() - 15) * 0.2);
    m_player->setFixedWidth(this->width() - 15);

    this->setLayout(m_mainLayout.get());
    m_secondLayout->addWidget(m_screen.get());
    m_secondLayout->addWidget(m_playList.get());
    m_mainLayout->addLayout(m_secondLayout.get());
    m_mainLayout->addWidget(m_player.get());
    m_playList->init();
    m_player->init();
    m_screen->init();
}

PlayScreenV *MediaPlayerV::playScreen() const
{
    return m_screen.get();
}

PlayListV *MediaPlayerV::playList() const
{
    return m_playList.get();
}

PlayerV *MediaPlayerV::player() const
{
    return m_player.get();
}
