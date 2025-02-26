#pragma once

#include <ctime>
#ifdef __linux__
#include <sys/time.h>
#endif
#include <string>

#include "fmt/color.h"
#include "fmt/core.h"

namespace lg {

struct LogTime {
#ifdef __linux__
  timeval tv;
#else
  time_t tim;

#endif
};

// Logging API
enum class level {
  trace = 0,
  debug = 1,
  info = 2,
  warn = 3,
  error = 4,
  die = 5,
  off_unless_die = 6,
  off = 7
};

void set_file(const std::string& filename,
              const bool should_rotate = true,
              const bool append = false,
              const std::string& dir = "");
void set_flush_level(level log_level);
void set_file_level(level log_level);
void set_stdout_level(level log_level);
void set_max_debug_levels();
void disable_ansi_colors();
void initialize();
void finish();

void log_message(level log_level, const LogTime& now, const char* message);
void log_print(const char* message);
void log_print_essential(const char* message);

template <typename... Args>
void log(level log_level, const std::string& format, Args&&... args) {
  LogTime now;
#ifdef __linux__
  gettimeofday(&now.tv, nullptr);
#else
  now.tim = time(nullptr);
#endif
  std::string formatted_message = fmt::format(fmt::runtime(format), std::forward<Args>(args)...);
  log_message(log_level, now, formatted_message.c_str());
}

template <typename... Args>
void print(const std::string& format, Args&&... args) {
#ifndef NO_LOG
  std::string formatted_message = fmt::format(fmt::runtime(format), std::forward<Args>(args)...);
  log_print(formatted_message.c_str());
#endif
}

template <typename... Args>
void print(const fmt::text_style& ts, const std::string& format, Args&&... args) {
#ifndef NO_LOG
  std::string formatted_message = fmt::format(ts, format, std::forward<Args>(args)...);
  log_print(formatted_message.c_str());
#endif
}

template <typename... Args>
void print_essential(const std::string& format, Args&&... args) {
  std::string formatted_message = fmt::format(fmt::runtime(format), std::forward<Args>(args)...);
  log_print_essential(formatted_message.c_str());
}

template <typename... Args>
void print_essential(const fmt::text_style& ts, const std::string& format, Args&&... args) {
  std::string formatted_message = fmt::format(ts, format, std::forward<Args>(args)...);
  log_print_essential(formatted_message.c_str());
}

// same as print but uses the C printf instead of fmt
void printstd(const char* format, va_list arg_list);

template <typename... Args>
void trace(const std::string& format, Args&&... args) {
#ifndef NO_LOG
  log(level::trace, format, std::forward<Args>(args)...);
#endif
}

template <typename... Args>
void debug(const std::string& format, Args&&... args) {
#if DEBUG
#ifndef NO_LOG
  log(level::debug, format, std::forward<Args>(args)...);
#endif
#endif
}

template <typename... Args>
void info(const std::string& format, Args&&... args) {
#ifndef NO_LOG
  log(level::info, format, std::forward<Args>(args)...);
#endif
}

template <typename... Args>
void info_essential(const std::string& format, Args&&... args) {
  log(level::info, format, std::forward<Args>(args)...);
}

template <typename... Args>
void warn(const std::string& format, Args&&... args) {
#ifndef NO_LOG
  log(level::warn, format, std::forward<Args>(args)...);
#endif
}

template <typename... Args>
void error(const std::string& format, Args&&... args) {
#ifndef NO_LOG
  log(level::error, format, std::forward<Args>(args)...);
#endif
}

template <typename... Args>
void die(const std::string& format, Args&&... args) {
#ifndef NO_LOG
  log(level::die, format, std::forward<Args>(args)...);
#endif
}
}  // namespace lg