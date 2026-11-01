Geica Elena-Bianca 333CC

BONUS: demonstratie corectitudine
Pentru N = 1000 si P = 3, se compileaza multiply_seq.c si rezolvare_test1.c prezente in director,
outputul lor se redirectioneaza in cate un fisier, apoi, intre cele doua fisiere .txt se face diff. (se poate folosi
test_multiply.sh pentru acest lucru). Daca diff nu afiseaza nimic, matricele obtinute sunt identice.

Demonstratie scalabilitate:

Pas 1) Comentez toate afisarile (mai putin cele de eroare ca oricum nu o sa le execute ca nu ajunge la ele, deci nu se adauga in Timp
       si daca as lua decizia sa le comentez si pe acelea, s-ar putea intampla, in cazul unei erori precum cea ca nu s-a dat nr de threaduri sau
       nr. de linii ale matricei, sa se termine foarte repede programul si sa inregistrez timpi irelevanti).

Pas 2) Programul secvential (dem_seq.c) foloseste aceeasi structura de calcul ca programul paralel (suma partiala intr-o
       variabila locala sum, scrisa o singura data in c[i][j]), pentru ca diferenta de timp sa provina doar din paralelizare.

!S-a folosit N = 1500 pentru demonstratie - MAXIMUL Restrictie practica: N <= 1500!

Timp program secvential (dem_seq.c -> time ./seq 1500 -> real) : 0m9.295s

Timp program paralel (dem_parallel.c -> time ./parallel 1500 P -> real):

1) P = 1 => 0m10.030s
2) P = 2 => 0m5.283s
3) P = 3 => 0m4.134s
4) P = 4 => 0m3.988s

Acceleratia obtinuta (Speed-up-ul) este reprezentata de raportul dintre timpul prog. secv. supra timpul prog. paralel:
1) S = 9.295 / 10.030 = 0,927
2) S = 9.295 / 5.283 = 1,759
3) S = 9.295 / 4.134 = 2,248
4) S = 9.295 / 3.988 = 2,331

Eficienta este data de raportul dintre Speed-up si numarul de threaduri folosite:
1) E = S / 1 = 0,927 / 1 = 0,927
2) E = S / 2 = 1,759 / 2 = 0,880
3) E = S / 3 = 2,248 / 3 = 0,749
4) E = S / 4 = 2,331 / 4 = 0,583

Comentariu scalabilitate:
- Cu P = 1, programul paralel este putin mai lent decat cel secvential (S < 1), din cauza costului suplimentar
  al crearii thread-ului si al operatiilor lock/unlock pe mutex, facute pentru fiecare element c[i][j].
- Acceleratia creste odata cu numarul de thread-uri, dar din ce in ce mai putin: de la 1 la 2 thread-uri timpul
  aproape se injumatateste, insa de la 3 la 4 thread-uri castigul este foarte mic.
- Eficienta scade pe masura ce P creste (de la 0,93 la 0,58), deci solutia nu scaleaza ideal.
- Cauza principala este descompunerea obligatorie dupa k: toate thread-urile contribuie la acelasi element c[i][j],
  deci adunarea finala trebuie protejata cu mutex. Fiecare thread face N*N operatii lock/unlock, iar thread-urile
  parcurg i si j in aceeasi ordine, deci ajung sa astepte unele dupa altele la acelasi mutex. Cu cat sunt mai multe
  thread-uri, cu atat creste timpul pierdut la mutex.
- Calculul sumelor partiale (partea costisitoare) ruleaza insa complet in paralel, iar mutexul protejeaza doar
  instructiunea c[i][j] += sum, deci serializarea este minima pentru aceasta descompunere.
