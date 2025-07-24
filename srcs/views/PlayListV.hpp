#pragma once

#include <QWidget>
#include <QLayout>
#include <QTableView>

#include "PlayListButtonsV.hpp"

class PlayListV : public QWidget
{
    Q_OBJECT
public:
    explicit PlayListV(QWidget *parent = nullptr);

    void init();

    QTableView *table() const;
    PlayListButtonsV *buttons() const;
    int getSelectedRow() const;

public slots:
    void displayTable(QAbstractTableModel *model);
    void setCurrentIndex(int row);

private:
    std::unique_ptr<QVBoxLayout>        m_mainLayout;
    std::unique_ptr<QTableView>         m_playList;
    std::unique_ptr<PlayListButtonsV>   m_buttons;

};
