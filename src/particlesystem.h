#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H
#include "particle.h"
#include "image.h"

typedef struct ParticleNode {
    Particle p;
    struct ParticleNode* next;
} ParticleNode;

typedef struct Particlesystem
{
    ParticleNode* firstP;
    ParticleNode* lastP;

} Particlesystem;

Particlesystem* new_particlesystem();

void add_particle(Particlesystem* ps, Particle p);

void free_particlesystem(Particlesystem* ps);

void draw_particle(Particle p, Image img);

void tick(Particlesystem* ps, Image img);

#endif