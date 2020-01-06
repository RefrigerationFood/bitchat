#include "CInterface.hpp"

#include <cstring>
#include <ncurses.h>

using namespace Client::Interface;

CInterface::CInterface()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);
    keypad(stdscr, TRUE);

    getmaxyx(stdscr, m_length, m_width);
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
    mvprintw(m_length - 1, 0, "> %s", m_draft.c_str());
    mvprintw(m_length - 2, 0, "%s", std::string(m_width, '-').c_str());
}
