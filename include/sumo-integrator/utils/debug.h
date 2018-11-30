#ifndef INCLUDE_INTEGRATOR_UTILS_DEBUG_H
#define INCLUDE_INTEGRATOR_UTILS_DEBUG_H


// clang-format off
#define DEBUG_OFF  0
#define DEBUG_INFO 1
#define DEBUG_DATA 2

#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RED     "\x1b[91m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
// clang-format on

#if DEBUG_LEVEL >= DEBUG_INFO
#define LOG_INFO \
    printf(ANSI_COLOR_CYAN "%-12s" ANSI_COLOR_RESET, "[ INFO ]");
#define LOG_INFO_SUCCESS(text, ...)                                \
    LOG_INFO                                                       \
    printf(ANSI_COLOR_GREEN "%-12s" ANSI_COLOR_RESET, "[  OK  ]"); \
    printf((text), ##__VA_ARGS__);                                 \
    printf("\n");
#define LOG_INFO_FAIL(text, ...)                                 \
    LOG_INFO                                                     \
    printf(ANSI_COLOR_RED "%-12s" ANSI_COLOR_RESET, "[ FAIL ]"); \
    printf((text), ##__VA_ARGS__);                               \
    printf("\n");
#else
#define LOG_INFO_SUCCESS(...)
#define LOG_INFO_FAIL(...)
#endif

#if DEBUG_LEVEL >= DEBUG_DATA
#defin LOG_DATA(text, ...)                                           \
    printf(ANSI_COLOR_MAGENTA "%-12s" ANSI_COLOR_RESET, "[ DATA ]"); \
    printf((text), ##__VA_ARGS__);                                   \
    printf("\n");
#else
#define LOG_DATA(...)
#endif


#endif  // INCLUDE_INTEGRATOR_UTILS_DEBUG_H
