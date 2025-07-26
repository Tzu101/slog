#include <slog.h>

int main() {
    size_t test_category = slog::category("test", true);
    slog::fatal(test_category, "This is a fatal message with param {}", 42);
    slog::error(test_category, "This is a error message with param {}", 42);
    slog::alert(test_category, "This is a alert message with param {}", 42);
    slog::event(test_category, "This is a event message with param {}", 42);
    slog::debug(test_category, "This is a debug message with param {}", 42);
    slog::trace(test_category, "This is a trace message with param {1} {0}", 42, 69);
}