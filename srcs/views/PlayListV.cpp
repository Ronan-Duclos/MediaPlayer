#include "PlayListV.hpp"

#include <QLabel>

PlayListV::PlayListV(QWidget *parent) :
    QWidget{parent}, m_mainLayout(new QVBoxLayout(this)),
    m_playList(new QTableView(this)),
    m_buttons(new PlayListButtonsV(this))
{

}

void PlayListV::init()
{
    m_mainLayout->setSpacing(5);
    m_mainLayout->setContentsMargins(5, 5, 5, 5);
    m_playList->setFixedWidth(this->width() - 15);
    m_playList->setFixedHeight((this->height() - 15) * 0.9);
    m_buttons->setFixedWidth(this->width() - 15);
    m_buttons->setFixedHeight((this->height() - 15) * 0.1);

    this->setLayout(m_mainLayout.get());
    m_mainLayout->addWidget(m_playList.get());
    m_mainLayout->addWidget(m_buttons.get());
    m_buttons->init();
    m_playList->setSelectionBehavior(QAbstractItemView::SelectRows);
}

QTableView *PlayListV::table() const
{
    return m_playList.get();
}

PlayListButtonsV *PlayListV::buttons() const
{
    return m_buttons.get();
}

int PlayListV::getSelectedRow() const
{
    return m_playList->currentIndex().row();
}

void PlayListV::displayTable(QAbstractTableModel *model)
{
    m_playList->setModel(model);
}

void PlayListV::setCurrentIndex(int row)
{
    m_playList->selectRow(row);
}

