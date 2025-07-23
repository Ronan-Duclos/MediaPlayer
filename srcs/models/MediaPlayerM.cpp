#include "MediaPlayerM.hpp"
#include <QDebug>
#include <QMediaMetaData>
#include <QRandomGenerator>

MediaPlayerM::MediaPlayerM(QObject *parent) :
    QObject{parent}, m_curTrack(0), m_loop(false),
    m_random(false), m_stopped(true), m_paused(false),
    m_player(new QMediaPlayer(this)),
    m_audioOutput(new QAudioOutput(m_player.get())),
    m_table(new TracksTableM(this))
{
    m_player->setAudioOutput(m_audioOutput.get());
    m_audioOutput->setVolume(50);
    setConnects();
}

void MediaPlayerM::lect()
{
    if (m_playList.size() > 0) {
        if (!m_paused) {
            if (m_random)
                m_curTrack = QRandomGenerator::global()->generate();
            std::shared_ptr<AudioFileM> track = m_playList.at(m_curTrack);
            m_player->setSource(QUrl::fromLocalFile(track->path()));
            emit trackChanged(track->title(), track->image());
            if (track->path().endsWith(".mp4") || track->path().endsWith(".avi"))
                emit displayChanged(false);
            else
                emit displayChanged(true);
        }
        else
            emit pausedChanged(m_paused = false);
        m_player->play();
        m_stopped = false;
        emit stoppedChanged(m_stopped);
    }
}

void MediaPlayerM::pause()
{
    m_player->pause();
    m_paused = true;
    emit pausedChanged(true);
}

void MediaPlayerM::stop()
{
    m_player->stop();
    m_stopped = true;
    emit stoppedChanged(m_stopped);
}

void MediaPlayerM::next()
{
    if (!m_stopped) {
        if (m_curTrack == m_playList.size() - 1) {
            if (m_loop) {
                m_curTrack = 0;
                lect();
            }
            else
                stop();
        }
        else {
            m_curTrack++;
            lect();
        }
    }
    else
        qDebug() << "NextFuck";
}

void MediaPlayerM::prev()
{
    if (!m_stopped) {
        if (m_player->position() < 5000) {
            if (m_curTrack == 0 && m_loop)
                m_curTrack = m_playList.size() - 1;
            else if (m_curTrack > 0) {
                m_curTrack--;
                lect();
            }
            else
                stop();
        }
        else
            m_player->setPosition(0);
    }
    else
        qDebug() << "PrevFuck";
}

void MediaPlayerM::addTrack(const QString &Track)
{
    foreach (std::shared_ptr<AudioFileM> file, m_playList) {
        if (file->path() == Track) {
            qDebug() << "File " + Track + " already added.";
            return ;
        }
    }
    bool empty = m_playList.isEmpty();
    std::shared_ptr<AudioFileM> tmp(new AudioFileM(Track));
    m_playList.push_back(tmp);
    QObject::connect(tmp.get(), &AudioFileM::trackAdded, this, &MediaPlayerM::onTackAdded);
    if (empty)
        emit tracksListEmptyChanged(false);
}

void MediaPlayerM::removeTrack(const int Track)
{
    m_playList.remove(Track);
    m_table->removeRow(Track);
    if (m_playList.isEmpty())
        emit tracksListEmptyChanged(true);
}

void MediaPlayerM::setPositionTrack(const qint64 pos)
{
    m_player->setPosition(pos);
}

QList<std::shared_ptr<AudioFileM>> MediaPlayerM::playList() const
{
    return m_playList;
}

QMediaPlayer *MediaPlayerM::player() const
{
    return m_player.get();
}

void MediaPlayerM::setVidoPlayer(QVideoWidget *screen)
{
    m_player->setVideoOutput(screen);
}

int MediaPlayerM::currentTrack() const
{
    return m_curTrack;
}

bool MediaPlayerM::isLoop() const
{
    return m_loop;
}

bool MediaPlayerM::isRandom() const
{
    return m_random;
}

void MediaPlayerM::setVolume(const int volume)
{
    m_audioOutput->setVolume(volume);
}

void MediaPlayerM::setLoop(const bool state)
{
    m_loop = state;
}

void MediaPlayerM::setRandom(const bool state)
{
    m_random = state;
}

void MediaPlayerM::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia)
        next();
}

void MediaPlayerM::onErrorThrown(QMediaPlayer::Error error, const QString &errorString)
{
    qDebug() << "Error:" << error;
    qDebug() << "ErrorStr:" << errorString;
}

void MediaPlayerM::onTackAdded(const QStringList track)
{
    m_table->insertRows(track);
    emit modelTableChanged(m_table.get());

}

void MediaPlayerM::setConnects()
{
    QObject::connect(m_player.get(), &QMediaPlayer::errorOccurred, this, &MediaPlayerM::onErrorThrown);
    QObject::connect(m_player.get(), &QMediaPlayer::mediaStatusChanged, this, &MediaPlayerM::onMediaStatusChanged);
}
