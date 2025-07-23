#pragma once

#include <QObject>

#include "../models/MediaPlayerM.hpp"
#include "../views/MediaPlayerV.hpp"

class MediaPlayerC : public QObject
{
    Q_OBJECT
public:
    explicit MediaPlayerC(QWidget *cw, QObject *parent = nullptr);


signals:

private:
    std::unique_ptr<MediaPlayerM>   m_model;
    std::unique_ptr<MediaPlayerV>   m_view;
    QWidget                         *m_cw;

    void setConnects();
    void setModelConnects();
    void setPlayListButtonsConnects();
    void setPlayListConnects();
    void setPlayerConnects();

private slots:
    void onAddTrack();
    void onRemoveTrack();
    void onAddDirTracks();

};

