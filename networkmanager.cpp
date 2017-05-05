#include "networkmanager.hpp"

NetworkManager& NetworkManager::instance()
{
  static NetworkManager __instance;
  return __instance;
}

void NetworkManager::sendRequest(NetworkRequest& request, void (*callback)(NetworkResponse response))
{
  callback(NetworkResponse{});
}

NetworkManager::NetworkManager() :
  _manager{new QNetworkAccessManager{}}
{

}
