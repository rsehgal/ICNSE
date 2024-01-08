/*
**	Filename : Geometry.h
**	2024-01-01
**	username : rsehgal
*/
#ifndef Geometry_h
#define Geometry_h

class G4Tubs;
class G4Box;
class G4LogicalVolume;
class G4Material;
class G4VSolid;
class G4Tubs;
class G4SubtractionSolid;

#include <G4CSGSolid.hh>
#include <G4String.hh>
//class G4String;
//class DetectorMessenger;
class G4GenericMessenger;

class GeometryProperties {
public:
  G4Material *fMaterial;
  G4LogicalVolume *fLogicalVolume;
  //DetectorMessenger *fGeometryMessenger;
  G4GenericMessenger *fGeometryMessenger=nullptr;

public:
  GeometryProperties();
  GeometryProperties(G4Material *material, G4VSolid *solid);
  GeometryProperties(G4String material, G4VSolid *solid);
  void SetProperties(G4String material, G4VSolid *solid);
  void SetProperties(G4Material *material, G4VSolid *solid);
  ~GeometryProperties();
  //void SetMaterial(G4Material *material);
  void SetMaterial(G4String logicalVolumeName,G4String material);
  
  // Function to change the inner and outer radius of tube
  void SetInnerRadius(G4String logicalVolumeName,double innerRad);
  void SetOuterRadius(G4String logicalVolumeName,double outerRad);

  // Functions to change Box dimensions
  void SetBoxXDim(G4String logicalVolumeName,double half);
  void SetBoxYDim(G4String logicalVolumeName,double half);
  void SetBoxZDim(G4String logicalVolumeName,double half);
  void SetBoxAllDim(G4String logicalVolumeName,double halfx, double halfy, double halfz);

  // Functions to change BoxShell dimension
  void SetBoxShellXDim(G4String logicalVolumeName,double half);
  void SetBoxShellYDim(G4String logicalVolumeName,double half);
  void SetBoxShellZDim(G4String logicalVolumeName,double half);
  void SetBoxShellThickness(G4String logicalVolumeName,double thickness);
   // Function to create geometry from UI
   /*void CreateBox(G4String name, double halfx, double halfy, double halfz,
                  G4String material,G4Rotation *rot, G4ThreeVector trans,
                  G4LogicalVolume *)
    */              

  //void SetInnerRadius(double innerRad);
  G4Material *GetMaterial() const;
  G4LogicalVolume *GetLogicalVolume() const;
  void DefineCommands();
};

class CylindricalShell : public GeometryProperties {
public:
  G4Tubs *fSolid;

public:
  CylindricalShell();
  CylindricalShell(G4String name, double rmin, double rmax, double dz, double sphi, double dphi,G4String material=G4String("G4_Galactic"));
  CylindricalShell(G4String name, double rmin, double rmax, double dz, double sphi, double dphi,G4Material *material);
  ~CylindricalShell();
};

class Box : public GeometryProperties {
public:
  G4Box *fSolid;

public:
  Box();
  Box(G4String name,  double halfx, double halfy, double halfz,G4String material=G4String("G4_Galactic"));
  Box(G4String name,  double halfx, double halfy, double halfz,G4Material *material);
  
  ~Box();
};

class BoxShellVSolid{

};

class BoxShell : public GeometryProperties{
//class BoxShell : public GeometryProperties,public G4CSGSolid {
//class BoxShell : public G4VSolid {
private:
  double fHalfX;
  double fHalfY;
  double fHalfZ;
  double fThickness;

public:
  //G4VSolid *fSolid;
  G4SubtractionSolid *fSolid;
  void SetXHalfLength(double half);
  void SetYHalfLength(double half);
  void SetZHalfLength(double half);
  void SetThickness(double thickness);


public:
  //BoxShell();
  BoxShell(G4String name,  double halfx, double halfy, double halfz, double thickness, G4String material=G4String("G4_Galactic"));
  BoxShell(G4String name,  double halfx, double halfy, double halfz, double thickness,G4Material *material);
  
  ~BoxShell();
};



#endif
