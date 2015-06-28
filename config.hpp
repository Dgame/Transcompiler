#ifndef CONFIG_HPP
#define CONFIG_HPP

#if _WIN32 || _WIN64
    #if _WIN64
        #define ENV_64_BIT
    #else
        #define ENV_32_BIT
    #endif
#elif __GNUC__
    #if __x86_64__ || __ppc64__
        #define ENV_64_BIT
    #else
        #define ENV_32_BIT
    #endif
#else
    #error "Unsupported OS"
#endif

#define DEBUG 1

#endif
