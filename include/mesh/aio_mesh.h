#ifndef __JETS_AIO_MESH_H__
#define __JETS_AIO_MESH_H__

#include "base_mesh.h"
#include "jetscomm.h"
#include "jets.h"

namespace jets
{
/**
 * @brief AIO stands for All In One. This mesh class gather
 * all elements in one processor. Namely, it is a serial mesh.
 * 
 */
class AIOMesh : public BaseMesh
{
    
};
} // namespace jets

#endif // __JETS_AIO_MESH_H__