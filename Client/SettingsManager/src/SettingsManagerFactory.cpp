#include <SettingsManager/SettingsManagerFactory.hpp>

#include "CSettingsManager.hpp"

namespace Client {
namespace SettingsManager {
namespace SettingsManagerFactory {

SettingsManagerPtr createInstance()
{
    return SettingsManagerPtr(new CSettingsManager());
}

} // namespace SettingsManagerFactory
} // namespace SettingsManager
} // namespace Client