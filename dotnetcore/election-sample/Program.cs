using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Threading;
using System.Threading.Tasks;

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
            var arrLength = CIller.Length * CIlceler.Length * CMahalleler.Length * COkullar.Length * CSandiklar.Length *
                            count;
            var arr = new Oy[arrLength];
            var arrIndex = 0;
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
                                    arrIndex++;
                                    var oy = new Oy()
                                    {
                                        Id = arrIndex,
                                        Il = CIller[i],
                                        Ilce = CIlceler[j],
                                        Mahalle = CMahalleler[k],
                                        Okul = COkullar[l],
                                        SandikNo = CSandiklar[m],
                                    };
                                    arr[arrIndex - 1] = oy;
                                }
                            }
                        }
                    }
                }
            }
            return arr;
        }

        static Oy[] GenerateRandomDataAsParallel(int count)
        {
            var arrLength = CIller.Length * CIlceler.Length * CMahalleler.Length * COkullar.Length * CSandiklar.Length *
                            count;
            var arr = new Oy[arrLength];
            var arrIndex = 0;
            Parallel.For(0, CIller.Length, i =>
            {
                Parallel.For(0, CIlceler.Length, j =>
                {
                    Parallel.For(0, CMahalleler.Length, k =>
                    {
                        Parallel.For(0, COkullar.Length, l =>
                        {
                            Parallel.For(0, CSandiklar.Length, m =>
                            {
                                Parallel.For(0, count, n =>
                                {
                                    Interlocked.Increment(ref arrIndex);
                                    var oy = new Oy()
                                    {
                                        Id = arrIndex,
                                        Il = CIller[i],
                                        Ilce = CIlceler[j],
                                        Mahalle = CMahalleler[k],
                                        Okul = COkullar[l],
                                        SandikNo = CSandiklar[m],
                                    };
                                    arr[arrIndex - 1] = oy;
                                });
                            });
                        });
                    });
                });
            });
            return arr;
        }
        
        static void Main(string[] args)
        {
            Console.WriteLine("Rastgele veriler oluşturuluyor...");
            var sw = Stopwatch.StartNew();
            var oylar = GenerateRandomData(10000);   
            sw.Stop();
            Console.WriteLine($"Rastgele veriler oluşturuldu. Kayıt sayısı: {oylar.Length} Boyut: {Marshal.SizeOf(oylar)} Geçen süre ms: {sw.ElapsedMilliseconds}");
            sw.Start();
            var oylar2 = GenerateRandomDataAsParallel(10000);
            sw.Stop();
            Console.WriteLine($"Rastgele veriler oluşturuldu. Kayıt sayısı: {oylar2.Length} Boyut: {Marshal.SizeOf(oylar2)} Geçen süre ms: {sw.ElapsedMilliseconds}");
            Console.WriteLine("");
            Console.WriteLine("İşlemler tamamlandı.");
        }
    }
}