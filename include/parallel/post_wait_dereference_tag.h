#ifndef __JETS_POST_WAIT_DEREFERENCE_TAG_H__
#define __JETS_POST_WAIT_DEREFERENCE_TAG_H__

#include "post_wait_work.h"
#include "message_tag.h"

namespace jets
{

namespace parallel
{
// PostWaitWork specialization for holding a MessageTag.  This
// prevents the MessageTag from being completely dereferenced and thus
// prevents a unique tag number from being reused until after the
// Request has been cleaned up.
struct PostWaitDereferenceTag : public PostWaitWork
{
    PostWaitDereferenceTag(const MessageTag& tag) : _tag(tag) {}

    // Our real work is done by the MessageTag member's destructor;
    // there's no advantage to dereferencing our tag slightly earlier.
    virtual void run() override {}

private:
    MessageTag _tag;
};
} // namespace parallel
} // namespace jets


#endif // __JETS_POST_WAIT_DEREFERENCE_TAG_H__