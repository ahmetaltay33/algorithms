#include <mpi.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <windows.h> 

const int n = 1000;
int a[10000];

// Slave tasklar icin gecici matris
int a2[n];

int main(int argc, char* argv[])
{
  int pid, np, elements_per_process, n_elements_recieved;
  double start, end, total = 0;
  // np -> Task sayisi 
  // pid -> Task ID 

  MPI_Status status;
   
  // Paralel iþlemler olusturuluyor 
  MPI_Init(&argc, &argv);

  // Task ID bulunuyor 
  // ve kaç task calistirildigi aliniyor
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  // Master Task
  if (pid == 0) {
    start = MPI_Wtime();

    int index, i;
    elements_per_process = n / np;

    //Matris varsayilan degerleri ile dolduruluyor
    for (int i = 0; i < n; i++)
      a[i] = i;

    // birden fazla task calisiyor ise
    if (np > 1) {

      // Matris parcalara bolunup toplanmasi icin slave tasklara gonderiliyor. 
      for (i = 1; i < np - 1; i++) {
        index = i * elements_per_process;

        MPI_Send(&elements_per_process, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        MPI_Send(&a[index], elements_per_process, MPI_INT, i, 0, MPI_COMM_WORLD);
      }

      // son islem parcalanan matrisin kalan kismi icin yapiliyor
      index = i * elements_per_process;
      int elements_left = n - index;

      MPI_Send(&elements_left, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
      MPI_Send(&a[index], elements_left, MPI_INT, i, 0, MPI_COMM_WORLD);
    }

    // Master task kendi uzerine dusen barca icin hesaplamayi yapiyor
    int sum = 0;
    for (i = 0; i < elements_per_process; i++)
    {
      sum += a[i];
      Sleep(10);
    }

    // Slave tasklardan toplam sonuclarini alip birlestiriyor
    int tmp;
    for (i = 1; i < np; i++) {
      MPI_Recv(&tmp, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
      int sender = status.MPI_SOURCE;
      sum += tmp;
    }

    end = MPI_Wtime();
    
    printf("Master Task Sonuc: %d\n", sum);
    printf("Gecen Sure: %f", end - start);
  }
  // Slave Tasks 
  else {
    MPI_Recv(&n_elements_recieved, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

    // Gelen matris a2 matrisi icerisine depolaniyor
    MPI_Recv(&a2, n_elements_recieved, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

    // Slave taska ait matris icerigi toplaniyor
    int partial_sum = 0;
    for (int i = 0; i < n_elements_recieved; i++)
    {
      partial_sum += a2[i];
      Sleep(10);
    }
    printf("Slave Task: %d, Parcali Toplam: %d", pid, partial_sum);

    // Toplam sonucu master taska gonderiliyor 
    MPI_Send(&partial_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
  }

  // Cikmadan once tum MPI istekleri bellekten temizleniyor.
  MPI_Finalize();

  return 0;
}