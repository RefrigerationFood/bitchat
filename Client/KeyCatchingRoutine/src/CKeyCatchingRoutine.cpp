#include "CKeyCatchingRoutine.hpp"

#include <Common/terminal_functions.hpp>

using namespace Client::KeyCatchingRoutine;

CKeyCatchingRoutine::CKeyCatchingRoutine()
    : m_run(false)
{
}

void CKeyCatchingRoutine::start()
{
    m_run = true;

    while (m_run)
    {
        if (kbhit())
        {
            if (m_callback)
            {
                m_callback(getch());
            }
            else
            {
                std::cerr << "*** ON KEY PRESSED CALLBACK IS NOT SET ***" << std::endl;
            }
        }
    }
}

void CKeyCatchingRoutine::stop()
{
    m_run = false;
}

void CKeyCatchingRoutine::setOnKeyPressedCallback(
    Client::KeyCatchingRoutine::KeyPressedCallback callback)
{
    m_callback = callback;
}
