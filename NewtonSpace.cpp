#ifndef NEWTONSPACE
#define NEWTONSPACE

// std::vector
#include <vector>
// sqrt
#include <cmath>
// memset
#include <cstring>

struct Point {
    double x, y;
    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }

    Point() {
        this->x = .0;
        this->y = .0;
    }

    Point operator *(double c) {
        return Point(this->x*c, this->y*c);
    }

    Point operator /(double c) {
        return Point(this->x/c, this->y/c);
    }

    Point operator +(Point p2) {
        return Point(this->x+p2.x, this->y+p2.y);
    }

    Point operator -(Point p2) {
        return Point(this->x-p2.x, this->y-p2.y);
    }
};


struct Particle {
    double mass, r;
    Point pos, d;
    Particle(double mass, double r, Point pos, Point d) {
        this->mass = mass;
        this->r = r;
        this->pos = pos;
        this->d = d;
    }
};


class NewtonSpace {
public:
    std::vector<Particle> particles;

    NewtonSpace() {
    }

    ~NewtonSpace() {
    }

    void addParticle(Particle p) {
        this->particles.push_back(p);
    }

    int getLen() {
        return this->particles.size();
    }

    void update(double G, double time, bool collide=false) {
        this->updateSpd(G, time, collide);
        this->updatePos(time);
    }

    std::vector<Particle> getParticles() {
        return this->particles;
    }

protected:

    // Main part!
    void updateSpd(double G, double time, bool collide) {
        const int len = this->getLen();

        // distances
        double dist[len][len];
        // forces
        double a[len][len];
        // accelerations
        double d2x[len];
        double d2y[len];

        memset(d2x, .0, sizeof(d2x));
        memset(d2y, .0, sizeof(d2y));

        // distances
        for(int i=0; i<len; i++) {
            for(int j=0; j<len; j++) {
                if(i==j)continue;
                dist[i][j] = sqrt(
                    pow(((this->particles)[i].pos.x - (this->particles)[j].pos.x),2.) +
                    pow(((this->particles)[i].pos.y - (this->particles)[j].pos.y),2.)
                );
            }
        }

        // forces
        for(int i=0; i<len; i++) {
            for(int j=0; j<len; j++) {
                if(i==j)continue;
                // cannot div by zero
                a[i][j] = G*(this->particles)[i].mass/pow(((dist[i][j]<.001)?.001:dist[i][j]),2);
            }
        }

        // accelerations
        for(int i=0; i<len; i++) {
            for(int j=0; j<len; j++) {
                if(i==j)continue;
                d2x[i] += a[i][j]*((this->particles)[i].pos.x - (this->particles)[j].pos.x);
                d2y[i] += a[i][j]*((this->particles)[i].pos.y - (this->particles)[j].pos.y);
            }
        }

        // apply
        for(int i=0; i<len; i++) {
            (this->particles)[i].d.x -= d2x[i]*time;
            (this->particles)[i].d.y -= d2y[i]*time;
        }

        if(!collide)return;
        // handle collide
        for(int i=0; i<len-1; i++) {
            for(int j=i+1; j<len; j++) {
                if(dist[i][j] < (this->particles)[i].r + (this->particles)[j].r) {
                    Particle newi = (this->particles)[i];
                    Particle newj = (this->particles)[j];

                    newi.d = ((this->particles)[i].d*((this->particles)[i].mass-(this->particles)[j].mass)+(this->particles)[j].d*(2*(this->particles)[j].mass)) / ((this->particles)[i].mass+(this->particles)[j].mass);
                    newj.d = ((this->particles)[j].d*((this->particles)[j].mass-(this->particles)[i].mass)+(this->particles)[i].d*(2*(this->particles)[i].mass)) / ((this->particles)[i].mass+(this->particles)[j].mass);

                    (this->particles)[i] = newi;
                    (this->particles)[j] = newj;

                    // Some stupid hacks
                    while(
                        sqrt(
                            pow(((this->particles)[i].pos.x - (this->particles)[j].pos.x),2.) +
                            pow(((this->particles)[i].pos.y - (this->particles)[j].pos.y),2.)
                        ) < (this->particles)[i].r + (this->particles)[j].r
                    ) {

                        (this->particles)[i].pos.x += (this->particles)[i].d.x*time;
                        (this->particles)[i].pos.y += (this->particles)[i].d.y*time;

                        (this->particles)[j].pos.x += (this->particles)[j].d.x*time;
                        (this->particles)[j].pos.y += (this->particles)[j].d.y*time;}
                }
            }
        }
    }

    void updatePos(double time) {
        const int len = this->getLen();

        for(int i=0; i<len; i++) {
            (this->particles)[i].pos.x += (this->particles)[i].d.x*time;
            (this->particles)[i].pos.y += (this->particles)[i].d.y*time;
        }
    }
};

#endif
