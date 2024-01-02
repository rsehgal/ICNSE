/*
**	Filename : Materials.h
**	2024-01-02
**	username : rsehgal
**
**	This class is introduced to add user defined materials
**	to the nist database, so that they be access as other
**	materials.
**
**	User Just needs to create an object somewhere,
**	May be in the main program itself.
*/

#ifndef Materials_h
#define Materials_h

class G4Material;

class Materials {
private:
  G4Material *fBP;
  G4Material *fHDPE;

public:
  Materials();
  ~Materials();
  void CreateBoratedPolyethylene();
  void CreateHighDensityPolyethylene();
  void RegisterMaterial(G4Material *material);

  G4Material* GetBP() const;
  G4Material* GetHDPE() const;
};

#endif
