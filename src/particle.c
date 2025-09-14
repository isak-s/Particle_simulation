#include "particle.h"
#include <math.h>
#include "constants.h"
#define G 6.67430e-11
#define METERS_PER_PIXEL 1.0

Particle new_particle(double x, double y, Color c) {
    Particle p;
    p.pos.x = x;
    p.pos.y = y;
    p.color = c;
    p.mass = 1000000;
    p.velocity.x = 0;
    p.velocity.y = 0;
    p.history_index = 0;
    p.move_randomly = 0;
    return p;
}


double distance_between(Particle p1, Particle p2) {
    return sqrt(pow(p1.pos.x - p2.pos.x, 2) + pow(p1.pos.y - p2.pos.y, 2));
}

Vec2 normalized_vec2(Vec2 v) {
    Vec2 newV;
    double len = sqrt(pow(v.x, 2) + pow(v.y, 2));
    newV.x = v.x / len;
    newV.y = v.y / len;

    return newV;
}

double magnitude_gravitational_force_between(Particle p1, Particle p2) {
    double d = distance_between(p1, p2);
    if (d < 0.000001) {return 1;}
    return (G * p1.mass * p2.mass) /
            pow(d * METERS_PER_PIXEL, 2);
}

Vec2 gravitational_force_between(Particle p1, Particle p2) {
    Vec2 v;
    v.x = p2.pos.x - p1.pos.x;
    v.y = p2.pos.y - p1.pos.y;
    Vec2 nv = normalized_vec2(v);
    double f = magnitude_gravitational_force_between(p1, p2);
    nv.x *= f;
    nv.y *= f;

    return nv;

}

void add_curr_pos_to_old_positions(Particle* p) {
    p->old_positions[p->history_index] = p->pos;
    p->history_index = (p->history_index + 1) % NUM_OLD_POSITIONS;
}


void clamp_velocity(Particle* p) {
    // could apply some breaking force here every tick instead
    Vec2 norm = normalized_vec2(p->velocity);
    norm.x *= MAX_VELOCITY;
    norm.y *= MAX_VELOCITY;
    p->velocity = norm;
}