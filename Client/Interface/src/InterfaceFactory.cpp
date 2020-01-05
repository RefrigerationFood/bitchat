#include <Interface/InterfaceFactory.hpp>

#include "CInterface.hpp"

namespace Client {
namespace Interface {
namespace InterfaceFactory {
InterfacePtr createInstance()
{
    return InterfacePtr(new CInterface());
}
} // namespace InterfaceFactory
} // namespace Interface
} // namespace Client