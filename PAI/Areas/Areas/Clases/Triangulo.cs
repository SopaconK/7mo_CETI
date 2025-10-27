using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Areas.Clases
{
    internal class Triangulo:FigurasConArea
    {
        private double altura;
        private double @base;
        public double Altura{
            set{
                altura = (value < 0) ? 0 : value;
            }

            get
            {
                return altura;
            }
        }

        public double Base
        {
            set
            {
                @base = (value < 0) ? 0 : value;
            }
            get
            {
                return @base;
            }
        }




        public Triangulo()
        {
            Altura = 0;
            Base = 0;
        }

        public Triangulo(double h, double b)
        {
            Altura = h;
            Base = b;
        }

        public double Area()
        {
            double area = (@base * altura) / 2;
            return area;
        }
    }
}
