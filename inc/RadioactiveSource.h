/*
**	Filename : RadioactiveSource.h
**	2024-01-12
**	username : rsehgal
*/
#ifndef RadioactiveSource_h
#define RadioactiveSource_h

class G4ParticleDefinition;

class RadioactiveSource{
private:
    G4ParticleDefinition *fParticle;
protected :
    int fZ;
    int fA;
    int fQ;

public:
    RadioactiveSource();
    RadioactiveSource(int z, int a, int q=0);
    ~RadioactiveSource();
    virtual void SetDecayProcess() = 0;
    G4ParticleDefinition* GetSource() const ;
};
#endif
