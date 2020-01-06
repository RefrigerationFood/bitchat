#pragma once

#include <SettingsManager/ISettingsManager.hpp>
#include <thread>

namespace Client {
namespace SettingsManager {
class CSettingsManager : public ISettingsManager
{
public:
    CSettingsManager();
    ~CSettingsManager();
    IntegerAttribute& getTerminalWidthAttribute() final;
    IntegerAttribute& getTerminalLengthAttribute() final;
    StringAttribute& getClientNameAttribute() final;

private:
    void updateValues();

private:
    std::thread m_updating_thread;
    bool m_run;
    IntegerAttribute m_terminal_width_attribute;
    IntegerAttribute m_terminal_length_attribute;
    StringAttribute m_client_name_attribute;
};
} // namespace SettingsManager
} // namespace Client