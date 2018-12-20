#include <iostream>

#include <ray.h>
#include "objects/sphere.h"
#include "float.h"
#include "hitablelist.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "io/stb_image_write.h"

// first try in c++ after years, raytracing in a weekend..

float hit_sphere(const vec3& center, float radius, const ray& r){

    vec3 ac = r.origin() - center; // oc means ac in the book
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(ac, r.direction());
    float c = dot(ac,ac) - radius * radius;
    float discrim  = b*b - 4*a*c;
    //return (discrim > 0); // only check for intersection, not where / when
    if (discrim < 0) {
        return -1.0;
    }
    else {
        return (-b-sqrt(discrim)) / (2.0 * a);
    }
}
vec3 color(const ray& r, hitable *scene){
    // color sphere red
    intersect_record rec;
    if (scene->hit(r,0.0,MAXFLOAT, rec)) {
        return 0.5 * vec3(rec.normal.x()+1,rec.normal.y() + 1, rec.normal.z() +1);
    }
    else{
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5,0.7,1.0);
    }

    

}

int main() {
    
    // Test some ppm output
    int nx = 600;
    int ny = 300;
    const int numChannels = 3;
    const std::string fileName = "output.png";
    unsigned char *imgData = new unsigned char[nx*ny*numChannels];

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    vec3 lower_left_corner(-2.0,-1.0,-1.0);
    vec3 horizontal(4.0, 0.0,0.0);
    vec3 vertical(0.0,2.0,0.0);
    vec3 origin(0.0,0.0,0.0);
    
    //Objects
    hitable *list[2];
    list[0] = new sphere(vec3(0,0,-1), 0.5);
    list[1] = new sphere(vec3(0,-100.5,-1),100);
    hitable_list *scene = new hitable_list(list,2);

    // OUTPUT
    for (int j = ny-1; j >= 0; j--){
        for (int i = 0; i < nx; i++) {
            
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            vec3 col = color(r,scene);
            int ir = int(255.99 * col.r());
            int ig = int(255.99 * col.g());
            int ib = int(255.99 * col.b());
            //std::cout << ir << " " << ig << " " << ib << "\n";
            imgData[(nx*numChannels)*(ny -1 -j) + numChannels*i+0] = ir;
            imgData[(nx*numChannels)*(ny -1 -j) + numChannels*i+1] = ig;
            imgData[(nx*numChannels)*(ny -1 -j) + numChannels*i+2] = ib;
        }
    }

    stbi_write_png(fileName.c_str(), nx, ny, numChannels, imgData, nx*numChannels);
    delete[] imgData;
}