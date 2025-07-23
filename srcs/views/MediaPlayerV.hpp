#pragma once

#include <QWidget>
#include <QLabel>
#include <QLayout>

#include "PlayListV.hpp"
#include "PlayerV.hpp"
#include "PlayScreenV.hpp"

class MediaPlayerV : public QWidget
{
    Q_OBJECT
public:
    explicit MediaPlayerV(QWidget *parent = nullptr);

    void init();

    PlayScreenV *playScreen() const;
    PlayListV *playList() const;
    PlayerV *player() const;

private:
    std::unique_ptr<QVBoxLayout>    m_mainLayout;
    std::unique_ptr<QHBoxLayout>    m_secondLayout;
    std::unique_ptr<PlayScreenV>    m_screen;
    std::unique_ptr<PlayListV>      m_playList;
    std::unique_ptr<PlayerV>        m_player;

};

