using System;
using Microsoft.VisualBasic.CompilerServices;

namespace election_sample
{
    class Oy
    {
        public int Id { get; set; }
        public string Il { get; set; }
        public string Ilce { get; set; }
        public string Mahalle { get; set; }
        public string Okul { get; set; }
        public int SandikNo { get; set; }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("İşlemler başlıyor...");



            Console.WriteLine("İşlemler tamamlandı. Çıkmak için bir tuşa basın...");
            Console.ReadKey();
        }
    }
}
