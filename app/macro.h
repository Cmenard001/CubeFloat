#ifndef __MACRO_H__
#define __MACRO_H__

/**
 * @brief Macro to avoid unused variable warning
 */
#define UNUSED_VAR(x) (void)(x);

/**
 * @brief Macro to create a MAE
 * @param enum_type The type of the MAE
 * @param init_state The initial state of the MAE
 * @param ... The other states of the MAE
 */
#define CREATE_MAE(enum_type, init_state, ...)                                        \
typedef enum                                                                          \
{                                                                                     \
    init_state = 0,                                                                   \
    __VA_ARGS__                                                                       \
} enum_type;                                                                          \
static enum_type state = init_state;                                                  \
static enum_type last_state = init_state;                                             \
static bool initialized = false;                                                      \
bool entrance = state != last_state || !initialized;                                  \
initialized = true;                                                                   \
last_state = state;                                                                   \
UNUSED_VAR(entrance);

/**
 * @brief Macro to reset a MAE
 */
#define RESET_MAE()                                                                   \
state = 0;                                                                            \
last_state = 0;                                                                       \
initialized = false;

#endif
