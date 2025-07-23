#pragma once

#include <QVideoWidget>

class ScreenV : public QVideoWidget
{
    Q_OBJECT
public:
    explicit ScreenV(QWidget *parent = nullptr);
    void setSize(QSize size);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    QSize m_size;
};

