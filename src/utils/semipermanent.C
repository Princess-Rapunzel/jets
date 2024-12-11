#include "semipermanent.h"
#include "jetscomm.h"

namespace jets
{
int SemiPermanent::_ref_count = 0;

std::vector<std::unique_ptr<SemiPermanent>> SemiPermanent::_stuff_to_clean;


SemiPermanent::Ref::~Ref()
{
  _ref_count--;

  // Last one to leave turns out the lights
  if (_ref_count <= 0)
    _stuff_to_clean.clear();
}


void SemiPermanent::add(std::unique_ptr<SemiPermanent> obj)
{
  jets_assert_greater(_ref_count, 0);

  _stuff_to_clean.push_back(std::move(obj));
}
} // namespace jets
