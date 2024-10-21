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
        std::function<void(Event)> _callee;
    };

    template<typename Event>
    class Listener {
        ListenCounter<Event>* _counter;

    public:
        Listener(std::function<void(Event)> callee)
            : _counter(new ListenCounter<Event>(0, callee)) {}

        ~Listener() {
            _counter->_callee = nullptr;
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
    };
}

#endif //LISTENER_H
