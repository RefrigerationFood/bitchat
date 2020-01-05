#pragma once

#include <KeyCatchingRoutine/IKeyCatchingRoutine.hpp>

#include <atomic>

namespace Client {
namespace KeyCatchingRoutine {

class CKeyCatchingRoutine : public IKeyCatchingRoutine
{
public:
    CKeyCatchingRoutine();
    void start() final;
    void stop() final;
    void setOnKeyPressedCallback(KeyPressedCallback callback) final;
private:
    KeyPressedCallback m_callback;
    std::atomic_bool m_run;
};

}
}