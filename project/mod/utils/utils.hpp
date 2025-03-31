#pragma once

// exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN
#define BUILD_NUMBER "1.0"

#include <windows.h>

#include <iostream>
#include <vector>
#include <format>
#include <print>

#define LOG( fmt, ... ) std::println( "[ tfbk-mod ] : " fmt, ##__VA_ARGS__ )

namespace mod
{
  void open_console();
  void close_console();

  std::uint8_t* find_sig( const HMODULE module, const std::string& byte_array );
}

namespace mod
{
  inline HMODULE m_module_base{};
  inline HMODULE m_khazan_base{};
}