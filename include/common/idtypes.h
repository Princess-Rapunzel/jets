#ifndef __IDTYPES_H__
#define __IDTYPES_H__

#include "jetscfg.h"
#include <stdint.h>

namespace jets
{

// Define processor id storage type.
#if JETS_PROCESSOR_ID_BYTES == 1
typedef uint8_t processor_id_type;
#elif JETS_PROCESSOR_ID_BYTES == 2
typedef uint16_t processor_id_type;
#elif JETS_PROCESSOR_ID_BYTES == 4
typedef uint32_t processor_id_type;
#elif JETS_PROCESSOR_ID_BYTES == 8
typedef uint64_t processor_id_type;
#endif

// How many bytes do we need to specify DoFObjects?  By default we'll
// allow for a few billion (each) nodes & elements.
//
// We'll need a sign bit in some internal buffers, so let's also
// define a signed type that we can convert to without loss.
#if JETS_DOF_ID_BYTES == 1
typedef uint8_t dof_id_type;
typedef  int8_t dof_id_signed_type;
#elif JETS_DOF_ID_BYTES == 2
typedef uint16_t dof_id_type;
typedef  int16_t dof_id_signed_type;
#elif JETS_DOF_ID_BYTES == 8
typedef uint64_t dof_id_type;
typedef  int64_t dof_id_signed_type;
#else // JETS_DOF_ID_BYTES = 4 (default)
typedef uint32_t dof_id_type;
typedef  int32_t dof_id_signed_type;
#endif
} // namespace jets


#endif // __IDTYPES_H__