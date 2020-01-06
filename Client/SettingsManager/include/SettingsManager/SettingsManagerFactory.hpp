#pragma once

#include "ISettingsManager.hpp"

namespace Client {
namespace SettingsManager {
namespace SettingsManagerFactory {
SettingsManagerPtr createInstance();
}
} // namespace SettingsManager
} // namespace Client