#include "hooks/hooks.hpp"

DWORD WINAPI initialize( void* module )
{
  utils::open_console();
  LOG( "initialized with module base: {}", module );

  mod::hooks::install();
  return 0;
}

bool APIENTRY DllMain( HMODULE module, DWORD reason, LPVOID reserved )
{
  if ( reason != DLL_PROCESS_ATTACH )
    return true;

  DisableThreadLibraryCalls( module );

  mod::m_module_base = module;

  HANDLE thread = CreateThread( nullptr, 0, initialize, module, 0, nullptr );

  // close the thread handle to prevent resource leaks
  if ( thread )
    CloseHandle( thread );

  return true;
}