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


