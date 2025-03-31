#include "../hooks.hpp"

std::int64_t mod::handle_potion( void* this_ptr, std::int64_t potion_id )
{
  auto potion_ptr = og::m_handle_potion( this_ptr, potion_id );

  if ( !potion_ptr )
    return 0;

  static int initial_potion_count = -1;

  // get the current potion count pointer (recalculated each call)
  auto potion_count_ptr = reinterpret_cast<int*>( potion_ptr + 0x20 );

  // if this is the first call, save the initial count
  if ( initial_potion_count == -1 )
  {
    initial_potion_count = *potion_count_ptr;
    LOG( "initial health potion count set to: {}", initial_potion_count );
  }

  // always restore to the initial amount
  *potion_count_ptr = initial_potion_count;

  LOG( "health potion count restored to: {}", initial_potion_count );

  return potion_ptr;
}