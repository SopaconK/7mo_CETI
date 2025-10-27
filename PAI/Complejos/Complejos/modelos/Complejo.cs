using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Complejos.modelos
{
    internal class Complejo
    {
        private int real;
        private int imaginario;

        public Complejo()
        {
            real = 0;
            imaginario = 0;
        }

        public Complejo(int real, int imaginario) { 
            this.real = real;
            this.imaginario = imaginario;
        }

        public int Real
        {
            set { real = value; }
            get { return real; }
        }

        public int Imaginario
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
    }
}
