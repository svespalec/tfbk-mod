#include "memory.hpp"

bool memory::c_patching::protect_memory( void* address, size_t size, DWORD protection, DWORD& old_protection )
{
  return VirtualProtect( address, size, protection, &old_protection ) != 0;
}

bool memory::c_patching::write_bytes( void* address, const std::vector<uint8_t>& bytes )
{
  if ( !address || bytes.empty() )
    return false;

  DWORD old_protection{};

  if ( !protect_memory( address, bytes.size(), PAGE_EXECUTE_READWRITE, old_protection ) )
    return false;

  std::memcpy( address, bytes.data(), bytes.size() );

  // restore original protection
  DWORD temp{};
  VirtualProtect( address, bytes.size(), old_protection, &temp );

  // ensure CPU sees our changes
  FlushInstructionCache( GetCurrentProcess(), address, bytes.size() );

  return true;
}

bool memory::c_patching::nop( void* address, size_t length )
{
  if ( !address || length == 0 )
    return false;

  // 0x90 = NOP
  std::vector<uint8_t> nops( length, 0x90 );

  return write_bytes( address, nops );
}

void* memory::c_patching::get_address( const HMODULE module, const std::string& signature, int offset )
{
  uint8_t* result = utils::find_sig( module, signature );

  if ( !result )
    return nullptr;

  return result + offset;
}

bool memory::c_patching::insert_trampoline( void* address, const std::vector<uint8_t>& custom_code )
{
  // todo
  return false;
}
