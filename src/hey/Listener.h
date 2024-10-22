//
// Created by gaeqs on 21/10/24.
//

#ifndef LISTENER_H
#define LISTENER_H

#include <functional>

namespace hey {
    template<typename Event>
    struct ListenCounter {
        size_t registered;
        std::function<void(Event)> callee;
        bool active;
    };

    template<typename Event>
    class Listener {
        ListenCounter<Event>* _counter;

    public:
        Listener(const Listener& other) = delete;

        Listener(Listener&& other) noexcept : _counter(other._counter) {
            other._counter = new ListenCounter<Event>(0, nullptr, true);
        }

        Listener() : _counter(new ListenCounter<Event>(0, nullptr, true)) {};

        template<class Fun>
        requires std::is_invocable_v<Fun, Event>
        Listener(Fun callee): _counter(new ListenCounter<Event>(0, callee, true)) {}

        ~Listener() {
            _counter->callee = nullptr;
            _counter->active = false;
            if (_counter->registered == 0) {
                delete _counter;
            }
        }

        ListenCounter<Event>* getCounter() const {
            return _counter;
        }

        [[nodiscard]] size_t getId() const {
            return _counter->id;
        }

        Listener& operator=(std::function<void(Event)> callee) {
            _counter->callee = callee;
            return *this;
        }
    };
}

#endif //LISTENER_H
