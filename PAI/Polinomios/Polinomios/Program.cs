using Polinomios.Clases;

Console.WriteLine("1: Dar (x,y) donde x coef, y exp");
Console.WriteLine("2: Encontrar raiz");

Polinomio P = new Polinomio();

while (true)
{
    int t = int.Parse(Console.ReadLine());
    if (t == 1)
    {
        double x;
        int y;
        x = double.Parse(Console.ReadLine());
        y = int.Parse(Console.ReadLine());
        P.addTermino(x, y);
    }

    else
    {
        if (P.deg % 2==1)
        {
            double x = P.Raiz();
            Console.Write("La raiz es: ");
            Console.WriteLine(x);
        }
        else
        {
            Console.WriteLine("Grado no es impar");
        }
    }
}
