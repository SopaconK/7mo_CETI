using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1.test
{
    internal class Paloma : Animal
    {
        public Paloma() { }
        public void comer() { Console.WriteLine("Paloma: Comiendo"); }
        public void caminar() { Console.WriteLine("Paloma: Caminando"); }
        public void volar() { Console.WriteLine("Paloma: Volando"); }
    }
}
