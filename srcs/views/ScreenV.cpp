#include "ScreenV.hpp"

#include <QApplication>
#include <QScreen>

ScreenV::ScreenV(QWidget *parent) :
    QVideoWidget(parent)
{

}

void ScreenV::setSize(QSize size)
{
    m_size = size;
}

void ScreenV::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (!isFullScreen()) {
        setFullScreen(true);
        setFixedSize(QApplication::primaryScreen()->size());
    }
    else {
        setFullScreen(false);
        setFixedSize(m_size);
    }
}
