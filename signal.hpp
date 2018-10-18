#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include <functional>
#include <map>

template <typename... Args>
class Signal
{
public:
    Signal() : current_id_(0) {}

    // 连接一个成员函数到 Signal
    template <typename T>
    int connect(T *inst, void (T::*func)(Args...)) {
        return connect([=] (Args... args) {
            (inst->*func)(args...);
        });
    };

    // 连接一个 std::function 到 signal.
    // 返回一个 id，可以用于 disconnect.
    int connect(std::function<void(Args...)> const& slot) const {
        slots_.insert(std::make_pair(++current_id_, slot));
        return current_id_;
    }

    // 断开连接的函数
    void disconnect(int id) const {
        slots_.erase(id);
    }

    // 断开所有连接的函数
    void disconnect_all() const {
        slots_.clear();
    }

    // 调用所有已连接的函数.
    void emit(Args... p) {
        for (auto it : slots_) {
            it.second(p...);
        }
    }

private:
    // Google C++ 命名规则，难受啊马飞~
    mutable std::map<int, std::function<void(Args...)>> slots_;
    mutable int current_id_;
};

#endif
