#pragma once

#include <Controller/IController.hpp>
#include <Interface/IInterface.hpp>
#include <ServerProxy/IServerProxy.hpp>

namespace Client {
namespace Controller {
class CController : public IController
{
public:
    CController(ServerProxy::ServerProxyPtr server_proxy, Interface::InterfacePtr interface);
    void processInput(char c) final;

private:
    ServerProxy::ServerProxyPtr m_server_proxy;
    Interface::InterfacePtr m_interface;
    std::string m_draft;
};

} // namespace Controller
} // namespace Client