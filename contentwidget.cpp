#include "contentwidget.hpp"
#include "ui_contentwidget.h"

ContentWidget::ContentWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ContentWidget)
{
  ui->setupUi(this);
}

ContentWidget::~ContentWidget()
{
  delete ui;
}
