//
// Created by gaeqs on 21/10/24.
//

#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <hey/Listener.h>

namespace hey {
    template<typename Event>
    class Observable {
        std::vector<ListenCounter<Event>*> _counters;

    public:
        Observable() = default;

        ~Observable() {
            for (auto counter: _counters) {
                if (counter->_callee == nullptr && counter->registered == 1) {
                    delete counter;
                } else {
                    --counter->registered;
                }
            }
        }

        void addListener(const Listener<Event>& listener) {
            _counters.push_back(listener.getCounter());
        }

        void invoke(Event event) {
            for (auto counter: _counters) {
                auto callee = counter->_callee;
                if (callee != nullptr) {
                    callee(event);
                }
            }
        }
    };
}

#endif //OBSERVABLE_H
