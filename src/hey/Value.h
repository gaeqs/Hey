//
// Created by gaeqs on 21/10/2024.
//

#ifndef VALUE_H
#define VALUE_H

namespace hey {
    template<typename T>
    class Value {
    public:
        virtual ~Value() = default;

        virtual std::conditional_t<std::is_reference_v<T>, const std::remove_reference_t<T>&, T> getValue() const = 0;

        virtual T getValue() = 0;
    };
}

#endif //VALUE_H
