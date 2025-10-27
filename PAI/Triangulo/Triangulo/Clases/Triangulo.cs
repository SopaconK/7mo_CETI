using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Triangulo.Clases
{
    internal class Triangulo:Areas
    {
        public int altura;
        public int Base;

        public Triangulo()
        {
            altura = 0;
            Base = 0;
        }

        public Triangulo(int h, int b)
        {
            altura = h;
            Base = b;
        }

        public double Area()
        {
            double area = (Base * altura) / 2;
            return area;
        }

    }
}
