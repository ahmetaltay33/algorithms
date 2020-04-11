using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Threading;
using Microsoft.VisualBasic.CompilerServices;
using Timer = System.Timers.Timer;

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
        private static readonly string[] CIller = new[] {"İstanbul", "Ankara", "İzmir", "Bursa", "Eskişehir", "Antalya", "Mersin"};
        private static readonly string[] CIlceler = new[] {"Merkez", "1", "2", "3", "4"};
        private static readonly string[] CMahalleler = new[] {"Merkez", "A", "B", "C", "D"};
        private static readonly string[] COkullar = new[] {"X", "Y", "Z", "Q", "W"};
        private static readonly int[] CSandiklar = new[] {1, 2, 3, 4, 5, 6, 7, 8, 9};
        
        static Oy[] GenerateRandomData(int count)
        {
            var arr = new Oy[] { };
            for (int i = 0; i < CIller.Length; i++)
            {
                for (int j = 0; j < CIlceler.Length; j++)
                {
                    for (int k = 0; k < CMahalleler.Length; k++)
                    {
                        for (int l = 0; l < COkullar.Length; l++)
                        {
                            for (int m = 0; m < CSandiklar.Length; m++)
                            {
                                for (int n = 0; n < count; n++)
                                {
                                    var oy = new Oy()
                                    {
                                        Id = arr.Length + 1,
                                        Il = CIller[i],
                                        Ilce = CIlceler[j],
                                        Mahalle = CMahalleler[k],
                                        Okul = COkullar[l],
                                        SandikNo = CSandiklar[m],
                                    };
                                    Array.Resize(ref arr, arr.Length + 1);
                                    arr[arr.Length - 1] = oy;
                                }
                            }
                        }
                    }
                }
            }
            return arr;
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Rastgele veriler oluşturuluyor...");
            var sw = Stopwatch.StartNew();
            var oylar = GenerateRandomData(10);   
            sw.Stop();
            Console.WriteLine($"Rastgele oluşturulan kayıtların sayısı {oylar.Length} Geçen süre ms: {sw.ElapsedMilliseconds}");
            
            Console.WriteLine("İşlemler tamamlandı.");
        }
    }
}