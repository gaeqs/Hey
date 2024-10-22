//
// Created by gaeqs on 21/10/2024.
//

#ifndef DERIVEDVALUE_H
#define DERIVEDVALUE_H

namespace hey {
    template<typename T, typename... D>
    class DerivedValue : public Value<T>, public Observable<T> {
        std::tuple<Listener<D>...> _listeners;
        std::tuple<const Value<D>*...> _values;
        std::function<T(D...)> _mapper;
        T _result;

        void refreshValue() {
            std::apply([this](const Value<D>*... args) {
                _result = _mapper(args->getValue()...);
                this->invoke(_result);
            }, _values);
        }

        template<typename V>
        Listener<V> createListener(const Value<V>& value) {
            auto* obs = dynamic_cast<const Observable<V>*>(&value);
            if (obs != nullptr) {
                return obs->createListener([this](const auto&) {
                    refreshValue();
                });
            }
            return Listener<V>();
        }

    public:
        template<typename Fun>
        explicit DerivedValue(Fun fun, const Value<D>&... obs)
            : _listeners(std::make_tuple(createListener<D>(obs)...)),
              _values(&obs...),
              _mapper(fun) {
            refreshValue();
        }

        ~DerivedValue() override = default;

        T getValue() const override {
            return _result;
        }

        T getValue() override {
            return _result;
        }
    };
}

#endif //DERIVEDVALUE_H
