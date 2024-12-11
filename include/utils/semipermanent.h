#ifndef __JETS_SEMIPERMANENT_H__
#define __JETS_SEMIPERMANENT_H__

// C/C++ includes

#include <memory>
#include <vector>
namespace jets
{
// Forward declare friend
namespace parallel
{
class JetsInit;
} // namespace parallel


/**
 * The \p SemiPermanent "class" is basically just a place for a
 * destructor vtable.  Derive from it and pass a unique_ptr to your
 * derived object to SemiPermanent::add() whenever you have
 * something that ought to be *almost* permanent: that should be
 * cleaned up eventually to avoid resource leaks, but that should not
 * be cleaned up until the last TIMPIInit object exits, just before
 * the MPI_Finalize call if TIMPI initialized MPI.
 */

class SemiPermanent
{
public:
    SemiPermanent()=default;
    virtual ~SemiPermanent()=default;

    /*
     * Transfer ownership of a pointer to some "SemiPermanent" objects,
     * to be destroyed (and thereby do any necessary cleanup work)
     * whenever the last TIMPIInit is destroyed, before MPI is
     * finalized.
     */
    static void add( std::unique_ptr<SemiPermanent> obj );

    // Class to hold a reference to the SemiPermanent objects; they will
    // only be destructed when the last Ref is.
    struct Ref
    {
        Ref() { _ref_count++; }
        ~Ref();
    };

private:

  // Mechanisms to avoid leaks after every TIMPIInit has been
  // destroyed
    static int _ref_count;
    static std::vector<std::unique_ptr<SemiPermanent>> _stuff_to_clean;
};
} // namespace TIMPI
#endif // __JETS_SEMIPERMANENT_H__