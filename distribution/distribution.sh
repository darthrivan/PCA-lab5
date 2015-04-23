#! /bin/sh

n_elems=100000000
n_bits=22
runs=3
freq=3200000


LANG=C
filename="results.txt"
nombre="distribution"


# Para las distribuciones 0 i 1
for d in `seq 0 1 1`; do
	rm -f $n_elems-$d-$filename

	# Para diferentes tamaños de bits
	for b in `seq 1 1 $n_bits`; do

		# Ejecutamos
		printf "$b " >> $n_elems-$d-$filename

		# Ejecutamos run veces y hacemos el cálculo:
		#  Ciclos por elemento: (tiempo*FREQUENCIA/n_elems)/runs

		./$nombre.3 $n_elems $b $d
		for i in `seq 1 $runs`; do
			./$nombre.3 $n_elems $b $d
		done | awk '/^[0-9]/{user+=$1;sys+=$2;i++} 
			END{printf "%.2f\n",((user+sys)*'$freq'/('$n_elems'*i))}' >> $n_elems-$d-$filename

	done

done

