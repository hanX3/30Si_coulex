#include "HPGeHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>


G4ThreadLocal G4Allocator<HPGeHit>* HPGeHitAllocator = nullptr;

//
HPGeHit::HPGeHit(G4int i)
: detector_id(i)
{

}

//
G4bool HPGeHit::operator==(const HPGeHit& right) const
{
  return (this == &right)?true:false;
}


//
void HPGeHit::Draw()
{
  G4VVisManager* vis_manager = G4VVisManager::GetConcreteInstance();
  if(vis_manager)
  {
    G4Circle circle(pos);
    circle.SetScreenSize(4.);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    vis_manager->Draw(circle);
  }
}

//
void HPGeHit::Print()
{
  G4cout
     << "  detector_id: " << detector_id << "energy dep: " << std::setw(7) << G4BestUnit(e_dep, "Energy")
     << " Position: " << std::setw(7) << G4BestUnit(pos, "Length") << G4endl;
}

