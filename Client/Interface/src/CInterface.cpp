#include "CInterface.hpp"

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

void CInterface::setMessages(const std::vector<Client::Common::Types::ChatMessage>& text) {}

void CInterface::render()
{
    clear();
    refresh();

    mvprintw(m_length - 2, 0, "%s", std::string(m_width, '-').c_str());
    mvprintw(m_length - 1, 0, "> %s", m_draft.c_str());
}
