using Grafos.Clases;
using System.Collections.Specialized;




Grafo g=new Grafo();

Console.WriteLine("1: Agregar nodo");
Console.WriteLine("2: Agregar arista");
Console.WriteLine("3: Preguntar caminos");

while (true)
{
    int t=int.Parse(Console.ReadLine());
    if (t == 1)
    {
        string s = Console.ReadLine();
        g.AddNodo(s);
    }
    else if (t == 2)
    {
        string s = Console.ReadLine();
        string s2 = Console.ReadLine();
        g.Unir(s, s2);
    }

    else if (t == 3)
    {
        string s = Console.ReadLine();
        string s2 = Console.ReadLine();
        g.EncontrarCamino(s,s2);
    }
}

//g.EncontrarCamino(0,2);














