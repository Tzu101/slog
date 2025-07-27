#pragma once

#include <string>

namespace slog {

enum Level {
    TRACE,
    DEBUG,
    EVENT,
    ALERT,
    ERROR,
    FATAL
};

using callback = void(Level level, const std::string& message);

}  // namespace slog
