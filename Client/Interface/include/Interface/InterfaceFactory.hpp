#pragma once

#include "IInterface.hpp"

#include <SettingsManager/ISettingsManager.hpp>

namespace Client {
namespace Interface {
namespace InterfaceFactory {
InterfacePtr createInstance(SettingsManager::SettingsManagerPtr settings_manager);
}
} // namespace Interface
} // namespace Client