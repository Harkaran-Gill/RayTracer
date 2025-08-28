//
// Created by harka on 27-08-2025.
//

#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"
#include "vec3.h"

class material {
public:
    virtual ~material() = default;

    virtual bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const {
        return false;
    }

};


class lambertian : public material {
public:
    lambertian(const color& albedo) : albedo(albedo) {}

    bool scatter(const ray &ray_in, const hit_record &rec, color &attenuation, ray &scattered)
    const override {
        auto scatter_direction = rec.normal + random_unit_vector();

        // Check if direction is not zero
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;

    }

private:
    color albedo;
};

class metal : public material {
public:
    metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz:1){}

    bool scatter(const ray &ray_in, const hit_record &rec, color &attenuation, ray &scattered)
    const override {
        vec3 reflected = reflect(ray_in.direction(), rec.normal);   // calculating reflected ray's direction
        reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return dot(scattered.direction(), rec.normal) > 0;
    }

private:
    color albedo;
    double fuzz;
};




#endif //MATERIAL_H
