#ifndef __JETS_MESSAGE_TAG_H__
#define __JETS_MESSAGE_TAG_H__

#include "jetscomm.h"
#include <climits>

namespace jets
{

namespace parallel
{
// Forward declaration.
class Communicator;

class MessageTag
{
public:

  /**
   * Invalid tag, to allow for default construction.
   */
  static const int invalid_tag=INT_MIN;

  /**
   * Explicit constructor, to discourage using "magic numbers"
   * as tags.  Communicator::get_unique_tag is recommended instead.
   */
  explicit MessageTag(int tagvalue=invalid_tag)
    : _tagvalue(tagvalue), _comm(nullptr)
  {}

/**
 * Copy constructor.  Helps Communicator do reference counting on
 * unique tags
 */
  MessageTag(const MessageTag& other);

  /**
   * Move constructor.  Helps Communicator do reference counting on
   * unique tags
   */
  MessageTag(MessageTag&& other);

  /**
   * Copy assignment operator.  Helps Communicator do reference
   * counting on unique tags
   */
  MessageTag& operator = (const MessageTag& other);

  /**
   * Move assignment operator.  Helps Communicator do reference
   * counting on unique tags
   */
  MessageTag& operator = (MessageTag&& other);

  /**
   * Destructor.  Helps Communicator do reference counting on unique
   * tags
   */
  ~MessageTag();

  int value() const { return _tagvalue; }

private:
  int _tagvalue;
  const Communicator* _comm;

  // Constructor for reference-counted unique tags
  MessageTag(int tagvalue, const Communicator* comm)
    : _tagvalue(tagvalue), _comm(comm)
  {}

// Let Communicator handle the reference counting
  friend class Communicator;
};


//-------------------------------------------------------------------
/**
 * Default message tag ids
 */
#ifdef JETS_HAVE_MPI
const MessageTag any_tag=MessageTag(MPI_ANY_TAG);
#else
const MessageTag any_tag=MessageTag(-1);
#endif

const MessageTag no_tag=MessageTag(0);

} // namespace parallel

} // namespace jets
#endif // __JETS_MESSAGE_TAG_H__
