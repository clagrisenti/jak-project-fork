// clang-format off
#include "GlobalProfiler.h"

GlobalProfiler gprof;
GlobalProfiler& prof() {
  return gprof;
}

ScopedEvent scoped_prof(const char* name) {
  auto& p = prof();
  p.begin_event(name);
  return ScopedEvent{&p};
}
