// See https://aka.ms/new-console-template for more information
Console.WriteLine("Ingrese el número:");
int Numero, Digit0, Digit1, Digit2, Digit3,Temporal, NumeroGrande, NumeroChico, NuevoNumero, CantidadOperaciones=0;

void Swap(ref int a,ref int b)
{
    int Temporal;
    Temporal = a;
    a = b;
    b = Temporal;
}


Numero =int.Parse(Console.ReadLine());
if (Numero < 0 || Numero >= 10000)
{
    Console.WriteLine("Número fuera de rango");
    return;
}

do
{
    CantidadOperaciones++;
    Digit0 = Numero % 10;
    Digit1 = (Numero / 10) % 10;
    Digit2 = (Numero / 100) % 10;
    Digit3 = (Numero / 1000);

    if (Digit0 == Digit1 && Digit1 == Digit2 && Digit2 == Digit3)
    {
        Console.WriteLine("Todos iguales");
        return;
    }

    //Ordenar de menor a mayor, Bubble Sort
    if (Digit2 > Digit3)
    {
        Swap(ref Digit2,ref Digit3);
    }

    if (Digit1 > Digit2)
    {
        Swap(ref Digit2, ref Digit1);
    }
    if (Digit0 > Digit1)
    {
        Swap(ref Digit1, ref Digit0);
    }
    if (Digit2 > Digit3)
    {
        Swap(ref Digit2, ref Digit3);
    }

    if (Digit1 > Digit2)
    {
        Swap(ref Digit2, ref Digit1);
    }
    if (Digit2 > Digit3)
    {
        Swap(ref Digit2, ref Digit3);
    }

    NumeroGrande = 1000 * Digit3 + 100 * Digit2 + 10 * Digit1 + Digit0;
    NumeroChico = 1000 * Digit0 + 100 * Digit1 + 10 * Digit2 + Digit3;
    NuevoNumero = NumeroGrande - NumeroChico;
    Console.Write(Numero);
    Console.Write(": ");
    Console.Write(NumeroGrande);
    Console.Write(" - ");
    Console.Write(NumeroChico);
    Console.Write(": ");
    Console.WriteLine(NuevoNumero);
    Numero = NuevoNumero;
} while (Numero != 6174);
Console.Write("El total de iteraciones fue: ");
Console.WriteLine(CantidadOperaciones);