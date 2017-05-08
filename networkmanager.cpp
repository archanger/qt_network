#include "networkmanager.hpp"

#include <QHash>

template <typename T>
int getID(T& obj) {
  return 0; //reinterpret_cast<int>(obj);
}

NetworkManager& NetworkManager::instance()
{
  static NetworkManager __instance;
  return __instance;
}

void NetworkManager::sendRequest(NetworkRequest& request, std::function<void(NetworkResponse)> callback)
{
  QString path = QString::fromUtf8((request.basePath() + request.path()).c_str());
  QNetworkRequest r{QUrl{path}};
  QNetworkReply* reply = _manager->sendCustomRequest(r, request.verb().c_str());
  connect(reply, &QNetworkReply::finished, _mapper, static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));
  int id = getID(reply);

  Task* task = new Task;
  task->callback = callback;
  task->reply = reply;

  _replies.insert(id, task);
  _mapper->setMapping(reply, id);

  callback(NetworkResponse{});
}

NetworkManager::NetworkManager(QObject* parent) :
  QObject{parent},
  _manager{new QNetworkAccessManager{this}},
  _mapper{new QSignalMapper{this}}
{
  connect(_mapper, static_cast<void(QSignalMapper::*)(int)>(&QSignalMapper::mapped), this, &NetworkManager::downloadFinished);
}

void NetworkManager::downloadFinished(int t)
{
  Task* task = _replies.take(t);

  NetworkResponse response{task->reply->readAll(), task->reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(), QNetworkReply::NoError};

  task->callback(response);
  task->reply->deleteLater();
  delete task;
}

NetworkRequest::~NetworkRequest()
{

}
