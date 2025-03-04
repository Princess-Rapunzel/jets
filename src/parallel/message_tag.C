#include "message_tag.h"
// #include "communicator.h"

namespace jets
{
namespace parallel
{

// MessageTag member functions

MessageTag::~MessageTag()
{
  //   if (_comm)
  //     _comm->dereference_unique_tag(_tagvalue);
}

MessageTag::MessageTag(const MessageTag& other)
  : _tagvalue(other._tagvalue), _comm(other._comm)
{
  //   if (_comm)
  //     _comm->reference_unique_tag(_tagvalue);
}

MessageTag::MessageTag(MessageTag&& other)
  : _tagvalue(other._tagvalue), _comm(other._comm)
{
  // I stole your tag reference!
  other._comm = nullptr;
}

MessageTag& MessageTag::operator=(const MessageTag& other)
{
  //   if (_comm)
  //     _comm->dereference_unique_tag(_tagvalue);

  _tagvalue = other._tagvalue;
  _comm = other._comm;

  //   if (_comm)
  //     _comm->reference_unique_tag(_tagvalue);

  return *this;
}

MessageTag& MessageTag::operator=(MessageTag&& other)
{
  //   if (_comm)
  //     _comm->dereference_unique_tag(_tagvalue);

  _tagvalue = other._tagvalue;
  _comm = other._comm;

  // I stole your tag reference!
  other._comm = nullptr;

  return *this;
}
} // namespace parallel
} // namespace jets
