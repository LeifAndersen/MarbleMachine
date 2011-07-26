#include "Mapper.h"

Mapper::Mapper(QWidget *parent)
    : QWidget(parent)
{
    QGridLayout * gridLayout = new QGridLayout;

    gridLayout->setSpacing(5);

    setLayout(gridLayout);
}

Mapper::~Mapper()
{

}
