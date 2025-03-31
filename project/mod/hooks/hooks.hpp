#pragma once

#include "../utils/memory.hpp"

#include <MinHook.h>

#define CREATE_HOOK( target, detour, og )                                                                                                                      \
  if ( create_hook( target, detour, reinterpret_cast<void**>( &( og ) ) ) )                                                                                    \
  {                                                                                                                                                            \
    mod::m_hooks.push_back( target );                                                                                                                   \
  }                                                                                                                                                            \
  else                                                                                                                                                         \
  {                                                                                                                                                            \
    return false;                                                                                                                                              \
  }

namespace mod
{
  // detours
  std::int64_t handle_potion( void* this_ptr, std::int64_t potion_id );

  // original functions
  namespace og
  {
    inline decltype( &handle_potion ) m_handle_potion{};
  }
}

namespace mod
{
  inline std::vector<void*> m_hooks{};

  bool create_hook( void* target, void* detour, void** original );
  bool install_hooks();
  bool unhook_all();
  bool unhook( const LPVOID target );
}