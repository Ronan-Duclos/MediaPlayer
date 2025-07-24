#include "MediaPlayerC.hpp"

#include <QFileDialog>

MediaPlayerC::MediaPlayerC(QWidget *cw, QObject *parent) :
    QObject{parent}, m_cw(cw),
    m_model(new MediaPlayerM()),
    m_view(new MediaPlayerV())
{
    QVBoxLayout tmp;

    tmp.addWidget(m_view.get());
    m_cw->setLayout(&tmp);

    m_view->setMinimumHeight(cw->height());
    m_view->setMinimumWidth(cw->width());
    m_view->init();
    m_model->setVidoPlayer(m_view->playScreen()->vdoScreen());

    setConnects();
}

void MediaPlayerC::setConnects()
{
    setModelConnects();
    setPlayListButtonsConnects();
    setPlayListConnects();
    setPlayerConnects();
}

void MediaPlayerC::setModelConnects()
{
    PlayerButtonsV *playerB = m_view->player()->buttons();
    PlayScreenV *screen = m_view->playScreen();

    QObject::connect(m_model.get(), &MediaPlayerM::trackChanged, this, &MediaPlayerC::onTrackChanged);
    QObject::connect(m_model.get(), &MediaPlayerM::displayChanged, screen, &PlayScreenV::onDisplayChanged);
    QObject::connect(m_model.get(), &MediaPlayerM::tracksListEmptyChanged, playerB, &PlayerButtonsV::setPlayList);
    QObject::connect(m_model.get(), &MediaPlayerM::stoppedChanged, playerB, &PlayerButtonsV::setStop);
    QObject::connect(m_model.get(), &MediaPlayerM::pausedChanged, playerB, &PlayerButtonsV::setPause);
}

void MediaPlayerC::setPlayListButtonsConnects()
{
    PlayListButtonsV *bs = m_view->playList()->buttons();
    QPushButton *bAddTrack = bs->addTrack();
    QPushButton *bRemoveTrack = bs->removeTrack();
    QPushButton *bAddDirTrack = bs->addDirTracks();
    QPushButton *cLoop = bs->loop();
    QPushButton *cRandom = bs->random();

    QObject::connect(bAddTrack, &QPushButton::released, this, &MediaPlayerC::onAddTrack);
    QObject::connect(bRemoveTrack, &QPushButton::released, this, &MediaPlayerC::onRemoveTrack);
    QObject::connect(bAddDirTrack, &QPushButton::released, this, &MediaPlayerC::onAddDirTracks);
    QObject::connect(cLoop, &QPushButton::clicked, m_model.get(), &MediaPlayerM::onLoopChanged);
    QObject::connect(cRandom, &QPushButton::clicked, m_model.get(), &MediaPlayerM::onRandomChanged);
}

void MediaPlayerC::setPlayListConnects()
{
    PlayListV *playList = m_view->playList();

    QObject::connect(m_model.get(), &MediaPlayerM::modelTableChanged, playList, &PlayListV::displayTable);
}

void MediaPlayerC::setPlayerConnects()
{
    PlayerButtonsV *bs = m_view->player()->buttons();
    QMediaPlayer *playerM = m_model->player();
    PlayerV *playerV = m_view->player();
    QPushButton *lect = bs->lectButton();
    QPushButton *pause = bs->pauseButton();
    QPushButton *stop = bs->stopButton();
    QPushButton *next = bs->nextButton();
    QPushButton *prev = bs->prevButton();

    QObject::connect(playerM, &QMediaPlayer::durationChanged, playerV, &PlayerV::onDurationChanged);
    QObject::connect(playerM, &QMediaPlayer::positionChanged, playerV, &PlayerV::onPositionChanged);
    QObject::connect(playerV, &PlayerV::positionChanged, m_model.get(), &MediaPlayerM::onPositionChanged);
    QObject::connect(playerV, &PlayerV::volumeChanged, m_model.get(), &MediaPlayerM::onVolumeChanged);
    QObject::connect(lect, &QPushButton::released, m_model.get(), &MediaPlayerM::lect);
    QObject::connect(pause, &QPushButton::released, m_model.get(), &MediaPlayerM::pause);
    QObject::connect(stop, &QPushButton::released, m_model.get(), &MediaPlayerM::stop);
    QObject::connect(next, &QPushButton::released, m_model.get(), &MediaPlayerM::next);
    QObject::connect(prev, &QPushButton::released, m_model.get(), &MediaPlayerM::prev);
}

void MediaPlayerC::onAddTrack()
{
    QString trackPath = QFileDialog::getOpenFileName(m_cw, tr("Select Track"),
                                                    QDir::homePath(),
                                                    tr("Sounds Files (*.mp3 *.mpga *.mpg4 *.wav *.wave *.bwf *.mp4 *.avi)")); //,
    if (!trackPath.isEmpty())
        m_model->addTrack(trackPath);
}

void MediaPlayerC::onRemoveTrack()
{
    int trackRow = m_view->playList()->getSelectedRow();
    if (trackRow >= 0)
        m_model->removeTrack(trackRow);
}

void MediaPlayerC::onAddDirTracks()
{
    QString trackDirPath = QFileDialog::getExistingDirectory(m_cw, tr("Select Tracks Directory"),
                                                       QDir::homePath(),
                                                       QFileDialog::ShowDirsOnly);
    if (!trackDirPath.isEmpty()) {
        QDir trackDir(trackDirPath);
        QStringList nameFilter{"*.mp3", "*.mpga", "*.mpg4", "*.wav", "*.wave", "*.bwf", "*.mp4", "*.avi"};

        if (!trackDir.isEmpty()) {
            QStringList files = trackDir.entryList(nameFilter, QDir::Files);

            foreach (QString file, files)
                m_model->addTrack(trackDirPath + '/' + file);
        }
    }
}

void MediaPlayerC::onTrackChanged(const QString &name, const QImage &img, const int nbTrack)
{
    m_view->playScreen()->onTrackChanged(name, img);
    m_view->playList()->setCurrentIndex(nbTrack);
}
