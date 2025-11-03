using Complejos.modelos;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Complejos
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

     

      
        private void cmdSumarComplejos(object sender, RoutedEventArgs e)
        {
            Complejo a, b;
            double r, i;
            r = double.Parse(txtReal1.Text);
            i = double.Parse(txtImg1.Text);

            a = new Complejo(r, i);
            b = new Complejo(
                double.Parse(txtReal2.Text),
                double.Parse(txtImg2.Text)
                );

            Complejo s = a+b;

            txtResultadoReal.Text = s.Real.ToString();
            txtResultadoImg.Text =s.Imaginario.ToString();
        }


        private void cmdRestarComplejos(object sender, RoutedEventArgs e)
        {
            Complejo a, b;
            double r, i;
            r = double.Parse(txtReal1.Text);
            i = double.Parse(txtImg1.Text);

            a = new Complejo(r, i);
            b = new Complejo(
                double.Parse(txtReal2.Text),
                double.Parse(txtImg2.Text)
                );

            Complejo s = a - b;

            txtResultadoReal.Text = s.Real.ToString();
            txtResultadoImg.Text = s.Imaginario.ToString();
        }

        private void cmdMultiplicarComplejos(object sender, RoutedEventArgs e)
        {
            Complejo a, b;
            double r, i;
            r = double.Parse(txtReal1.Text);
            i = double.Parse(txtImg1.Text);

            a = new Complejo(r, i);
            b = new Complejo(
                double.Parse(txtReal2.Text),
                double.Parse(txtImg2.Text)
                );

            Complejo s = a * b;

            txtResultadoReal.Text = s.Real.ToString();
            txtResultadoImg.Text = s.Imaginario.ToString();
        }

        private void cmdDividirComplejos(object sender, RoutedEventArgs e)
        {
            Complejo a, b;
            double r, i;
            r = double.Parse(txtReal1.Text);
            i = double.Parse(txtImg1.Text);

            a = new Complejo(r, i);
            b = new Complejo(
                double.Parse(txtReal2.Text),
                double.Parse(txtImg2.Text)
                );

            if (b.Real==0 && b.Imaginario==0)
            {
                txtResultadoReal.Text = "0";
                txtResultadoImg.Text = "0";

                return;
            }
            Complejo s = a / b;

            txtResultadoReal.Text = s.Real.ToString();
            txtResultadoImg.Text = s.Imaginario.ToString();
        }


    }
}