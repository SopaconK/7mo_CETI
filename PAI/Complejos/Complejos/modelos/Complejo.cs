using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Complejos.modelos
{
    internal class Complejo
    {
        private double real;
        private double imaginario;

        public Complejo()
        {
            real = 0;
            imaginario = 0;
        }

        public Complejo(double real, double imaginario) { 
            this.real = real;
            this.imaginario = imaginario;
        }

        public double Real
        {
            set { real = value; }
            get { return real; }
        }

        public double Imaginario
        {
            set {  imaginario = value; }
            get { return imaginario; }
        }

        public static Complejo Suma(Complejo a, Complejo b)
        {
            return new Complejo(
                a.Real + b.Real,
                a.Imaginario + b.Imaginario
               );
        }

        
        public static Complejo operator + (Complejo a, Complejo b)
        {
            return Suma(a, b);
        }

        public static Complejo Resta(Complejo a, Complejo b)
        {
            return new Complejo(
                a.Real - b.Real,
                a.Imaginario - b.Imaginario
               );
        }


        public static Complejo operator -(Complejo a, Complejo b)
        {
            return Resta(a, b);
        }

        public static Complejo Multiplicacion(Complejo a, Complejo b)
        {
            return new Complejo(
                a.Real*b.Real-a.Imaginario*b.Imaginario,
                a.Real*b.Imaginario+a.Imaginario*b.Real
               );
        }


        public static Complejo operator *(Complejo a, Complejo b)
        {
            return Multiplicacion(a, b);
        }

        public static Complejo Dividir(Complejo a, Complejo b)
        {  
            return Multiplicacion(a,new Complejo(
                b.Real/(b.Real*b.Real+b.Imaginario*b.Imaginario),
                 -b.Imaginario / (b.Real * b.Real + b.Imaginario * b.Imaginario)
                ));
        }


        public static Complejo operator /(Complejo a, Complejo b)
        {
            return Dividir(a, b);
        }

       
    }
}
