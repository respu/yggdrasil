#ifndef MONGO_BASE_MACROS_HPP_INCLUDED
#define MONGO_BASE_MACROS_HPP_INCLUDED




#define MONGO_DECLARE_NONCOPYABLE(name)     \
    name(const name& other) = delete;       \
                                            \
    name&                                   \
    operator=(const name& other) = delete;

#endif // MONGO_BASE_MACROS_HPP_INCLUDED
