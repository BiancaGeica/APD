Geica Elena-Bianca 333CC

BONUS: demonstratie corectitudine
Pentru N = 1000 si P = 3, se compileaza multiply_seq.c si rezolvare_test1.c prezente in director,
outputul lor se redirectioneaza in cate un fisier, apoi, intre cele doua fisiere .txt se face diff. (se poate folosi 
test_multiply.sh pentru acest lucru).

Demonstratie scalabilitate:

Pas 1) Comentez toate afisarile (mai putin cele de eroare ca oricum nu o sa le execute ca nu ajunge la ele, deci nu se adauga in Timp
       si daca as lua decizia sa le comentez si pe acelea, s-ar putea intampla, in cazul unei erori precum cea ca nu s-a dat nr de threaduri sau
       nr. de linii ale matricei, sa se termine foarte repede programul si sa inregistrez timpi irelevanti).

!S-a folosit N = 1500 pentru demonstratie - MAXIMUL Restricție practică: N <= 1500!

Timp program secvential (dem_seq.c -> time ./seq 1500 3 -> real ) : 0m15.657s

Timp program paralel (dem_parallel.c -> time ./parallel 1500 P -> real):

1) P = 1 => 0m10.030s
2) P = 2 => 0m5.283s
3) P = 3 => 0m4.134s
4) P = 4 => 0m3.988s

Acceleratia obtinuta (Speed-up-ul) este reprezentata de raportul dintre timpul prog. secv. supra timpul prog. paralel:
1) S = 15.657 / 10.030 = 1,561
2) S = 15.657 / 5.283 = 2,963
3) S = 15.657 / 4.134 = 3,787
4) S = 15.657 / 3.988 = 3,926

Eficienta este data de raportul dintre Speed-up si numarul de threaduri folosite:
1) E = S / 1 = 1,561 / 1 = 1,561
2) E = S / 2 = 2,963 / 2 = 1,4815
3) E = S / 3 = 3,787 / 3 = 1,262
4) E = S / 4 = 3,926 / 4 = 0,9815