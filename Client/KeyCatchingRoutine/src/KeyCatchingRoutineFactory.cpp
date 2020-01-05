#include <KeyCatchingRoutine/KeyCatchingRoutineFactory.hpp>
#include "CKeyCatchingRoutine.hpp"

namespace Client {
namespace KeyCatchingRoutine {
namespace KeyCatchingRoutineFactory {
KeyCatchingRoutinePtr createInstance()
{
    return KeyCatchingRoutinePtr(new CKeyCatchingRoutine());
}
}
}
}