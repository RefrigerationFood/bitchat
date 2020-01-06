#include <Interface/InterfaceFactory.hpp>

#include "CInterface.hpp"

namespace Client {
namespace Interface {
namespace InterfaceFactory {
InterfacePtr createInstance(SettingsManager::SettingsManagerPtr settings_manager)
{
    return InterfacePtr(new CInterface(std::move(settings_manager)));
}
} // namespace InterfaceFactory
} // namespace Interface
} // namespace Client