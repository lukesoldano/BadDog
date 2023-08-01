#pragma once

#if !SILENCE_LOGGING
   #include <chrono>
   #include <iostream>
#endif

#if !SILENCE_LOGGING && MESSAGE_LOGGING
   #define LOG_MESSAGE(message) std::cout << std::chrono::system_clock::now() << \
                                             " | LOG | " << \
                                             __FILE__ << ":" << \
                                             __LINE__ << "::" << \
                                             __func__ << "(...) -> " << \
                                             message << std::endl;
#else 
   #define LOG_MESSAGE(message); // do nothing
#endif

#if !SILENCE_LOGGING && WARNING_LOGGING
   #define LOG_WARNING(warning) std::cerr << std::chrono::system_clock::now() << \
                                             " | WRN | " << \
                                             __LINE__ << "::" << \
                                             __func__ << "(...) -> " << \
                                             warning << std::endl;
#else
   #define LOG_WARNING(warning); // do nothing
#endif

#if !SILENCE_LOGGING && ERROR_LOGGING
   #define LOG_ERROR(error)  std::cerr << std::chrono::system_clock::now() << \
                                          " | ERR | " << \
                                          __LINE__ << "::" << \
                                          __func__ << "(...) -> " << \
                                          error << std::endl;
#else
   #define LOG_ERROR(error); // do nothing
#endif

#if !SILENCE_LOGGING && VERBOSE_LOGGING
   #define LOG_VERBOSE(message) std::cout << std::chrono::system_clock::now() << \
                                             " | VRB | " << \
                                             __LINE__ << "::" << \
                                             __func__ << "(...) -> " << \
                                             message << std::endl;
#else
   #define LOG_VERBOSE(message); // do nothing
#endif
