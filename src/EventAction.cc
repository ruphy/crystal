// Martin Goettlich @ DESY
//
 
#include "EventAction.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"
#include "G4SDManager.hh"
#include "MyMaterials.hh"
#include "CreateTree.hh"


EventAction::EventAction()
{
	mppcCollID = -1;
}
 
EventAction::~EventAction()
{
}

void EventAction::BeginOfEventAction(const G4Event* evt)
{
  	G4int evtNb = evt->GetEventID();
  	if(evtNb%100 == 0 && evtNb!=0 ) 
	{
    		G4cout << "---> Begin of Event: " << evtNb << G4endl;
  	}

  	G4SDManager * SDman = G4SDManager::GetSDMpointer();

  	// -------------------- INSTANCE RUN/EVENT IN TREE ---------------------- //
  	Int_t run = CreateTree::Instance() -> Run;

  	CreateTree::Instance()->Clear();
  	CreateTree::Instance()->Run = run;
  	CreateTree::Instance()->Event = evt->GetEventID();

}

void EventAction::EndOfEventAction(const G4Event* evt)
{
  CreateTree::Instance()->Fill();

  if(0) 
  {
    G4cout<<"==> event summary <=="<<G4endl;
    G4cout<<"Number of optical photons produces in this event : "<<CreateTree::Instance()->NumOptPhotons<<G4endl;
    G4cout<<"Number of absorbed photons (at boundary)         : "<<CreateTree::Instance()->NumBoundaryAbsorption<<G4endl;
    G4cout<<"Number of absorbed photons (in crystal)          : "<<CreateTree::Instance()->NumOptPhotonsAbsorbed<<G4endl;
    Int_t check=CreateTree::Instance()->NumOptPhotons;
    check-=CreateTree::Instance()->NumBoundaryAbsorption;
    check-=CreateTree::Instance()->NumOptPhotonsAbsorbed;
    if(check!=0) G4cout<<"Check sum test failed: "<<check<<G4endl;
  }

}

