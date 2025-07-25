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
    void addTrack(const QString &track);
    void removeTrack(const int track);
    void onVolumeChanged(const int volume);
    void onPositionChanged(const qint64 pos);
    void onLoopChanged(const bool state);
    void onRandomChanged(const bool state);
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void onErrorThrown(QMediaPlayer::Error error, const QString &errorString);

signals:
    void modelTableChanged(QAbstractTableModel *model);
    void stoppedChanged(const bool stopped);
    void pausedChanged(const bool paused);
    void tracksListEmptyChanged(const bool empty);
    void trackChanged(const QString &name, const QImage &img, const int nbTrack);
    void displayChanged(const bool img);

private slots:
    void onTackAdded(const QStringList track);

private:
    std::shared_ptr<QMediaPlayer>       m_player;
    std::shared_ptr<QAudioOutput>       m_audioOutput;
    std::shared_ptr<TracksTableM>       m_table;
    QList<std::shared_ptr<AudioFileM>>  m_playList;
    QList<int>                          m_randOrder;
    int                                 m_curTrack;
    bool                                m_loop;
    bool                                m_random;
    bool                                m_stopped;
    bool                                m_paused;

    void setConnects();
    void setRandomTracks();
    int selectTrack();

};
