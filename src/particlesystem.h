#include "particle.h"

typedef struct ParticleNode {
    Particle p;
    struct ParticleNode* next;
} ParticleNode;

typedef struct Particlesystem
{
    ParticleNode* firstP;
    ParticleNode* lastP;

} Particlesystem;

void add_particle(Particlesystem* ps, Particle p);
