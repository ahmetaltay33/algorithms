using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection;
using System.Threading;
using System.Threading.Tasks;

namespace election_sample
{
    class Oy
    {
        public Guid Id { get; set; }
        public string Il { get; set; }
        public string Ilce { get; set; }
        public string Mahalle { get; set; }
        public string Okul { get; set; }
        public int SandikNo { get; set; }
        public string Parti { get; set; }
    }

    class Program
    {
        private static readonly string[] CIller = new[] {"İstanbul", "Ankara", "İzmir", "Bursa", "Eskişehir", "Antalya", "Mersin"};
        private static readonly string[] CIlceler = new[] {"Merkez", "1", "2", "3", "4"};
        private static readonly string[] CMahalleler = new[] {"Merkez", "A", "B", "C", "D"};
        private static readonly string[] COkullar = new[] {"X", "Y", "Z", "Q", "W"};
        private static readonly int[] CSandiklar = new[] {1, 2, 3, 4, 5, 6, 7, 8, 9};
        private static readonly string[] CPartiler = new[] {"A Partisi", "B Partisi"};
        private static int _count = 1;
        private static int _delayMs = 1;

        private static string GenerateRandomPartyName()
        {
            var random = new Random();
            var index = random.Next(0, 1);    
            return CPartiler[index];
        }

        private static List<Oy> GenerateRandomData()
        {
            var arr = new List<Oy>();
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
                                for (int n = 0; n < _count; n++)
                                {
                                    var oy = new Oy()
                                    {
                                        Id = Guid.NewGuid(),
                                        Il = CIller[i],
                                        Ilce = CIlceler[j],
                                        Mahalle = CMahalleler[k],
                                        Okul = COkullar[l],
                                        SandikNo = CSandiklar[m],
                                        Parti = GenerateRandomPartyName()
                                    };
                                    Thread.Sleep(_delayMs);
                                    arr.Add(oy);
                                }
                            }
                        }
                    }
                }
            }

            return arr;
        }

        private static ConcurrentBag<Oy> GenerateRandomDataUsingTasks()
        {
            var arr = new ConcurrentBag<Oy>(); // Thread Safe List
            var tasks = new List<Task>();
            for (int i = 0; i < CIller.Length; i++)
            {
                var ilAdi = CIller[i];
                var task = Task.Run(() =>
                {
                    for (int j = 0; j < CIlceler.Length; j++)
                    {
                        for (int k = 0; k < CMahalleler.Length; k++)
                        {
                            for (int l = 0; l < COkullar.Length; l++)
                            {
                                for (int m = 0; m < CSandiklar.Length; m++)
                                {
                                    for (int n = 0; n < _count; n++)
                                    {
                                        var oy = new Oy()
                                        {
                                            Id = Guid.NewGuid(),
                                            Il = ilAdi,
                                            Ilce = CIlceler[j],
                                            Mahalle = CMahalleler[k],
                                            Okul = COkullar[l],
                                            SandikNo = CSandiklar[m],
                                            Parti = GenerateRandomPartyName()
                                        };
                                        Thread.Sleep(_delayMs);
                                        arr.Add(oy);
                                    }
                                }
                            }
                        }
                    }
                });
                tasks.Add(task);
            }
            Task.WaitAll(tasks.ToArray());
            return arr;
        }

        private static ConcurrentBag<Oy> GenerateRandomDataUsingParallelLoop()
        {
            var arr = new ConcurrentBag<Oy>(); // Thread Safe List
            for (int i = 0; i < CIller.Length; i++)
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
                                Parallel.For(0, _count, n =>
                                {
                                    var oy = new Oy()
                                    {
                                        Id = Guid.NewGuid(),
                                        Il = CIller[i],
                                        Ilce = CIlceler[j],
                                        Mahalle = CMahalleler[k],
                                        Okul = COkullar[l],
                                        SandikNo = CSandiklar[m],
                                        Parti = GenerateRandomPartyName()
                                    };
                                    Thread.Sleep(_delayMs);
                                    arr.Add(oy);
                                });
                            });
                        });
                    });
                });
            });
            return arr;
        }

        private static void TestSirali()
        {
            Console.WriteLine("");
            Console.WriteLine("Veriler sıralı algoritma ile oluşturuluyor... (Paralel yok, sıralı)");
            var sw = Stopwatch.StartNew();
            var arr = GenerateRandomData();
            sw.Stop();
            Console.WriteLine($"Veriler oluşturuldu. Kayıt sayısı: {arr.Count} Geçen süre ms: {sw.ElapsedMilliseconds}");
            arr.Clear();
        }

        private static void TestIllerParalel()
        {
            Console.WriteLine("");
            Console.WriteLine("Task kullanılarak sadece illerin paralelleştirildiği yöntem ile veriler oluşturuluyor... (Sadece iller paralel)");
            var sw = Stopwatch.StartNew();
            var arr = GenerateRandomDataUsingTasks();
            sw.Stop();
            Console.WriteLine($"Veriler oluşturuldu. Kayıt sayısı: {arr.Count} Geçen süre ms: {sw.ElapsedMilliseconds}");
            arr.Clear();
        }
        
        private static void TestTamamiParalel()
        {
            Console.WriteLine("");
            Console.WriteLine("Tüm döngüler Parallel.For ile çalıştırılarak veriler oluşturuluyor... (Tüm döngüler paralel)");
            var sw = Stopwatch.StartNew();
            var arr = GenerateRandomDataUsingParallelLoop();
            sw.Stop();
            Console.WriteLine($"Veriler oluşturuldu. Kayıt sayısı: {arr.Count} Geçen süre ms: {sw.ElapsedMilliseconds}");
            arr.Clear();
        }

        private static void ClearMemory()
        {
            GC.Collect();
            GC.WaitForPendingFinalizers();
        }
        
        static void Main(string[] args)
        {
            if (args != null && args.Length != 0)
            {
                if(args.Length > 0)
                    _count = Convert.ToInt32(args[0]);
                if(args.Length > 1)
                    _delayMs = Convert.ToInt32(args[1]);
            }
            else
            {
                Console.WriteLine(
                    $"Programı parametreli olarak çağırabilirsiniz.\n" +
                    $"İlk parametre her sandık için oluşturulacak oy sayısı, ikinci parametre gecikme süresidir.\n" +
                    $"Varsayılan kullanım;\n" +
                    $"{Assembly.GetExecutingAssembly().GetName().Name}.exe {_count} {_delayMs}");
            }

            TestSirali();
            ClearMemory();

            TestIllerParalel();
            ClearMemory();
            
            TestTamamiParalel();
            ClearMemory();
        }
    }
}