#ifndef NETWORKMANAGER_HPP
#define NETWORKMANAGER_HPP

#include <QNetworkAccessManager>

#include <functional>

class NetworkRequest {
public:
  explicit NetworkRequest();
  virtual ~NetworkRequest() = 0;

  virtual std::string& path() const = 0;
  virtual std::string& basePath() const = 0;
  virtual std::string& verb() const = 0;
};

class NetworkResponse {

public:
  inline QNetworkReply::NetworkError error() const { return _error; }
  QByteArray data() const { return _data; }
  int responseCode() const { return _responseCode; }

private:
  QNetworkReply::NetworkError _error;
   QByteArray _data;
   int _responseCode;
};

class NetworkManager
{
public:
  static NetworkManager& instance();

  void sendRequest(NetworkRequest& request, void (*callback)(NetworkResponse response));

private:
  NetworkManager();

private:
  std::unique_ptr<QNetworkAccessManager> _manager;
};

#endif // NETWORKMANAGER_HPP
