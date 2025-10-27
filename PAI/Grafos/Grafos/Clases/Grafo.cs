using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Grafos.Clases
{
    internal class Grafo
    {
        public List<Nodo> nodos=new List<Nodo>();
        private List<(Nodo, Nodo)> pila;
        private List<Nodo> camino;
        private int cantcaminos = 0;
        public Grafo(List<Nodo> nodos)
        {
            this.nodos = nodos;
        }
        public Grafo() { }


        public void AddNodo(String s)
        {
            Nodo x=new Nodo(s);
            x.ind = nodos.Count();
            nodos.Add(x);
        }


        public void Unir(string sx, string sy)
        {
            int x = StringToInd(sx);
            int y = StringToInd(sy);
            if(x!=-1 && y!=-1) Unir(x, y);
        }
        private void Unir(int x, int y)
        {
            nodos[x].Unir(nodos[y]);
        }
        private int StringToInd(string s)
        {
            for(int i = 0; i < nodos.Count; i++)
            {
                if (nodos[i].nombre == s) return i;
            }
            return -1;
        }

        public void EncontrarCamino(string s1, string s2)
        {
            int x=StringToInd(s1);
            int y=StringToInd(s2);
            if (x != -1 && y != -1) EncontrarCamino(x, y);
        }
        public void EncontrarCamino(int x, int y)
        {
            if (isCycle())
            {
                Console.WriteLine("Hay ciclos");
                return;
            }
            if (x == y)
            {
                Console.WriteLine("Son iguales");
                return;
            }
            Nodo a = nodos[x];
            Nodo b = nodos[y];
           
            pila = new List<(Nodo, Nodo)>();
            camino = new List<Nodo>();
            cantcaminos = 0;
            pila.Add((a, new Nodo()));
            while (pila.Count() > 0)
            {
                AgregarACamino();
                if (camino.Count() == 0) continue;
                if (camino[camino.Count() - 1] == b)
                {
                    cantcaminos++;
                    for (int i = 0; i < camino.Count() - 1; i++)
                    {
                        Console.Write(camino[i].nombre);
                        Console.Write(" -> ");
                    }
                    Console.WriteLine(camino[camino.Count() - 1].nombre);
                    camino.RemoveAt(camino.Count() - 1);
                }
            }
            if (cantcaminos == 0)
            {
                Console.WriteLine("No caminos");

            }
        }

        private void AgregarACamino()
        {
            Nodo X = pila[pila.Count() - 1].Item1;
            Nodo y = pila[pila.Count() - 1].Item2;
            pila.RemoveAt(pila.Count() - 1);
            if (camino.Count() > 0)
            {
                while (camino.Count > 0 && camino[camino.Count() - 1] != y) camino.RemoveAt(camino.Count() - 1);
                if (camino.Count() > 0 && camino[camino.Count() - 1] == y)
                {
                    camino.Add(X);
                    foreach (Nodo n in X.vecinos)
                    {
                        pila.Add((n, X));
                    }

                }

            }
            else
            {
                camino.Add(X);
                foreach (Nodo n in X.vecinos)
                {
                    pila.Add((n, X));
                }
            }
        }

        private bool[] visitados;
        private bool[] visitadosGlob;

        public bool isCycle()
        {
            visitados=new bool[nodos.Count()];
            visitadosGlob = new bool[nodos.Count()];
            for (int i = 0; i < nodos.Count(); i++)
            {
                
                if (visitadosGlob[i]) continue;
                
                if (dfs(i)) return true;
            }
            return false;
        }

        private bool dfs(int x)
        {
  

            if(visitados[x]) return true;
            visitados[x] = true;
            visitadosGlob[x] = true;
         
            foreach(Nodo n in nodos[x].vecinos)
            {
                
                if (dfs(n.ind)) return true;
            }
            visitados[x] = false;
            return false;

        }

    }
}
