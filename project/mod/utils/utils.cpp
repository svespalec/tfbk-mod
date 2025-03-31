#include "utils.hpp"

void utils::open_console()
{
  // create a new console
  AllocConsole();

  FILE* dummy{};
  freopen_s( &dummy, "CONOUT$", "w", stdout );

  // make sure the console window is visible
  ShowWindow( GetConsoleWindow(), SW_SHOW );

  const auto title = std::format( "khazan-mod | build: {}", BUILD_NUMBER );
  SetConsoleTitleA( title.c_str() );
}

void utils::close_console()
{
  // first hide the console window
  ShowWindow( GetConsoleWindow(), SW_HIDE );

  // properly redirect stdout away from console
  FILE* dummy{};
  freopen_s( &dummy, "NUL", "w", stdout );

  // free the console
  FreeConsole();
}

// https://github.com/W1lliam1337/spotify_patcher/blob/master/DigitalSpotify/utils/utils.cpp
std::uint8_t* utils::find_sig( const HMODULE module, const std::string& byte_array )
{
  if ( !module )
    return nullptr;

  static const auto pattern_to_byte = []( const char* pattern )
  {
    auto       bytes = std::vector<int>{};
    const auto start = const_cast<char*>( pattern );
    const auto end   = const_cast<char*>( pattern ) + std::strlen( pattern );

    for ( auto current = start; current < end; ++current )
    {
      if ( *current == '?' )
      {
        ++current;

        if ( *current == '?' )
          ++current;

        bytes.push_back( -1 );
      }
      else
        bytes.push_back( std::strtoul( current, &current, 16 ) );
    }

    return bytes;
  };

  const auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>( module );
  const auto nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>( reinterpret_cast<std::uint8_t*>( module ) + dos_header->e_lfanew );

  const auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
  const auto pattern_bytes = pattern_to_byte( byte_array.c_str() );
  const auto scan_bytes    = reinterpret_cast<std::uint8_t*>( module );

  const auto pattern_size = pattern_bytes.size();
  const auto pattern_data = pattern_bytes.data();

  for ( auto i = 0ul; i < size_of_image - pattern_size; ++i )
  {
    auto found = true;

    for ( auto j = 0ul; j < pattern_size; ++j )
    {
      if ( scan_bytes[i + j] == pattern_data[j] || pattern_data[j] == -1 )
        continue;

      found = false;
      break;
    }

    if ( !found )
      continue;

    return &scan_bytes[i];
  }

  return nullptr;
}