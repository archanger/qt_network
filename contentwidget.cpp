#include "contentwidget.hpp"
#include "ui_contentwidget.h"

#include <QDebug>

ContentWidget::ContentWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ContentWidget)
{
  ui->setupUi(this);
  connect(ui->button, &QPushButton::clicked, this, &ContentWidget::loadData);
}

ContentWidget::~ContentWidget()
{
  delete ui;
}

void ContentWidget::loadData()
{
  Request request{};
  NetworkManager::instance().sendRequest(request, [this](NetworkResponse response) {
    loaded(response);
  });
}

void ContentWidget::loaded(NetworkResponse response)
{
  ui->content->setText(response.data());
}

Request::Request()
{
  _path = "https://api-estel.letsapp.ru/v3/salon/2";
  _verb = "GET";
}

Request::~Request()
{

}
