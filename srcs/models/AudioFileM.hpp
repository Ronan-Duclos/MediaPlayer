#pragma once

#include <QObject>
#include <QMediaPlayer>
#include <QImage>

class AudioFileM : public QObject
{
    Q_OBJECT
public:
    explicit AudioFileM(QString path, QObject *parent = nullptr);

    QString path() const;
    QString singer() const;
    QString title() const;
    QString album() const;
    qint64 duration() const;
    QString durationToString() const;
    QImage image()const;
    std::shared_ptr<AudioFileM> next();
    void setNext(const std::shared_ptr<AudioFileM> next);
    void unSetNext();
    void setInfo();

signals:
    void trackAdded(QStringList track);

private slots:
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);

private:
    QString m_path;
    QString m_singer;
    QString m_title;
    QString m_album;
    qint64 m_duration;
    QImage m_img;
    QMediaPlayer *m_mp;
    std::shared_ptr<AudioFileM> m_next;

    void setImage();
};
