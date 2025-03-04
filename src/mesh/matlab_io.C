#include "matlab_io.h"
#include "base_mesh.h"
#include "tri3.h"

#include <fstream>
#include <vector>

namespace jets
{

void MatlabIO::read(const std::string & name)
{
  std::ifstream in (name.c_str());
  this->read_stream(in);
}

BaseMesh& MatlabIO::mesh() { return _mesh; }

void MatlabIO::read_stream(std::istream & in)
{
    // This is a serial-only process for now;
    // the Mesh should be read on processor 0 and
    // broadcast later
#ifdef JETS_HAVE_MPI
    jets_assert_equal_to(this->mesh().processor_id(), 0);
#endif // JETS_HAVE_MPI
    
    // Get a reference to the mesh
    BaseMesh& the_mesh = this->mesh();
    
    // Clear any existing mesh data
    the_mesh.clear();
    
    // PDE toolkit only works in 2D
    the_mesh.set_dim(2);
    
    // Check the input buffer
    jets_assert_msg(in.good(), "Could not open file for reading");
    
    size_type nNodes=0, nElem=0;
    
    in >> nNodes   // Read the number of nodes
         >> nElem;   // Read the number of elements
    
    // Sort of check that it worked
    jets_assert_greater_msg(nNodes, 0, "No nodes in mesh");
    jets_assert_greater_msg(nElem, 0, "No elements in mesh");
    
    // Read the nodal coordinates
    {
        Real x=0., y=0., z=0.;
        for (size_type i=0; i<nNodes; i++)
        {
            in >> x   // x-coordinate value
            >> y;  // y-coordinate value  
            auto node = new Node(x, y, z, i);
            the_mesh.add_node(*node);
        }
    }

    // Read the elements (elements)
  {
    size_type node=0;

    for (size_type i=0; i<nElem; i++)
    {
        std::vector<Node*> nodes(3);
        for (size_type j=0; j<3; j++)
        {
            in >> node;
            nodes[j] = &the_mesh.get_node(node - 1);
        }
        // Always build a triangle
        auto tri = new Tri3(nodes, i);
        the_mesh.add_elem(*tri);
    }
  }
}
} // namespace jets