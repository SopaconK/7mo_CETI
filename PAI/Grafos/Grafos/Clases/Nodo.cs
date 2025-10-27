using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Grafos.Clases
{
    internal class Nodo
    {
        public string nombre;
        public int ind;
        public List<Nodo> vecinos = new List<Nodo>();

        public Nodo() { }
        public Nodo(string nombre) { this.nombre = nombre; }

        public void Unir(Nodo N)
        {
            vecinos.Add(N);
        }


    }
}
