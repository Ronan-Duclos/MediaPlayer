#pragma once

#include <QWidget>
#include <QLayout>
#include <QStackedWidget>
#include <QLabel>

#include "ScreenV.hpp"

class PlayScreenV : public QWidget
{
    Q_OBJECT

public:
    explicit PlayScreenV(QWidget *parent = nullptr);

    void init();
    QVideoWidget *vdoScreen() const;
    QLabel *imgScreen() const;

signals:


public slots:
    void onTrackChanged(const QString &title, const QImage &img);
    void onDisplayChanged(const bool img);

private:
    std::unique_ptr<QVBoxLayout> m_mainLayout;
    std::unique_ptr<QLabel> m_titleTrack;
    std::shared_ptr<QStackedWidget> m_sw;
    std::shared_ptr<QLabel> m_imgDisplay;
    std::shared_ptr<ScreenV> m_vdoDisplay;

    void initTitleLabel();
    void initImgLabel();
};
