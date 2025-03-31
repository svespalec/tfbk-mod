#include "hooks.hpp"

bool mod::hooks::create_hook( void* target, void* detour, void** original )
{
  auto status = MH_CreateHook( target, detour, original );

  if ( status != MH_OK )
  {
    LOG( "failed to create hook for target: {:p}, error: {}", target, MH_StatusToString( status ) );
    return false;
  }

  status = MH_EnableHook( target );

  if ( status != MH_OK )
  {
    LOG( "failed to enable hook for target: {:p}, error: {}", target, MH_StatusToString( status ) );
    return false;
  }

  LOG( "created target: {:p}, detour: {:p}, og: {:p}", target, detour, *original );

  return true;
}

bool mod::hooks::install()
{
  // set our module base
  mod::m_khazan_base = GetModuleHandleA( nullptr );

  if ( MH_Initialize() != MH_OK )
  {
    LOG( "failed to initialize minhook!" );
    return false;
  }

  LOG( "initialized minhook!" );

  static const auto potion_func = static_cast<void*>( memory::c_patching::get_address( mod::m_khazan_base, "7F ? 48 05 ? ? ? ? 48 3B C2 75 ? 33 C0", -0x7D ) );

  CREATE_HOOK( potion_func, handle_potion, og::m_handle_potion );

  LOG( "all hooks setup!" );

  return true;
}

bool mod::hooks::unhook_all()
{
  // only attempt if we actually have hooks installed
  if ( hooks::m_hooks.empty() )
    return true;

  for ( const auto target : hooks::m_hooks )
    if ( !unhook( target ) )
      return false;

  LOG( "removed all hooks!" );

  MH_Uninitialize();
}

bool mod::hooks::unhook( const LPVOID target )
{
  auto status = MH_DisableHook( target );

  if ( status != MH_OK )
  {
    LOG( "failed to unhook on target {} | error: {}", target, MH_StatusToString( status ) );
    return false;
  }

  LOG( "unhooked target: {}", target );

  return true;
}