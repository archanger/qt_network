#ifndef CONTENTWIDGET_HPP
#define CONTENTWIDGET_HPP

#include <QWidget>
#include "networkmanager.hpp"

class Request : public NetworkRequest
{
public:
  Request();
  ~Request();
};

namespace Ui {
  class ContentWidget;
}

class ContentWidget : public QWidget
{
  Q_OBJECT

public:
  explicit ContentWidget(QWidget *parent = nullptr);
  ~ContentWidget();

public slots:
  void loadData();

private:
  void loaded(NetworkResponse response);

private:
  Ui::ContentWidget *ui;
};

#endif // CONTENTWIDGET_HPP
