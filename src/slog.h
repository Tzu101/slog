#pragma once

#include <memory>
#include <string>
#include <vector>

#include "slog_types.h"

#if defined(_WIN32)
#define NOGDI   // All GDI defines and routines
#define NOUSER  // All USER defines and routines
#endif

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

namespace {

std::vector<std::shared_ptr<spdlog::logger>> log_categories;

auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs.log", true);

constexpr auto FATAL_PATTERN = "[%H:%M:%S] [%^FATAL%$] [%n] %v";
constexpr auto ERROR_PATTERN = "[%H:%M:%S] [%^ERROR%$] [%n] %v";
constexpr auto ALERT_PATTERN = "[%H:%M:%S] [%^ALERT%$] [%n] %v";
constexpr auto EVENT_PATTERN = "[%H:%M:%S] [%^EVENT%$] [%n] %v";
constexpr auto DEBUG_PATTERN = "[%H:%M:%S] [%^DEBUG%$] [%n] %v";
constexpr auto TRACE_PATTERN = "[%H:%M:%S] [%^TRACE%$] [%n] %v";

}  // namespace

namespace slog {

size_t category(const char* name, bool debug) {
    size_t category_id = log_categories.size();
    auto category_logger = std::make_shared<spdlog::logger>(name, spdlog::sinks_init_list{console_sink, file_sink});

    if (debug) {
        category_logger->set_level(spdlog::level::trace);
    } else {
        category_logger->set_level(spdlog::level::info);
    }

    log_categories.emplace_back(category_logger);
    return category_id;
}

template <typename... Args>
void fatal(size_t category_id, spdlog::format_string_t<Args...> fmt, Args&&... args) {
    auto& category = log_categories[category_id];
    category->set_pattern(FATAL_PATTERN);
    category->critical(fmt, std::forward<Args>(args)...);
}

template <typename... Args>
void error(size_t category_id, spdlog::format_string_t<Args...> fmt, Args&&... args) {
    auto& category = log_categories[category_id];
    category->set_pattern(ERROR_PATTERN);
    category->error(fmt, std::forward<Args>(args)...);
}

template <typename... Args>
void alert(size_t category_id, spdlog::format_string_t<Args...> fmt, Args&&... args) {
    auto& category = log_categories[category_id];
    category->set_pattern(ALERT_PATTERN);
    category->warn(fmt, std::forward<Args>(args)...);
}

template <typename... Args>
void event(size_t category_id, spdlog::format_string_t<Args...> fmt, Args&&... args) {
    auto& category = log_categories[category_id];
    category->set_pattern(EVENT_PATTERN);
    category->info(fmt, std::forward<Args>(args)...);
}

template <typename... Args>
void debug(size_t category_id, spdlog::format_string_t<Args...> fmt, Args&&... args) {
    auto& category = log_categories[category_id];
    category->set_pattern(DEBUG_PATTERN);
    category->debug(fmt, std::forward<Args>(args)...);
}

template <typename... Args>
void trace(size_t category_id, spdlog::format_string_t<Args...> fmt, Args&&... args) {
    auto& category = log_categories[category_id];
    category->set_pattern(TRACE_PATTERN);
    category->trace(fmt, std::forward<Args>(args)...);
}

}  // namespace slog
