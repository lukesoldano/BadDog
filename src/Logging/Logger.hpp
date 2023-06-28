#pragma once

#ifndef SILENCE_LOGGING

   #include <chrono>
   #include <iostream>

   #define LOG_MESSAGE(message) \
      std::cout << "LOG|" << std::chrono::system_clock::now() << "|" << \
                             __FILE__ << ":" << \
                             __LINE__ << ":" << \
                             __func__ << ": " << \
                             message << std::endl;
   #define LOG_WARNING(warning) \
      std::cout << "WRN|" << std::chrono::system_clock::now() << "|" << \
                             __FILE__ << ":" << \
                             __LINE__ << ":" << \
                             __func__ << ": " << \
                             warning << std::endl;
   #define LOG_ERROR(error) \
      std::cerr << "ERR|" << std::chrono::system_clock::now() << "|" << \
                             __FILE__ << ":" << \
                             __LINE__ << ":" << \
                             __func__ << ": " << \
                             error << std::endl;

#else 

   #define LOG_MESSAGE(message); // do nothing
   #define LOG_WARNING(warning); // do nothing
   #define LOG_ERROR(error); // do nothing

#endif