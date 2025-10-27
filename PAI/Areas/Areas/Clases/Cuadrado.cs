using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Areas.Clases
{
    internal class Cuadrado:FigurasConArea
    {
        private double lado;
        public double Lado
        {
            set
            {
                lado = (value < 0) ? 0 : value;
            }
            get { return lado; }
        }
        public Cuadrado()
        {
            Lado = 0;
        }

        public Cuadrado(double lado)
        {
            Lado = lado;
        }

        public double Area()
        {
            return lado * lado;
        }


    }
}
