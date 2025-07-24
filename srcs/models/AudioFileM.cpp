#include "AudioFileM.hpp"

#include <QMediaMetaData>
#include <QVariant>

AudioFileM::AudioFileM(QString path, QObject *parent) :
    QObject{parent}, m_path(path), m_mp(new QMediaPlayer())
{
    QObject::connect(m_mp, &QMediaPlayer::mediaStatusChanged, this, &AudioFileM::onMediaStatusChanged);
    m_mp->setSource(QUrl::fromLocalFile(m_path));
}

QString AudioFileM::path() const
{
    return m_path;
}

QString AudioFileM::singer() const
{
    return m_singer;
}

QString AudioFileM::title() const
{
    return m_title;
}

QString AudioFileM::album() const
{
    return m_album;
}

qint64 AudioFileM::duration() const
{
    return m_duration;
}

QString AudioFileM::durationToString() const
{
    QString ret;
    int m = m_duration / 60000;
    int h = m / 60;
    m = m % 60;
    int rest = m_duration - (m + h * 60) * 60000 ;
    int s = rest / 1000;
    int ms = rest - s * 1000;
    if (h > 0) {
        ret = QString(QString::number(h) + "h" +
                      QString::number(m) + "m" +
                      QString::number(s) + "s" +
                      QString::number(ms) + "ms");
    }
    else if (m > 0) {
        ret = QString(QString::number(m) + "m" +
                      QString::number(s) + "s" +
                      QString::number(ms) + "ms");
    }
    else {
        ret = QString(QString::number(s) + "s" +
                      QString::number(ms) + "ms");
    }
    return ret;
}

QImage AudioFileM::image() const
{
    return m_img;
}

void AudioFileM::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::LoadedMedia)
        setInfo();
}

void AudioFileM::setInfo()
{
    QMediaMetaData tmp = m_mp->metaData();

    m_title = tmp.value(QMediaMetaData::Title).toString();
    if (m_title.isEmpty()) {
        int pos = m_path.lastIndexOf('/') + 1;
        m_title = m_path.sliced(pos, m_path.size() - pos - 5);
    }
    m_singer = tmp.value(QMediaMetaData::ContributingArtist).toString();
    m_album = tmp.value(QMediaMetaData::AlbumTitle).toString();
    m_duration = tmp.value(QMediaMetaData::Duration).toULongLong();

    //setImage();

    disconnect(m_mp, &QMediaPlayer::mediaStatusChanged, this, &AudioFileM::onMediaStatusChanged);
    delete m_mp;
    emit trackAdded({m_title, m_singer, m_album, durationToString()});
}

void AudioFileM::setImage()
{
    /*
    QMediaMetaData tmp = m_mp->metaData();

    foreach (const QMediaMetaData::Key &key, tmp.keys()) {
        qDebug() << key << tmp.value(key);
    }
    cover = QImage::fromData(tmp.value(QMediaMetaData::CoverArtImage).toByteArray());
    qDebug() << "Cover:" << cover;
    QVariant img = tmp.value(QMediaMetaData::ThumbnailImage);
    qDebug() << "ImageQVariant: " << img;
    m_img = img.value<QImage>();
    qDebug() << "ImageQImage:" << m_img;
*/
}
