int[] arreglo;



arreglo=new int[int.Parse(Console.ReadLine())];
for (int i = 0; i < arreglo.Length; i++)
{
    arreglo[i] = i;
}

imprime(arreglo);
incrementa(arreglo);
imprime(arreglo);

arreglo = new int[arreglo.Length/2];
imprime(arreglo);







void imprime(int[] arreglo)
{
    for (int i = 0; i < arreglo.Length; i++)
    {
        Console.Write(arreglo[i]);
        Console.Write(" "); 
    }
    Console.WriteLine("");
}


void incrementa(int[] arreglo)
{
    for(int i=0; i<arreglo.Length; i++)
    {
        arreglo[i]++;
    }
}