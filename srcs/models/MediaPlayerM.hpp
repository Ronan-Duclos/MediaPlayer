#pragma once

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QVideoSink>
#include <QAbstractTableModel>

#include "AudioFileM.hpp"
#include "TracksTableM.hpp"

#include <QVideoWidget>

class MediaPlayerM : public QObject
{
    Q_OBJECT

public:
    explicit MediaPlayerM(QObject *parent = nullptr);

    QList<std::shared_ptr<AudioFileM>> playList() const;
    QMediaPlayer *player() const;
    void setVidoPlayer(QVideoWidget *screen);

    int currentTrack() const;
    bool isLoop() const;
    bool isRandom() const;
    bool isStopped() const;


public slots:
    void lect();
    void pause();
    void stop();
    void next();
    void prev();
    void setVolume(const int volume);
    void addTrack(const QString &track);
    void removeTrack(const int track);
    void setPositionTrack(const qint64 pos);
    void setLoop(const bool state);
    void setRandom(const bool state);
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void onErrorThrown(QMediaPlayer::Error error, const QString &errorString);

signals:
    void modelTableChanged(QAbstractTableModel *model);
    void stoppedChanged(const bool stopped);
    void pausedChanged(const bool paused);
    void tracksListEmptyChanged(const bool empty);
    void trackChanged(const QString &name, const QImage &img);
    void displayChanged(const bool img);

private slots:
    void onTackAdded(const QStringList track);
    //void onTrackChanged(const);

private:
    std::shared_ptr<QMediaPlayer>       m_player;
    std::shared_ptr<QAudioOutput>       m_audioOutput;
    std::shared_ptr<TracksTableM>       m_table;
    QList<std::shared_ptr<AudioFileM>>  m_playList;
    int                                 m_curTrack;
    bool                                m_loop;
    bool                                m_random;
    bool                                m_stopped;
    bool                                m_paused;

    void setConnects();

};
