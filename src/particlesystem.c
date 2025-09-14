#include "particlesystem.h"
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"

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

void draw_particle(Particle* p, Image* img) {
    draw_pixel(img, p->pos.x, p->pos.y, p->color);
}

void draw_old_particle_positions(Particle* p, Image* img) {

    for (int i = 0; i < NUM_OLD_POSITIONS; i++) {
        int x = p->old_positions[i].x;
        int y = p->old_positions[i].y;
        draw_pixel(img, x, y, p->color);
    }
}

void draw_particles(Particlesystem* ps, Image* img) {
    ParticleNode* curr = ps->firstP;

    while (curr != NULL) {
        draw_particle(&curr->p, img);
        draw_old_particle_positions(&curr->p, img);
        curr = curr->next;
    }
}

void update_acceleration(Particlesystem* ps) {
    // calculate sum of all gravitational forces acting upon particles and save.

    ParticleNode* curr = ps->firstP;

    while (curr != NULL) {
        printf("particle at (%f, %f), color = (%d, %d, %d)\n",
                curr->p.pos.x, curr->p.pos.y, curr->p.color.r, curr->p.color.g, curr->p.color.b);

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
            // signed in the other direction for the actor
            actor->p.acceleration.x -= force.x;
            actor->p.acceleration.y -= force.y;

            actor = actor->next;
        }
        curr = curr->next;
    }
}

void apply_acceleration(Particlesystem* ps) {
    // simulate some variable amount of time to apply acceleration and update location of particles.
    ParticleNode* curr = ps->firstP;
    while (curr != NULL) {
        if (curr->p.move_randomly) {
            curr->p.velocity.x += (rand() % (MAX_VELOCITY) - (rand() % MAX_VELOCITY));
            curr->p.velocity.y += (rand() % (MAX_VELOCITY) - (rand() % MAX_VELOCITY));
        } else {
            curr->p.velocity.x += curr->p.acceleration.x;
            curr->p.velocity.y += curr->p.acceleration.y;
        }
        clamp_velocity(&curr->p);

        curr = curr->next;
    }
}

void apply_velocity(Particlesystem* ps) {
    // simulate some variable amount of time to apply acceleration and update location of particles.
    // add some randomness??!!
    double coefficient = 0.1;
    ParticleNode* curr = ps->firstP;
    while (curr != NULL) {
        curr->p.pos.x += coefficient * curr->p.velocity.x;
        curr->p.pos.y += coefficient * curr->p.velocity.y;
        clamp_velocity(&curr->p);
        curr = curr->next;
    }
}


int particle_is_within_image(Particle p, Image* img) {
    return p.pos.x <= img->width && p.pos.x >= 0 && p.pos.y <= img->height && p.pos.y >= 0;
}

void boundary_check(Particlesystem* ps, Image* img) {
    // if the particle is outside of the image dimensions,
    // snap it back to the edge and reverse the direction of the velocity.

    ParticleNode* curr = ps->firstP;

    while (curr != NULL) {
        if (!particle_is_within_image(curr->p, img)) {
            if (curr->p.pos.x < 0) { curr->p.pos.x = 0; curr->p.velocity.x = -curr->p.velocity.x; }
            if (curr->p.pos.x >= img->width) { curr->p.pos.x = img->width - 1; curr->p.velocity.x = -curr->p.velocity.x; }
            if (curr->p.pos.y < 0) { curr->p.pos.y = 0; curr->p.velocity.y = -curr->p.velocity.y; }
            if (curr->p.pos.y >= img->height) { curr->p.pos.y = img->height - 1; curr->p.velocity.y = -curr->p.velocity.y; }
        }
        curr = curr->next;
    }

}
void update_old_positions(Particlesystem* ps) {
    ParticleNode* curr = ps->firstP;

    while (curr != NULL) {
        add_curr_pos_to_old_positions(&curr->p);
        curr = curr->next;
    }
}

void tick(Particlesystem* ps, Image* img) {
    update_old_positions(ps);
    update_acceleration(ps);
    apply_acceleration(ps);
    apply_velocity(ps);
    boundary_check(ps, img);
    draw_particles(ps, img);
}