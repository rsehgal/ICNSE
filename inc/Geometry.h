/*
**	Filename : Geometry.h
**	2024-01-01
**	username : rsehgal
*/
#ifndef Geometry_h
#define Geometry_h

class G4Tubs;
class G4LogicalVolume;
class G4Material;
class G4VSolid;
class G4Tubs;
class G4String;
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
  ~GeometryProperties();
  //void SetMaterial(G4Material *material);
  void SetMaterial(G4String logicalVolumeName,G4String material);
  void SetInnerRadius(G4String logicalVolumeName,double innerRad);
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
  CylindricalShell(G4String name, double rmin, double rmax, double dz, double sphi, double dphi);
  ~CylindricalShell();
};

#endif
