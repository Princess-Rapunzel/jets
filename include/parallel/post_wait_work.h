#ifndef __JETS_PARALLEL_POST_WAIT_WORK_H__
#define __JETS_PARALLEL_POST_WAIT_WORK_H__

namespace jets
{

namespace parallel
{

struct PostWaitWork
{
    virtual ~PostWaitWork() {}

    // Do *something* after a communication wait has succeeded.
    virtual void run()=0;
};
} // namespace parallel

} // namespace jets

#endif // __JETS_PARALLEL_POST_WAIT_WORK_H__