#include "hooks/hooks.hpp"

DWORD WINAPI initialize( void* module_base )
{
  utils::open_console();

  LOG( "mod loaded on build: {}", BUILD_NUMBER );
  LOG( "module base: {}", module_base );

  mod::hooks::install();

  LOG( "press DELETE to unload the mod." );

  while ( !GetAsyncKeyState( VK_DELETE ) )
    Sleep( 100 );

  LOG( "unloading mod!" );

  mod::hooks::unhook_all();
  Sleep( 2000 );
  utils::close_console();
  FreeLibraryAndExitThread( mod::m_module_base, 0 );

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