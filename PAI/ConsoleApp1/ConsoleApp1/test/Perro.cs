using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1.test
{
    internal class Perro : Animal
    {
        public Perro() { }
        public void comer() { Console.WriteLine("Perro: Comiendo"); }
        public void caminar() { Console.WriteLine("Perro: Caminando"); }
    }
}
