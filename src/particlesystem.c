#include "particlesystem.h"
#include <stdlib.h>
#include <stdio.h>

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

void draw_particles(Particlesystem* ps, Image img) {
    ParticleNode* curr = ps->firstP;

    while (curr != NULL) {
        draw_particle(curr->p, img);
        curr = curr->next;
    }
}

void update_acceleration(Particlesystem* ps) {
    // calculate sum of all gravitational forces acting upon particles and save.

    ParticleNode* curr = ps->firstP;

    while (curr != NULL) {
        printf("particle at (%f, %f), color = (%d, %d, %d)\n",
                curr->p.x, curr->p.y, curr->p.color.r, curr->p.color.g, curr->p.color.b);

        curr->p.acceleration.x = 0;
        curr->p.acceleration.y = 0;
        curr = curr->next;
    }

    curr = ps->firstP;

    while (curr != NULL) {
        ParticleNode* actor = curr->next;
        while (actor != NULL) {
            Vec2 force = gravitational_force_between(curr->p, actor->p);

            curr->p.acceleration.x += force.x;
            curr->p.acceleration.y += force.y;

            actor = actor->next;
        }
        curr = curr->next;
    }
}

void apply_acceleration(Particlesystem* ps) {
    // simulate some variable amount of time to apply acceleration and update location of particles.
    ParticleNode* curr = ps->firstP;
    while (curr != NULL) {
        curr->p.velocity_x += curr->p.acceleration.x;
        curr->p.velocity_y += curr->p.acceleration.y;
        curr = curr->next;
    }
}

void apply_velocity(Particlesystem* ps) {
    // simulate some variable amount of time to apply acceleration and update location of particles.
    // add some randomness??!!
    double coefficient = 1;
    ParticleNode* curr = ps->firstP;
    while (curr != NULL) {
        curr->p.x += coefficient * curr->p.velocity_x;
        curr->p.y += coefficient * curr->p.velocity_y;
        curr = curr->next;
    }
}

void tick(Particlesystem* ps, Image img) {
    update_acceleration(ps);
    apply_acceleration(ps);
    apply_velocity(ps);
    draw_particles(ps, img);
}