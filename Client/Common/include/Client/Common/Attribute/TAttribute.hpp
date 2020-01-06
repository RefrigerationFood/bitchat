#pragma once

#include <boost/optional.hpp>
#include <functional>
#include <map>
#include <mutex>

namespace Client {
namespace Common {

template <class T>
class TAttribute
{
public:
    using OnUpdateCallback = std::function<void(const T&)>;

public:
    TAttribute()
        : counter(0)
    {
    }

    void setValue(const T& value)
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        if (!m_value_opt.is_initialized() || m_value_opt.get() != value)
        {
            m_value_opt = value;

            for (auto subscription : m_subscriptions)
            {
                subscription.second(m_value_opt.get());
            }
        }
    }

    const T& getValue() const
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        return m_value_opt.get();
    }

    bool isInitialized() const { return m_value_opt.is_initialized(); }

    size_t subscribe(OnUpdateCallback callback) const
    {
        std::lock_guard<std::mutex> lock(m_subscription_mutex);

        m_subscriptions[counter] = callback;
        return counter++;
    }

    void unsubscribe(size_t subscription) const
    {
        std::lock_guard<std::mutex> lock(m_subscription_mutex);

        m_subscriptions.erase(subscription);
    }

private:
    boost::optional<T> m_value_opt;
    mutable std::map<size_t, OnUpdateCallback> m_subscriptions;
    mutable size_t counter;
    mutable std::mutex m_mutex;
    mutable std::mutex m_subscription_mutex;
};
} // namespace Common
} // namespace Client