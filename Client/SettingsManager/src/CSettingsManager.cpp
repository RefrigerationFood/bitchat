#include "CSettingsManager.hpp"

#include <ncurses.h>

using namespace Client::SettingsManager;

CSettingsManager::CSettingsManager()
    : m_run(true)
{
    updateValues();

    m_updating_thread = std::thread([this]() {
        while (m_run)
        {
            updateValues();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });
}

void CSettingsManager::updateValues()
{
    int length, width;

    getmaxyx(stdscr, length, width);

    m_terminal_length_attribute.setValue(length);
    m_terminal_width_attribute.setValue(width);
}

CSettingsManager::~CSettingsManager()
{
    m_run = false;
    m_updating_thread.join();
}

IntegerAttribute& CSettingsManager::getTerminalWidthAttribute()
{
    return m_terminal_width_attribute;
}

IntegerAttribute& CSettingsManager::getTerminalLengthAttribute()
{
    return m_terminal_length_attribute;
}

StringAttribute& CSettingsManager::getClientNameAttribute()
{
    return m_client_name_attribute;
}