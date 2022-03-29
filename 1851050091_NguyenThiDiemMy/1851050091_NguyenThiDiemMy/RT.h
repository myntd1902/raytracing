#include <stdlib.h>
#include <GL/glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <vector>
#include <math.h>
#include "Vec3.h"

double PI = 3.14159265359;
const int WIDTH = 640;
const int HEIGHT = 480;
const int sumPixel = WIDTH * HEIGHT;

template<typename T>
class Sphere
{
public:
    Vec3<T> center, color, emission;
    T radius, radius2;

    Sphere(const Vec3<T>& center, const T& radius, const Vec3<T>& color, const Vec3<T>& emission = 0) :
        center(center), radius(radius), color(color), emission(emission), radius2(radius* radius) {}

    bool intersect(const Vec3<T>& orig, const Vec3<T>& dir, T* t0 = NULL, T* t1 = NULL) const
    {
        //giải pháp hình học
        Vec3<T> L = center - orig; //vectơ từ gốc tia đến tâm hình cầu
        T tca = L.dot(dir); //độ lớn vectơ L theo hướng của phương tia
        if (tca < 0) //phương tia đi theo hướng ngược lại
            return false;
        T d2 = L.dot(L) - tca * tca; //bình phương đoạn thẳng kẻ từ tâm vuông góc với tia: áp dụng pytago
        if (d2 > radius2) //phương tia không đi trúng hình cầu
            return false;
        T thc = sqrt(radius2 - d2); //độ sâu của tca đi vào quả cầu: áp dụng pytago
        if (t0 != NULL && t1 != NULL)
        {
            *t0 = tca - thc; //độ lớn từ gốc tia đến giao điểm đầu tiên
            *t1 = tca + thc; //độ lớn từ gốc tia đến giao điểm thứ hai
        }
        return true;
    }

    void getSurfaceData(const Vec3<T>& phit, Vec3<T>& nhit) const
    {
        nhit = phit - center;
        nhit.normalize();
    }

};

template<typename T>
Vec3<T> trace(const Vec3<T>& orig, const Vec3<T>& dir,
    const std::vector<Sphere<T>*>& spheres)
{
    T tNear = INFINITY;
    const Sphere<T>* sphere = NULL;
    T bias = 1e-4;
    Vec3<T> color = 0;
    Vec3<T> phit;
    Vec3<T> nhit;

    for (unsigned i = 0; i < spheres.size(); ++i)
    {
        T t0 = INFINITY;
        T t1 = INFINITY;
        if (spheres[i]->intersect(orig, dir, &t0, &t1)) //tia cắt hình cầu
        {
            if (t0 < 0) //gốc tia trong hình cầu
                t0 = t1;

            if (t0 < tNear) //t0 trước tNear
            {
                tNear = t0;
                sphere = spheres[i];
            }
        }
    }

    if (!sphere)
        return Vec3<T>(0.8, 0.8, 0.8); //trả về màu nền


    phit = orig + (dir * tNear);
    sphere->getSurfaceData(phit, nhit); //lấy nhit

    for (unsigned i = 0; i < spheres.size(); ++i)
    {
        if (spheres[i]->emission.x > 0) //nguồn sáng
        {
            Vec3<T> lightDir = spheres[i]->center - phit;
            lightDir.normalize();
            Vec3<T> tms = 1.0;

            for (unsigned j = 0; j < spheres.size(); ++j)
            {
                if (j != i)
                {
                    T t0, t1;
                    if (spheres[j]->intersect(phit + (nhit * bias), lightDir, &t0, &t1))
                        tms *= spheres[j]->color;
                }
            }
            color += sphere->color * tms * std::max(T(0), nhit.dot(lightDir)) * spheres[i]->emission;
        }
    }
    return color + sphere->emission;
}

//tạo tia sơ cấp cho mỗi pixel, trace nó và trả về màu
Vec3<double>* image = new Vec3<double>[sumPixel];
static Vec3<double> cam_pos = Vec3<double>(0);
template<typename T>
void render(const std::vector<Sphere<T>*>& spheres)
{
    Vec3<T>* pixel = image;
    T fov = 25;
    T imgAspectratio = T(WIDTH) / T(HEIGHT); //tỷ lệ khung ảnh
    T angle = tan(PI * 0.5 * fov / T(180));

    for (GLuint y = 0; y < HEIGHT; ++y)
    {
        for (GLuint x = 0; x < WIDTH; ++x, ++pixel)
        {

            T xx = (2 * ((x + 0.5) * 1 / T(WIDTH)) - 1) * angle * imgAspectratio;
            T yy = (1 - 2 * ((y + 0.5) * 1 / T(HEIGHT))) * angle;

            ////MAYA-STYLE
            //T xx = (2 * ((x + 0.5) * 1 / T(WIDTH)) - 1) * angle;
            //T yy = (1 - 2 * ((y + 0.5) * 1 / T(HEIGHT))) * angle * 1 / imgAspectratio;

            Vec3<T> raydir(xx, yy, -1);
            raydir.normalize();
            *pixel = trace(cam_pos, raydir, spheres);
        }
    }
}