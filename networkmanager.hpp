#ifndef NETWORKMANAGER_HPP
#define NETWORKMANAGER_HPP

#include <QNetworkAccessManager>
#include <QSignalMapper>
#include <QNetworkReply>

#include <functional>

class NetworkRequest {
public:
  virtual ~NetworkRequest() = 0;

  std::string& path() { return _path; }
  std::string& basePath() { return _basePath; }
  std::string& verb() { return _verb; }

protected:
  std::string _path;
  std::string _basePath;
  std::string _verb;
};

class NetworkResponse {

public:
  NetworkResponse() :
    NetworkResponse{QByteArray{}, 200, QNetworkReply::NoError}
  {}

  NetworkResponse(QByteArray data, int responseCode, QNetworkReply::NetworkError error) :
    _error{error},
    _data{data},
    _responseCode{responseCode} {}

  QNetworkReply::NetworkError error() const { return _error; }
  QByteArray data() const { return _data; }
  int responseCode() const { return _responseCode; }

private:
  QNetworkReply::NetworkError _error;
  QByteArray _data;
  int _responseCode;
};

class NetworkManager : public QObject
{
  Q_OBJECT

public:
  static NetworkManager& instance();

  void sendRequest(NetworkRequest& request, std::function<void(NetworkResponse)> callback);

private:
  explicit NetworkManager(QObject* parent = nullptr);

private slots:
  void downloadFinished(int);

private:
  struct Task;
  QNetworkAccessManager* _manager;
  QSignalMapper* _mapper;
  QHash<int, Task*> _replies;

private:
  struct Task {
  public:
    QNetworkReply* reply;
    std::function<void(NetworkResponse)> callback;
  };
};

#endif // NETWORKMANAGER_HPP
