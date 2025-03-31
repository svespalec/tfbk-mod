#pragma once

#include "utils.hpp"

namespace memory
{
  class c_patching
  {
  public:
    // write raw bytes to memory
    static bool write_bytes( void* address, const std::vector<uint8_t>& bytes );
    static bool nop( void* address, size_t length );

    // helper to get address from signature+offset
    static void* get_address( const HMODULE module, const std::string& signature, int offset = 0 );

    // todo
    static bool insert_trampoline( void* address, const std::vector<uint8_t>& custom_code );

  private:
    // utility to change memory protection
    static bool protect_memory( void* address, size_t size, DWORD protection, DWORD& old_protection );
  };
}
