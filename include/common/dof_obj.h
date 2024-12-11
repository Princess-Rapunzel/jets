#ifndef __DOF_OBJ_H__
#define __DOF_OBJ_H__

#include "jets.h"

namespace jets
{

/**
 * The \p DofObject defines an abstract base class for objects that
 * have degrees of freedom associated with them.  Examples of such
 * objects are the \p Node and \p Elem classes.  This class can
 * not be instantiated, only derived from.
 * @author Ariel Louis
 * @date   2024-10-26
 * @brief  Degree of freedom object
 */
__jets_abstract__ class DofObject
{

public:
    DofObject();
    // virtual ~DofObject() = 0;
    ~DofObject();

    const dof_id_type& id() const;
private:
    dof_id_type _id;
};

__jets_inline__ DofObject::DofObject() 
{ jets_abstract_class(); }

__jets_inline__ const dof_id_type& DofObject::id() const
{ return _id; }
__jets_inline__ DofObject::~DofObject() = default;
} // namespace jets
#endif // __DOF_OBJ_H__
