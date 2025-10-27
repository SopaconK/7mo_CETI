using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Polinomios.Clases
{
    internal class Polinomio
    {
        private List<(double, int)> coef;
        public int deg = 0;
        private Polinomio Derivada;
        private bool estaDerivado;

        public Polinomio()
        {
            coef=new List<(double, int)> ();
            estaDerivado = false;
        }

        public void addTermino(double x, int y)
        {
            coef.Add((x, y));
            deg = Math.Max(deg, y);
        }

        public double evaluar(double x)
        {
            double sum = 0;
            for (int i = 0; i < coef.Count(); i++)
            {
                sum += coef[i].Item1 * Math.Pow(x, coef[i].Item2);
            }
            return sum;
        }

        public Polinomio Derivar()
        {
            Polinomio derivado=new Polinomio();
            for (int i = 0; i < coef.Count(); i++)
            {
                if (coef[i].Item2> 0)
                {
                    derivado.addTermino(coef[i].Item1 * (coef[i].Item2), coef[i].Item2 - 1);
                }
            }
            return derivado;

        }

        public double Raiz()
        {

            if (!estaDerivado)
            {
                Derivada = Derivar();
                estaDerivado=true;
            }
            double x = 1434;
            while (Math.Abs(evaluar(x)) > 0.001)
            {
                x = iterar(x);
            }
            return x;
        }

        public double iterar(double x)
        {
            double a = evaluar(x);
            double b = Derivada.evaluar(x);
            if (b == 0)
            {
                return x -= 0.1;
            }
            return x - a / b;
        }

    }
}
