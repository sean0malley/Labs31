#include <iostream>
#include <vector>
#include <cmath>

// абстрактный класс

class Cylinder
{
public:
    Cylinder() : H(1) {}
    Cylinder(double h) : H(h) {}

    // чистый виртуальный метод расчета площади основания square()
    virtual double square() = 0;
    // метод расчета объема volume() – возвращает значение объема на основе поля H и метода расчета площади square().
    double volume() { return H * square(); }

    virtual ~Cylinder() {}

protected:
    double H; // поле H, содержащее высоту
};

// классы-наследники

class RoundCylinder : public Cylinder
{
public:
    RoundCylinder() : Cylinder(), R(1) {}
    RoundCylinder(double r, double h) : Cylinder(h), R(r)
    {

    }

    double square() { return 3.1415926 * R * R; }

private:
    double R;
};

class TrianglePrizm : public Cylinder
{
public:
    TrianglePrizm() : Cylinder(), A(1), B(1), C(1) {}
    TrianglePrizm(double a, double b, double c, double h = 1) : Cylinder(h), A(a), B(b), C(c)
    {

    }

    double square()
    {
        // формула Герона
        double p = (A + B + C) / 2; // полу-периметр
        return std::sqrt(p * (p - A) * (p - B) * (p - C));
    }

private:
    double A;
    double B;
    double C;
};

void printInfo(Cylinder& c)
{
    std::cout << c.volume() << '\n';
}

int main(void)
{
    //создание объектов-наследников класса
    RoundCylinder C1(3, 6);
    printInfo(C1);
    TrianglePrizm C2(3, 6, 2);
    printInfo(C2);
    std::cout << "------------" << std::endl;
    // объединение разных видов объектов-наследников класса в один массив
    int N = 10;
    std::vector<Cylinder*> figure_array(N);
    for (int i = 0; i < N; i++)
    {
        if (rand() % 2 == 1)
        {
            figure_array[i] = new RoundCylinder(i + 5, rand() % 5 + 2);
        }
        else
            figure_array[i] = new TrianglePrizm(i + 5, rand() % 5 + 2, rand()
                % 5 + 2, rand() % 5 + 2);
    }
    for (auto f : figure_array)
    {
        printInfo(*f);
    }
    for (auto& f : figure_array)
    {
        delete f;
    }
    return 0;
}
