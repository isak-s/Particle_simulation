#include "particlesystem.h"
#include <stdlib.h>

Particlesystem* new_particlesystem() {
    Particlesystem* ps = malloc(sizeof(Particlesystem));
    ps->firstP = NULL;
    ps->lastP = NULL;
    return ps;
}

void add_particle(Particlesystem* ps, Particle p) {

    ParticleNode* pn = malloc(sizeof(ParticleNode));

    pn->next = NULL;
    pn->p = p;

    if (ps->firstP == NULL) {
        ps->firstP = pn;
        ps->lastP = pn;
        return;
    }
    ps->lastP->next = pn;
    ps->lastP = pn;
}

void free_particlesystem(Particlesystem* ps) {
    ParticleNode* head = ps->firstP;

    while (head != NULL) {
        ParticleNode* tmp = head;
        head = head->next;
        free(tmp);
    }
    free(ps);
}

void draw_particle(Particle p, Image img) {
    img.pixels[((int) p.y) * img.width + (int)p.x] = p.color;
}

void draw_particles(Particlesystem ps, Image img) {
    ParticleNode* curr = ps.firstP;

    while (curr != NULL) {
        draw_particle(curr->p, img);
        curr = curr->next;
    }
}

void update_acceleration() {
    // calculate sum of all gravitational forces acting upon particles and save.

    // add some randomness??!!

    // for first prototype, perhaps only have head apply force to all others.

}

void apply_acceleration() {
    // simulate some variable amount of time to apply acceleration and update location of particles.
}

void tick(Particlesystem ps, Image img) {
    update_acceleration();
    apply_acceleration();
    draw_particles(ps, img);
}