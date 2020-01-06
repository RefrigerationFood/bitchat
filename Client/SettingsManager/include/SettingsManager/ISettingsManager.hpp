#pragma once

#include <Client/Common/Attribute/TAttribute.hpp>

#include <memory>
#include <string>

namespace Client {
namespace SettingsManager {
using IntegerAttribute = Client::Common::TAttribute<int>;
using StringAttribute = Client::Common::TAttribute<std::string>;

class ISettingsManager
{
public:
    virtual IntegerAttribute& getTerminalWidthAttribute() = 0;
    virtual IntegerAttribute& getTerminalLengthAttribute() = 0;
    virtual StringAttribute& getClientNameAttribute() = 0;
};

using SettingsManagerPtr = std::shared_ptr<ISettingsManager>;

} // namespace SettingsManager
} // namespace Client