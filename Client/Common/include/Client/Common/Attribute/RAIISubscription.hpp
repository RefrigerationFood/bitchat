#include "TAttribute.hpp"

#include <mutex>

namespace Client {
namespace Common {

template <class T>
class RAIISubscription
{
public:
    RAIISubscription(
        const TAttribute<T>& attribute,
        typename TAttribute<T>::OnUpdateCallback callback)
        : m_attribute(attribute)
    {
        m_subscription = m_attribute.subscribe(callback);
    }

    RAIISubscription(const TAttribute<T>& attribute, T& value_ref)
        : m_attribute(attribute)
    {
        if (m_attribute.isInitialized())
        {
            value_ref = m_attribute.getValue();
        }

        m_subscription = m_attribute.subscribe([&value_ref](T value) { value_ref = value; });
    }

    RAIISubscription(const TAttribute<T>& attribute, T& value_ref, std::mutex& mutex)
        : m_attribute(attribute)
    {
        if (m_attribute.isInitialized())
        {
            std::lock_guard<std::mutex> lock(mutex);
            value_ref = m_attribute.getValue();
        }

        m_subscription = m_attribute.subscribe([&value_ref, &mutex](T value) {
            std::lock_guard<std::mutex> lock(mutex);
            value_ref = value;
        });
    }

    ~RAIISubscription() { m_attribute.unsubscribe(m_subscription); }

private:
    const TAttribute<T>& m_attribute;
    size_t m_subscription;
};

} // namespace Common
} // namespace Client