//
// Created by gaeqs on 21/10/24.
//

#ifndef OBSERVABLEVALUE_H
#define OBSERVABLEVALUE_H

#include <hey/Observable.h>
#include <hey/Value.h>

namespace hey {
    template<typename T>
    class ObservableValue : public Observable<T>, public Value<T> {
        T _value;

    public:
        ObservableValue() = default;

        ObservableValue(const T& value) : _value(value) {}

        ObservableValue(T&& value) : _value(std::move(value)) {}

        ~ObservableValue() override = default;

        T getValue() override {
            return _value;
        }

        T getValue() const override {
            return _value;
        }

        void setValue(const T& value) {
            _value = value;
            this->invoke(_value);
        }

        void setValue(T&& value) {
            _value = std::move(value);
            this->invoke(_value);
        }

        ObservableValue& operator=(const T& other) {
            _value = std::move(other);
            this->invoke(_value);
            return *this;
        }

        ObservableValue& operator=(T&& other) {
            _value = std::move(other);
            this->invoke(_value);
            return *this;
        }
    };
}
#endif //OBSERVABLEVALUE_H
