#include "particlesystem.h"
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"

#include <math.h>

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

void add_black_hole(Particlesystem* ps, Particle p) {
    // adds the particle to the particlesystem list
    // while also keeping a pointer to that particlenode's particle
    ParticleNode* pn = malloc(sizeof(ParticleNode));

    pn->next = NULL;
    pn->p = p;

    ps->black_hole = &pn->p;

    if (ps->firstP == NULL) {
        ps->firstP = pn;
        ps->lastP = pn;

        return;
    }
    ps->lastP->next = pn;
    ps->lastP = pn;

}

void add_white_hole(Particlesystem* ps, Particle p) {
    ParticleNode* pn = malloc(sizeof(ParticleNode));

    pn->next = NULL;
    pn->p = p;

    ps->white_hole = &pn->p;

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

int collides_with_black_hole(Particlesystem* ps, Particle* p) {

    // if it is the black hole itself, we do nothing
    if (ps->black_hole == p) {
        return 0;
    }

    return (distance_between(*ps->black_hole, *p) < COLLISION_RADIUS);
}

void update_acceleration(Particlesystem* ps) {
    // calculate sum of all gravitational forces acting upon particles and save.

    ParticleNode* curr = ps->firstP;

    while (curr != NULL) {
        // printf("particle at (%f, %f), color = (%d, %d, %d)\n",
        //         curr->p.pos.x, curr->p.pos.y, curr->p.color.r, curr->p.color.g, curr->p.color.b);

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

    ParticleNode* curr = ps->firstP;
    while (curr != NULL) {
        // uncomment to add functionality, currently unused due to refactoring
        if (curr->p.move_randomly) {
            curr->p.velocity.x += (rand() % (MAX_VELOCITY) - (rand() % MAX_VELOCITY));
            curr->p.velocity.y += (rand() % (MAX_VELOCITY) - (rand() % MAX_VELOCITY));
        } else {
            curr->p.velocity.x += curr->p.acceleration.x;
            curr->p.velocity.y += curr->p.acceleration.y; // * dt
        }
        clamp_velocity(&curr->p);

        curr = curr->next;
    }
}


void handle_collisions(Particlesystem* ps) {
    ParticleNode* curr = ps->firstP;
    while (curr != NULL) {
        if (collides_with_black_hole(ps, &curr->p)) {
            printf("collision!\n");
            curr->p.pos.x = ps->white_hole->pos.x;
            curr->p.pos.y = ps->white_hole->pos.y;
        }
        curr = curr->next;
    }
}

void apply_velocity(Particlesystem* ps) {
    ParticleNode* curr = ps->firstP;
    while (curr != NULL) {
        curr->p.pos.x += SPEEDUP_COEFFICIENT * dt * curr->p.velocity.x;
        curr->p.pos.y += SPEEDUP_COEFFICIENT * dt * curr->p.velocity.y;
        clamp_velocity(&curr->p);
        curr = curr->next;
    }
}


int particle_is_within_image(Particle p, Image* img) {
    return p.pos.x <= img->width && p.pos.x >= 0 && p.pos.y <= img->height && p.pos.y >= 0;
}

void bounce_particle(Image* img, Particle* p) {
    if (p->pos.x < 0) {
        p->pos.x = 0;
        p->velocity.x = -p->velocity.x;
    }
    else if (p->pos.x >= img->width) {
        p->pos.x = img->width - 1;
        p->velocity.x = -p->velocity.x;
    }
    if (p->pos.y < 0) {
        p->pos.y = 0;
        p->velocity.y = -p->velocity.y;
    }
    else if (p->pos.y >= img->height) {
        p->pos.y = img->height - 1;
        p->velocity.y = -p->velocity.y;
    }
}

void boundary_check(Particlesystem* ps, Image* img) {
    ParticleNode* curr = ps->firstP;

    while (curr != NULL) {
        if (!particle_is_within_image(curr->p, img)) {
            bounce_particle(img, &curr->p);
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
    handle_collisions(ps);
    apply_velocity(ps);
    boundary_check(ps, img);
    draw_particles(ps, img);
}