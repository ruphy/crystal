// Martin Goettlich @ DESY
//

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "ConfigFile.h"
#include "TString.h"

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4OpBoundaryProcess.hh"


class DetectorConstruction : public G4VUserDetectorConstruction
{
	public:
		DetectorConstruction();
   		~DetectorConstruction();

    		// World dimensions
    		G4double expHall_x;
    		G4double expHall_y;
    		G4double expHall_z;
    		// Crystal parameters
    		G4double crystal_x;    
    		G4double crystal_y;
    		G4double crystal_height;
    		int      crystal_material;
    		int      crystal_lightyield;
    		G4double crystal_risetime;
    		G4double crystal_abslength;
		G4double airgap;

		int surConfig;

		TString wReffile;
		G4double wReflectivity;
		G4double wSurrefind;
		int wSurtype;
		G4double wSpecularspike;
		G4double wSpecularlobe;
		G4double wSigmaalpha;
		G4double wLambertian;
		G4double wBackscatter;
		int wrappingSurfinish;
		TString cReffile;
		G4double cReflectivity;
		G4double cSurrefind;
		int cSurtype;
		G4double cSpecularspike;
		G4double cSpecularlobe;
		G4double cSigmaalpha;
		G4double cLambertian;
		G4double cBackscatter;
		int crystalSurfinish;
		TString RefFile;
		G4double reflectivity;
		G4double surrefind;
		int surtype;
		G4double specularspike;
		G4double specularlobe;
		G4double sigmaalpha;
		G4double lambertian;
		G4double backscatter;
		G4double crystal_reflectivity;
		int surfinish;	
  		G4double Ephoton[3];

		//Materials
		G4Material* Air;
		G4Material* Water;
		G4Material* Vacuum;
		G4Material* Silicon;
		G4Material* OptGrease;
		G4Material* ScMaterial;



    		G4VPhysicalVolume* Construct();

    		//
		// Update geometry
		// 
    		void     UpdateGeometry();
    		G4bool   GetUpdated() const;
    		G4bool updated;

    		//DetectorMessenger* detectorMessenger;
		void readConfigFile(string configFileName);
		void initializeMaterials();
		void initializeSurface(G4OpticalSurface* mySurface, string surfaceType);
		void initializeReflectivitySurface(G4OpticalSurface* mySurface, string surfaceType);
};



#endif /*DetectorConstruction_h*/
