#include "CController.hpp"

using namespace Client::Controller;

CController::CController(
    ServerProxy::ServerProxyPtr server_proxy,
    Interface::InterfacePtr interface)
    : m_server_proxy(std::move(server_proxy))
    , m_interface(std::move(interface))
{
    m_interface->setDraft(m_draft);
}

void CController::processInput(char c)
{
    m_draft += c;
    m_interface->setDraft(m_draft);
}
