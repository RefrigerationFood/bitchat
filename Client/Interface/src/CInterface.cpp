#include "CInterface.hpp"

#include <ncurses.h>

using namespace Client::Interface;

CInterface::CInterface(SettingsManager::SettingsManagerPtr settings_manager)
    : m_settings_manager(std::move(settings_manager))
    , m_length_subscription(m_settings_manager->getTerminalLengthAttribute(), m_length, m_mutex)
    , m_width_subscription(m_settings_manager->getTerminalWidthAttribute(), m_width, m_mutex)
{
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);
    keypad(stdscr, TRUE);
}

CInterface::~CInterface()
{
    def_prog_mode();
}

void CInterface::setDraft(const std::string& text)
{
    m_draft = text;

    render();
}

void CInterface::setMessages(const std::vector<Client::Common::Types::ChatMessage>& messages)
{
    m_messages = messages;

    render();
}

void CInterface::render()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    clear();
    refresh();

    int i = 0;
    for (auto& message : m_messages)
    {
        std::string author = message.from_current_user ? "me" : message.author;
        mvprintw(i, 0, "%-20s | %s", author.c_str(), message.text.c_str());
        ++i;
    }
    auto lenghth = m_length;
    mvprintw(m_length - 1, 0, "> %s", m_draft.c_str());
    mvprintw(m_length - 2, 0, "%s", std::string(m_width, '-').c_str());
}
