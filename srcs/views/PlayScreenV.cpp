#include "PlayScreenV.hpp"

#include <QFont>

PlayScreenV::PlayScreenV(QWidget *parent) :
    QWidget(parent), m_mainLayout(new QVBoxLayout(this)),
    m_titleTrack(new QLabel(this)), m_sw(new QStackedWidget(this)),
    m_imgDisplay(new QLabel(this)), m_vdoDisplay(new ScreenV(this))
{

}

void PlayScreenV::init()
{
    m_mainLayout->setSpacing(5);
    m_mainLayout->setContentsMargins(5, 5, 5, 5);

    m_titleTrack->setFixedHeight((this->height() - 15) * 0.1);
    m_titleTrack->setFixedWidth(this->width() - 15);
    m_sw->setFixedHeight((this->height() - 15) * 0.9);
    m_sw->setFixedWidth(this->width() - 15);
    m_vdoDisplay->setSize(QSize(this->width(), this->height() * 0.9));

    initTitleLabel();
    initImgLabel();

    m_mainLayout->addWidget(m_sw.get());
    m_mainLayout->addWidget(m_titleTrack.get());
    m_sw->addWidget(m_imgDisplay.get());
    m_sw->addWidget(m_vdoDisplay.get());
    m_sw->setCurrentIndex(0);
}

QVideoWidget *PlayScreenV::vdoScreen() const
{
    return m_vdoDisplay.get();
}

QLabel *PlayScreenV::imgScreen() const
{
    return m_imgDisplay.get();
}

void PlayScreenV::onTrackChanged(const QString &title, const QImage &img)
{
    m_titleTrack->setText(title);
    qDebug() << "Image: " << img;
    m_imgDisplay->setPixmap(QPixmap::fromImage(img));
}

void PlayScreenV::onDisplayChanged(const bool img)
{
    if (img)
        m_sw->setCurrentIndex(0);
    else
        m_sw->setCurrentIndex(1);
}

void PlayScreenV::initTitleLabel()
{
    m_titleTrack->setText("---");
    m_titleTrack->setWordWrap(true);
    m_titleTrack->setFont(QFont("Tahoma", 10, QFont::Bold, false));
    m_titleTrack->setAlignment(Qt::AlignCenter);
    m_titleTrack->setStyleSheet("color: rgb(0, 0, 0);");
}

void PlayScreenV::initImgLabel()
{
    m_imgDisplay->setStyleSheet("background-color: rgb(125, 125, 125);");
    m_imgDisplay->setScaledContents(true);
    QImage tmp("img/CanaSky.png");
    m_imgDisplay->setPixmap(QPixmap::fromImage(tmp));
}
