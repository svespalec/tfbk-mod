#include "../hooks.hpp"

std::int64_t mod::hooks::handle_potion( void* this_ptr, std::int64_t potion_id )
{
  LOG( __FUNCTION__ );

  return og::m_handle_potion( this_ptr, potion_id );
}